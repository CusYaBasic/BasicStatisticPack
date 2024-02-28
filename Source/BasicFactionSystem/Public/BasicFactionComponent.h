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
#include "Engine.h"
#include "Components/ActorComponent.h"
#include "BasicFactionComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFactionUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFactionDown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFactionJoin, FString, factionname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFactionLeave, FString, factionname);


UENUM(Blueprintable)
enum FactionHostility
{

	Loved UMETA(DisplayName = "Loved"),
	Liked UMETA(DisplayName = "Liked"),
	Neutral UMETA(DisplayName = "Neutral"),
	Disliked UMETA(DisplayName = "Disliked"),
	Hated UMETA(DisplayName = "Hated")

};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHostilityChanged, FString, factionname, TEnumAsByte<FactionHostility>, newhostility);


USTRUCT(Blueprintable)
struct FFactionValues : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		UTexture2D* FactionIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int FactionLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int MaxFactionLevel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int CurrentFactionReputation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int NextFactionReputation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int PreviousFactionReputation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		int MaxReputation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Factions")
		TEnumAsByte<FactionHostility> Hostility;
};



USTRUCT(Blueprintable)
struct FFactionInfo : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Reputation")
		int NextFactionReputation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Reputation")
		int PreviousFactionReputation;
};

USTRUCT(Blueprintable)
struct FHostilityLevels : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hostility")
		TEnumAsByte<FactionHostility> Hostility;

};

UENUM()
enum OwnerTypeFaction
{

	Player_F UMETA(DisplayName = "Player"),
	AI_F UMETA(DisplayName = "AI")

};

UENUM()
enum ChangeTypeFaction
{

	Add_F UMETA(DisplayName = "Add"),
	Remove_F UMETA(DisplayName = "Remove"),
	Change_F UMETA(DisplayName = "Change")

};

UCLASS(Blueprintable, ClassGroup = (Custom))
class BASICFACTIONSYSTEM_API UBasicFactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBasicFactionComponent();

	//Select whether this is a player or AI
	UPROPERTY(Replicated, EditAnywhere, Category = "Faction|Main")
		TEnumAsByte<OwnerTypeFaction> Owner;

	//Components current primary Factions
	UPROPERTY(Replicated, EditAnywhere, Category = "Faction|Main")
		TArray<FFactionValues> Factions;

	//Faction Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Faction|Data")
		class UDataTable* FactionInfo;

	//Faction Default Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Faction|Data")
		class UDataTable* FactionDefault;

	//Faction Default Data Table
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly, Category = "Faction|Data")
		class UDataTable* FactionHostilityLevels;

	//Can this component gain or lose reputation?
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Faction|Main")
		bool CanModifyReputation;

	//Sound this component play sound?
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Faction|Sounds")
		bool PlaySound;

	//Level up sound
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Faction|Sounds")
		USoundCue* FactionLevelUpSound;

	//Level down sound
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Faction|Sounds")
		USoundCue* FactionLevelDownSound;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	int Percentage(int x, int a, int b);

	//Get Faction Level-
	//
	//Get a factions level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionLevel(FString name);

	//Get Faction Icon-
	//
	//Get a factions icon by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		UTexture2D* GetFactionIcon(FString name);

	//Get Faction Max Reputation Level-
	//
	//Get a Factions max level by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionMaxReputationLevel(FString name);

	//Get Faction Current Reputation-
	//
	//Get a Factions current reputation by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionCurrentReputation(FString name);

	//Get Faction Next Reputation-
	//
	//Get a Factions next reputation by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionNextReputation(FString name);

	//Get Faction Previous Reputation-
	//
	//Get a Factions previous reputation by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionPreviousReputation(FString name);

	//Get Faction Max Reputation-
	//
	//Get a Factions max reputation by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionMaxReputation(FString name);

	//Is Max Faction-
	//
	//Get if selected Faction is at it's max value by name/type
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool IsMaxFactionLevel(FString name);

	//Is In Faction-
	//
	//Returns if in named faction
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool IsInFaction(FString name);

	//Check For Hostility Change
	//
	//Checks if the hostility state needs to be changed
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Get"))
		void CheckForHostilityChange(FString name);

	//Get Faction By Name
	//
	//Get a Factions struct by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		FFactionValues GetFactionByName(FString name);

	//Get Faction Index
	//
	//Get a Factions array index by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionIndex(FString name);

	//ModifyReputation-
	//
	//Add or remove Reputation from selected Faction by name
	//Fires an overideable FactionUp/FactionDown event if reaches reputation caps
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Modify"))
		void ModifyReputation(FString name, ChangeTypeFaction changetype, int amount, bool debug);

	//Has Enough Reputation To Level-
	//
	//Checks if this component has enough reputation to advance to the next reputation level
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool HasEnoughReputationToLevel(int current, int amountNeeded);

	//Has Required Faction Level-
	//
	//Checks if this component has the declared level needed
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool HasRequiredFactionLevel(FString name, int FactionLevelNeeded);

	//Has Enough Reputation To Down Faction-
	//
	//Checks if this component has enough reputation to decrease a Faction
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool HasEnoughReputationToDownLevel(int current, int amountNeeded);

	//Set Can Modify Reputation-
	//
	//Change whether this component can add/remove reputation
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Modify"))
		void SetCanModifyReputation(bool canmodify);

	//Get Can Modify Reputation-
	//
	//Get whether this component can add/remove reputation
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool GetCanModifyReputation();

	//Get Faction Reputation Value As Percentage
	//
	//Gets selected Faction as a percentage by type/name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetFactionReputationValueAsPercentage(FString name);

	//Get Faction Reputation Value For Progress Bar
	//
	//Gets selected Faction as a percentage by type/name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		float GetFactionReputationValueForProgressBar(FString name);

	//Get Reputation Left Until Faction Up As Percentage
	//
	//Gets selected Factions Reputation until Faction up as percentage
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetReputationLeftUntilFactionLevelUpAsPercentage(FString name);

	//Get Reputation Left Until Faction Up
	//
	//Gets selected Factions reputation until Faction up
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		int GetReputationLeftUntilFactionLevelUp(FString name);

	//Is Player
	//
	//Return if this components owner is controller by a player or AI
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Get"))
		bool IsPlayer();

	//Join Faction
	//
	//Joins faction by name
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Get"))
		void JoinFaction(FString name);

	//Leave Faction
	//
	//Leave faction by name
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Get"))
		void LeaveFaction(FString name);

	//Faction Up Overideable Events
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Misc"))
		void FactionLevelUp(const FString& name);

	//Faction Down Overideable Events
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Misc"))
		void FactionLevelDown(const FString& name);

	//Set Factions
	//
	//Sets the factions array, used to help with loading saves
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Faction|Misc"))
		void SetFactions(TArray<FFactionValues> faction);

	//Get Factions
	//
	//Gets the factions array, used to help with saving games
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Faction|Misc"))
		void GetFactions(TArray<FFactionValues> &faction);

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Faction|Bind"))
		FOnFactionUp OnFactionLevelUp;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Faction|Bind"))
		FOnFactionDown OnFactionLevelDown;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Faction|Bind"))
		FHostilityChanged OnHostilityChanged;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Faction|Bind"))
		FOnFactionJoin OnFactionJoin;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Faction|Bind"))
		FOnFactionLeave OnFactionLeave;
};