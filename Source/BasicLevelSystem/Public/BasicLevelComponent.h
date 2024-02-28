/*
 * @
 * @ Copyright Simple Game Studios/Basic/Lewis Herbert, All Rights Reserved. @2022
 * @
 *
 *  If ya'll need help with anything to do with this product hit me up:
 *  Twitter: @SimpleGameIndie
 *  Discord: https://discord.gg/ub5ZpSfUEP
 *  Email: support@simplegamestudios.co.uk
 *
 *  Last but not least, Ya Basic!
 *
 */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "Math/Color.h"
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "BasicLevelComponent.generated.h"



//Level values struct, we use FTableRowBase so we can turn it into a data table
USTRUCT(Blueprintable)
struct FLevelValues : public FTableRowBase
{
	GENERATED_BODY()

	//Name of the level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		FString Name;

	//Current level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int Level;

	//Max allowed level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int MaxLevel;

	//Current xp
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int CurrentXP;

	//XP needed to advance to the next level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int NextLevelXP;

	//XP needed to go down to the next level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int PreviousLevelXP;

	//Max allowed XP
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Levels")
		int MaxXP;

	//Stat icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		UTexture2D* Icon;

	//Stat color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FColor Color;
};

//Level info, we use FTableRowBase so we can tur nit into a data table
USTRUCT(Blueprintable)
struct FLevelInfo : public FTableRowBase
{
	GENERATED_BODY()

	//XP needed to advance to the next level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XP")
		int NextLevelXP;

	//XP needed to go down to the next level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "XP")
		int PreviousLevelXP;
};

//LevelType, enum used to declare what level we're modifying or checking
UENUM()
enum LevelType
{

	Main_L UMETA(DisplayName = "Main"),
	Primary_L UMETA(DisplayName = "Primary"),
	Secondary_L UMETA(DisplayName = "Secondary")

};

//OwnerTypeLevel, enum used to declare if the owner is player or AI
UENUM()
enum OwnerTypeLevel
{

	Player_L UMETA(DisplayName = "Player"),
	AI_L UMETA(DisplayName = "AI")

};

//ChangeTypeLevel, enum used to declare how we are modifying the level 
UENUM()
enum ChangeTypeLevel
{

	Add_L UMETA(DisplayName = "Add"),
	Remove_L UMETA(DisplayName = "Remove"),
	Change_L UMETA(DisplayName = "Change")

};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of event delegates
////////////////////////////////////////////////////////////////////////////////////////////////////////

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyXP, ChangeTypeLevel, changetype, int, oldxp, int, newxp, int, amount);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of event delegates
////////////////////////////////////////////////////////////////////////////////////////////////////////

UCLASS(Blueprintable, ClassGroup=(Custom) )
class BASICLEVELSYSTEM_API UBasicLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasicLevelComponent();

	//Select whether this is a player or AI
	UPROPERTY(Replicated, EditAnywhere, Category = "Level")
		TEnumAsByte<OwnerTypeLevel> Owner;

	//Components main level
	UPROPERTY(Replicated, EditAnywhere, Category = "Level")
		FLevelValues MainLevel;

	//Components current primary levels
	UPROPERTY(Replicated, EditAnywhere, Category = "Level")
		TArray<FLevelValues> PrimaryLevels;

	//Components current secondary levels
	UPROPERTY(Replicated, EditAnywhere, Category = "Level")
		TArray<FLevelValues> SecondaryLevels;

	//Main Level Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Data")
		class UDataTable* LevelInfo;

	//Primary Level Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Data")
		class UDataTable* PrimaryLevelInfo;

	//Secondary Level Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Data")
		class UDataTable* SecondaryLevelInfo;

	//Level Defaults Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Level|Data")
		class UDataTable* LevelDefaultsInfo;

	//Can this component gain or lose xp?
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Level")
		bool CanModifyXP;

	//Does this component play sound?
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Level|Sounds")
		bool PlaySound;

	//Sound to play on level up
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Level|Sounds")
		USoundCue* LevelUpSound;

	//Sound to play on level down
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Level|Sounds")
		USoundCue* LevelDownSound;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

public:	

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of functions
////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Replcates the variables
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//Calculate a percentage from a range of numbers
	int Percentage(int x, int a, int b);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of functions
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of UFUNCTIONS
//
//	These functions can be called by blueprints because they are labeled "UFUNCTION" which exposes them
//	to blueprints.
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Load Main Level-
	//
	//Sets this components main level
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Modify"))
		void LoadMainLevel(FLevelValues Details);

	//Load Primary Levels-
	//
	//Sets this components primary levels
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Modify"))
		void LoadPrimaryLevels(TArray<FLevelValues> Details);

	//Load secondary Levels-
	//
	//Sets this components secondary levels
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Modify"))
		void LoadSecondaryLevel(TArray<FLevelValues> Details);

	//Get Main Level Details-
	//
	//Gets this components main level details
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		FLevelValues GetMainLevelDetails();

	//Get Primary Level-
	//
	//Gets this components primary level details
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		TArray<FLevelValues> GetPrimaryLevelDetails();

	//Get Secondary Level Details-
	//
	//Gets this components secondary level details
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		TArray<FLevelValues> GetSecondaryLevelDetails();

	//Get Main Level-
	//
	//Gets this components main level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevel();

	//Get Main Level Max Level-
	//
	//Gets this components main levels max level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevelMaxLevel();

	//Get Main Level Name-
	//
	//Gets this components main level name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		FString GetMainLevelName();

	//Get Main Level Current XP-
	//
	//Get this components main level current xp
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevelCurrentXP();

	//Get Main Level Next Level XP-
	//
	//Get this components main level next level xp
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevelNextLevelXP();

	//Get Main Level Previous Level XP-
	//
	//Get this components main level previous level xp
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevelPreviousLevelXP();

	//Get Main Level Max XP-
	//
	//Get this components main level max xp
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetMainLevelMaxXP();

	//Get Primary Level-
	//
	//Get a primary level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevel(FString name);

	//Get Primary Level Max Level-
	//
	//Get a primary levels max level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelMaxLevel(FString name);

	//Get Primary Level Current XP-
	//
	//Get a primary levels current xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelCurrentXP(FString name);

	//Get Primary Level Next Level XP-
	//
	//Get a primary levels next level xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelNextLevelXP(FString name);

	//Get Primary Level Previous Level XP-
	//
	//Get a primary levels previous level xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelPreviousLevelXP(FString name);

	//Get Primary Level Max XP-
	//
	//Get a primary levels max xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelMaxXP(FString name);

	//Get Secondary Level-
	//
	//Get a secondary level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevel(FString name);

	//Get Secondary Level Max Level-
	//
	//Get a secondary levels max level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelMaxLevel(FString name);

	//Get Secondary Level Current XP-
	//
	//Get a secondary levels current xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelCurrentXP(FString name);

	//Get Secondary Level Next Level XP-
	//
	//Get a secondary levels next level xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelNextLevelXP(FString name);

	//Get Secondary Level Previous Level XP-
	//
	//Get a secondary levels previous level xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelPreviousLevelXP(FString name);

	//Get Secondary Level Max XP-
	//
	//Get a secondary levels max xp by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelMaxXP(FString name);

	//Get Level Defaults-
	//
	//Returns default values for the seleceted level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		FLevelValues GetLevelDefaults(FString name);

	//Does Primary Level Exist-
	//
	//Returns if primary level exists in our level array
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool DoesPrimaryLevelExist(FString name);

	//Does Secondary Level Exist-
	//
	//Returns if secondary level exists in our level array
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool DoesSecondaryLevelExist(FString name);

	//Is Max Level-
	//
	//Get if selected level is at it's max value by name/type
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool IsMaxLevel(LevelType level, FString name);

	//Get Primary Level By Name
	//
	//Get a primary levels struct by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		FLevelValues GetPrimaryLevelByName(FString name);

	//Get Primary Level Index
	//
	//Get a primary levels array index by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetPrimaryLevelIndex(FString name);

	//Get Secondary Level By Name-
	//
	//Get a secondary levels struct by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		FLevelValues GetSecondaryLevelByName(FString name);

	//Get Secondary Level Index-
	//
	//Get a secondary levels array index by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetSecondaryLevelIndex(FString name);

	//ModifyXP-
	//
	//Add or remove xp from selected level by type/name
	//Fires an overideable LevelUp/LevelDown event if reaches XP caps
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Modify"))
		void ModifyXP(LevelType level, FString name, ChangeTypeLevel changetype, int amount, bool debug);

	//Has Enough XP To Level-
	//
	//Checks if this component has enough xp to advance to the next level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool HasEnoughXPToLevel(int current, int amountNeeded);

	//Has Enough XP To Level-
	//
	//Checks if this component has enough xp to advance to the next level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool HasRequiredLevel(LevelType level, FString name, int levelneeded);

	//Has Enough XP To Down Level-
	//
	//Checks if this component has enough xp to decrease a level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool HasEnoughXPToDownLevel(int current, int amountNeeded);

	//Set Can Modify XP-
	//
	//Change whether this component can add/remove xp
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Modify"))
		void SetCanModifyXP(bool canmodify);

	//Get Can Modify XP-
	//
	//Get whether this component can add/remove xp
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool GetCanModifyXP();

	//Get Level XP Value As Percentage
	//
	//Gets selected level as a percentage by type/name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetLevelXPValueAsPercentage(LevelType level, FString name);

	//Get Level XP Value For Progress Bar
	//
	//Gets selected level as a percentage by type/name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		float GetLevelXPValueForProgressBar(LevelType level, FString name);

	//Get XP Left Until Level Up As Percentage
	//
	//Gets selected levels xp until level up as percentage
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetXPLeftUntilLevelUpAsPercentage(LevelType level, FString name);

	//Get XP Left Until Level Up
	//
	//Gets selected levels xp until level up
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		int GetXPLeftUntilLevelUp(LevelType level, FString name);

	//Is Player
	//
	//Return if this components owner is controller by a player or AI
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Level|Get"))
		bool IsPlayer();

	//Level Up Overideable Events
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Misc"))
		void LevelUp(LevelType level, const FString& name);

	//Level Down Overideable Events
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Level|Misc"))
		void LevelDown(LevelType level, const FString& name);


////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of UFUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of Bindable events
//
//	These properties are the bindable events that get fired in certain functions allowing blueprint
// 	users ability to add their own logic to the function.
// 	mainly used for updating UI/Widgets.
////////////////////////////////////////////////////////////////////////////////////////////////////////

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Level|Bind"))
		FOnLevelUp OnLevelUp;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Level|Bind"))
		FOnLevelDown OnLevelDown;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Level|Bind"))
		FOnModifyXP OnModifyXP;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of Bindable events
////////////////////////////////////////////////////////////////////////////////////////////////////////
};