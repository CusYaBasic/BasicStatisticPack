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
#include "Engine/Texture2D.h"
#include "Sound/SoundCue.h"
#include "Engine/StaticMesh.h"
#include "Engine.h"
#include "WorldCurrency.h"
#include "Components/ActorComponent.h"
#include "BasicCurrencyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPurchaseSuccess, FString, itemname, int, amounttopurchase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPurchaseFailed);

USTRUCT(Blueprintable)
struct FCurrencyValues
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		int CurrentAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		int MaxAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		UTexture2D* CurrencyImage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
		bool PlaySound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
		USoundCue* CurrencyIncreasedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
		USoundCue* CurrencyDecreasedSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Currency")
		USoundCue* CurrencyDropSound;

	
};

UENUM(Blueprintable)
enum CurrencyType
{

	Main_C UMETA(DisplayName = "Main"),
	Secondary_C UMETA(DisplayName = "Secondary"),
	Special_C UMETA(DisplayName = "Special")

};

UENUM(Blueprintable)
enum OwnerTypeCurrency
{

	Player_C UMETA(DisplayName = "Player"),
	AI_C UMETA(DisplayName = "AI")

};

UENUM(Blueprintable)
enum CurrencyChangeType
{

	Add_C UMETA(DisplayName = "Add"),
	Remove_C UMETA(DisplayName = "Remove"),
	Change_C UMETA(DisplayName = "Change")

};

UCLASS(Blueprintable, ClassGroup=(Custom))
class BASICCURRENCYSYSTEM_API UBasicCurrencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBasicCurrencyComponent();

	//Select whether this is a player or AI
	UPROPERTY(Replicated, EditAnywhere, Category = "Currency")
		TEnumAsByte<OwnerTypeCurrency> Owner;

	//Components main currency
	UPROPERTY(Replicated, EditAnywhere, Category = "Currency")
		FCurrencyValues MainCurrency;

	//Components current secondary currencies
	UPROPERTY(Replicated, EditAnywhere, Category = "Currency")
		TArray<FCurrencyValues> SecondaryCurrencies;

	//Components current special currencies
	UPROPERTY(Replicated, EditAnywhere, Category = "Currency")
		TArray<FCurrencyValues> SpecialCurrencies;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Replcate variables
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//Get Main Currency-
	//
	//Gets this components main Currency
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetMainCurrencyAmount();

	//Get Main Currency Max Currency-
	//
	//Gets this components main Currencies max amount
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetMainCurrencyMaxAmount();

	//Get Main Currency Name-
	//
	//Gets this components main Currency name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		FString GetMainCurrencyName();


	//Get Main Currency Current Icon-
	//
	//Get this components main Currency current Icon
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UTexture2D* GetMainCurrencyIcon();

	//Get Main Currency Play Sound-
	//
	//Get if this currency plays sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		bool GetMainCurrencyPlaySound();

	//Get Main Currency Increase Sound-
	//
	//Get this components main Currency increase sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetMainCurrencyIncreaseSound();

	//Get Main Currency Decrease Sound-
	//
	//Get this components main Currency decrease sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetMainCurrencyDecreaseSound();

	//Get Main Currency Drop Sound-
	//
	//Get this components main Currency decrease sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetMainCurrencyDropSound();

	//Get Main Currency Mesh
	//
	//Get this components main Currency mesh
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UStaticMesh* GetMainCurrencyMesh();

	//Get Special Currency By Name
	//
	//Get a speical currency struct by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		FCurrencyValues GetSpecialCurrencyByName(FString name);

	//Get Special Currency Index
	//
	//Get a special currency array index by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSpecialCurrencyIndex(FString name);

	//Get Special Currency Amount-
	//
	//Get a Special Currency by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSpecialCurrencyAmount(FString name);

	//Get Special Currency Max Amount-
	//
	//Get a Special Currencies max amount by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSpecialCurrencyMaxAmount(FString name);

	//Get Special Currency Icon-
	//
	//Get a Special Currencies icon by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UTexture2D* GetSpecialCurrencyIcon(FString name);

	//Get Special Currency Play Sound-
	//
	//Get if this currency plays sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		bool GetSpecialCurrencyPlaySound(FString name);

	//Get Special Currency Increase Sound-
	//
	//Get a Special Currencies increase sound by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSpecialCurrencyIncreaseSound(FString name);

	//Get Special Currency Decrease Sound-
	//
	//Get a Special Currencies decrease sound by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSpecialCurrencyDecreaseSound(FString name);

	//Get Special Currency Drop Sound-
	//
	//Get this components special Currency decrease sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSpecialCurrencyDropSound(FString name);

	//Get Special Currency Mesh-
	//
	//Get a Special Currencies mesh by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UStaticMesh* GetSpecialCurrencyMesh(FString name);

	//Get Secondary Currency By Name
	//
	//Get a secondary currency struct by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		FCurrencyValues GetSecondaryCurrencyByName(FString name);

	//Get Secondary Currency Index
	//
	//Get a Secondary currency array index by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSecondaryCurrencyIndex(FString name);

	//Get Secondary Currency Amount-
	//
	//Get a Secondary Currency by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSecondaryCurrencyAmount(FString name);

	//Get Secondary Currency Max Amount-
	//
	//Get a Secondary Currencies max amount by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		int GetSecondaryCurrencyMaxAmount(FString name);

	//Get Secondary Currency Icon-
	//
	//Get a Secondary Currencies icon by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UTexture2D* GetSecondaryCurrencyIcon(FString name);

	//Get Secondary Currency Play Sound-
	//
	//Get if this currency plays sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		bool GetSecondaryCurrencyPlaySound(FString name);

	//Get Secondary Currency Increase Sound-
	//
	//Get a Secondary Currencies increase sound by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSecondaryCurrencyIncreaseSound(FString name);

	//Get Secondary Currency Decrease Sound-
	//
	//Get a Secondary Currencies decrease sound by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSecondaryCurrencyDecreaseSound(FString name);

	//Get Secondary Currency Drop Sound-
	//
	//Get this components secondary Currency decrease sound
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		USoundCue* GetSecondaryCurrencyDropSound(FString name);

	//Get Secondary Currency Mesh-
	//
	//Get a Secondary Currencies mesh by name
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		UStaticMesh* GetSecondaryCurrencyMesh(FString name);

	//Has Enough Currency-
	//
	//Check if we have enough of our declared currency
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		bool HasEnoughCurrency(CurrencyType currency, FString name, int amount);

	//Get Currency Drop Location-
	//
	//Get the default drop location (in front of character)
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Get"))
		FTransform GetCurrencyDropLocation();

	//Modify Currency-
	//
	//Add or remove from selected currency by type/name
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Modify"))
		void ModifyCurrency(CurrencyType currency, FString name, CurrencyChangeType changetype, int amount, bool debug);

	//Purchase-
	//
	//Buy something with the declared currency
	//Checks if we have enough to buy, fires a bindable event if successful
	//Also fires a seperate bindable evnet if unsuccessful
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Modify"))
		void Purchase(CurrencyType currency, FString currencyname, int costamount, FString itemname, int amounttopurchase);

	//Drop Currency-
	//
	//Drops declared currency and amount
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Modify"))
		void DropCurrency(CurrencyType currency, FString name, int amount, FTransform transform, bool debug);

	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Modify"))
		bool DoesSecondaryCurrencyExist(FString name);

	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Modify"))
		bool DoesSpecialCurrencyExist(FString name);

	//Set Currencies
	//
	//Set the currency structs and arrays, used for help with loading games
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Currency|Misc"))
		void SetCurrencies(FCurrencyValues main, TArray<FCurrencyValues> secondary, TArray<FCurrencyValues> special);

	//Get Currencies
	//
	//Get the currency structs and arrays, used for help with saving games
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Currency|Misc"))
		void GetCurrencies(FCurrencyValues &main, TArray<FCurrencyValues> &secondary, TArray<FCurrencyValues> &special);

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Currency|Bind"))
		FOnPurchaseSuccess OnPurchaseSuccess;

	UPROPERTY(BlueprintAssignable, meta = (Category = "Basic|Currency|Bind"))
		FOnPurchaseFailed OnPurchaseFailed;
};