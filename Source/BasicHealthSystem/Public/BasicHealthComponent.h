/*
 * @
 * @ Copyright Simple Game Studios/Basic/Lewis Herbert, All Rights Reserved. @2022
 * @
 *
 *  If ya'll need help with anything to do with this product hit me up:
 *  Twitter: @CusYaBasic
 *  Discord: CusYaBasic#9194
 *  Email: cusyabasic@hotmail.com
 *
 *  Last but not least, Ya Basic!
 *
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/AudioComponent.h"
#include "Components/SceneComponent.h"
#include "Sound/SoundBase.h"
#include "Math/Color.h"
#include "TimerManager.h"
#include "BasicHealthComponent.generated.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of structs
////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Timer delegates, used for the overtime functions
*/
USTRUCT(BlueprintType)
struct FTimerDels
{

	GENERATED_BODY()

	FSimpleDelegate HealthIncrease;
	FSimpleDelegate HealthDecrease;

	FSimpleDelegate ShieldIncrease;
	FSimpleDelegate ShieldDecrease;

	FSimpleDelegate StaminaIncrease;
	FSimpleDelegate StaminaDecrease;

	FSimpleDelegate ResourceIncrease;
	FSimpleDelegate ResourceDecrease;

	FSimpleDelegate EnergyIncrease;
	FSimpleDelegate EnergyDecrease;

	FSimpleDelegate HydrationIncrease;
	FSimpleDelegate HydrationDecrease;

	FSimpleDelegate SprintingIncrease;
	FSimpleDelegate SprintingDecrease;
};


/*
* Timer handles, used for the overtime functions
*/
USTRUCT(BlueprintType)
struct FTimerHandles
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle HealthIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle HealthDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle ShieldIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle ShieldDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle StaminaIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle StaminaDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle ResourceIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle ResourceDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle EnergyIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle EnergyDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle HydrationIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle HydrationDecrease;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle SprintingIncrease;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		FTimerHandle SprintingDecrease;
};

/*
* Stat values, holds all the variables for our stats
*/
USTRUCT(BlueprintType)
struct FCYB_Values
{
	GENERATED_BODY()

	//Current stat value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float Current;

	//Original stat value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float Default;

	//Max stat value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float Max;

	//Amount to add every interval 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float OvertimeIncrease;
	//Amount to remove every interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float OvertimeDecrease;

	//Amount of time between each increase interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float IncreaseRate;

	//Amount of time between each decrease interval
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float DecreaseRate;
};

/*
* Death values, holds all the variables for our death
*/
USTRUCT(BlueprintType)
struct FDeathValues
{

	GENERATED_BODY()

	//Location to respawn after death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		FVector RespawnLocation;

	//Rotation of character after death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		FRotator RespawnRotation;

	//Name of Level to go to on death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		FName MainMenuLevelName;

	//Widget to show on death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		UUserWidget* Widget;

	//Posititon of death widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		FVector2D WidgetPos;

	//Delay the death function by a specifiyed time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
		float DeathDelay;
};

/*
* Check values, holds all the variables for our checks
*/
USTRUCT(BlueprintType)
struct FChecks
{

	GENERATED_BODY()

		//Can this component take damamge?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool CanBeDamaged = true;

		//Reset health to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetHealth = true;

		//Reset shield to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetShield = true;

		//Reset stamina to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetStamina = true;

		//Reset Resource to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetResource = true;

		//Reset hydration to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetHydration = true;

		//Reset energy to max value on death?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
			bool ResetEnergy = true;
};

/*
* Sound values, holds all the variables for our sounds
*/
USTRUCT(BlueprintType)
struct FSounds
{

	GENERATED_BODY()

		//Sound to play when hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayHealthHitSound = true;

		//Sound to play when shields hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayShieldHitSound = true;

		//Sound to play when healths low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayHealthLowSound = true;

		//Sound to play when shields low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayShieldLowSound = true;

		//Sound to play when components owner dies
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayDeathSound = true;

		//Sound to play when Shield hits 0
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayShieldBreakSound = true;

		//Sound to play when staminas low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Play Sound")
			bool PlayStaminaLowSound = true;

		//Sound to play when hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundBase* HealthHitSounds;

		//Sound to play when hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* HealthHitSound;

		//Sound to play when shields hit
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* ShieldHitSound;

		//Sound to play when healths low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* HealthLowSound;

		//Sound to play when shields low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* ShieldLowSound;

		//Sound to play when components owner dies
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* DeathSound;

		//Sound to play when Shield hits 0
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* ShieldBreakSound;

		//Sound to play when staminas low
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			USoundCue* StaminaLowSound;

		//At what percent should the low health sound play?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			float HealthLowPercentage;

		//At what percent should the low shield sound play?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			float ShieldLowPercentage;

		//At what percent should the low stamina sound play?
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sounds")
			float StaminaLowPercentage;
};

USTRUCT(BlueprintType)
struct FAnimDetails
{

	GENERATED_BODY()

	//Refernece to the characters anim instance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
		UAnimInstance* AnimInstance;

	//Play hit animation?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
		bool PlayHitAnim;

	//Play death animation?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
		bool PlayDeathAnim;

	//Anim to play on hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
		UAnimMontage* HitAnim;
	//Anim to play on death
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Details")
		UAnimMontage* DeathAnim;
};

USTRUCT(BlueprintType)
struct FStatInfo
{
	GENERATED_BODY()

	//Stat icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		UTexture2D* Icon;

	//Stat color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FColor Color;

};

USTRUCT(BlueprintType)
struct FStatMedia
{
	GENERATED_BODY()

	//Health media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo HealthMedia;

	//Shield media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo ShieldMedia;

	//Stamina media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo StaminaMedia;

	//Resource media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo ResourceMedia;

	//Energy media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo EnergyMedia;

	//Hydration media
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
		FStatInfo HydrationMedia;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of structs
////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of enums
////////////////////////////////////////////////////////////////////////////////////////////////////////

UENUM(BlueprintType)
enum StatsType
{

	Health_H UMETA(DisplayName = "Health"),
	Shield_H UMETA(DisplayName = "Shield"),
	Stamina_H UMETA(DisplayName = "Stamina"),
	Resource_H UMETA(DisplayName = "Resource"),
	Energy_H UMETA(DisplayName = "Energy"),
	Hydration_H UMETA(DisplayName = "Hydration")

};


UENUM(BlueprintType)
enum StatType
{

	Health_H2 UMETA(DisplayName = "Health"),
	Shield_H2 UMETA(DisplayName = "Shield"),
	Both_H UMETA(DisplayName = "Both")

};

UENUM(BlueprintType)
enum ChangeType
{

	Add_H UMETA(DisplayName = "Add"),
	Remove_H UMETA(DisplayName = "Remove"),
	Change_H UMETA(DisplayName = "Change")

};


UENUM(BlueprintType)
enum DeathType
{

	Respawn_H UMETA(DisplayName = "Respawn"),
	Main_Menu_H UMETA(DisplayName = "Main Menu"),
	Destroy_H UMETA(DisplayName = "Destroy"),
	Show_Widget_H UMETA(DisplayName = "Show Widget")

};

UENUM(BlueprintType)
enum OwnerTypeHealth
{

	Player_H UMETA(DisplayName = "Player"),
	AI_H UMETA(DisplayName = "AI"),
	World_Object_H UMETA(DisplayName = "World Object")

};


UENUM(BlueprintType)
enum MovementType
{

	Walking_H UMETA(DisplayName = "Walking"),
	Crouching_H UMETA(DisplayName = "Crouching"),
	Sprinting_H UMETA(DisplayName = "Sprinting")

};
////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of enums
////////////////////////////////////////////////////////////////////////////////////////////////////////


USTRUCT(BlueprintType)
struct FMovementDetails
{

	GENERATED_BODY()

	//Select the components current movement type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		TEnumAsByte<MovementType> Movement;

	//Current walking speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float WalkingSpeed;

	//Current crouching speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float CrouchingSpeed;

	//Current sprinting speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float SprintingSpeed;

	//Min amount of stamina value allowed for sprinting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float MinSprintStamina;

	//Min amount of stamina value allowed for jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float MinJumpStamina;

	//Cost amount of stamina value allowed for jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Settings")
		float JumpStaminaCost;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of event delegates
////////////////////////////////////////////////////////////////////////////////////////////////////////

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SevenParams(FOnDamageEvent, float, oldshield, float, oldhealth, float, newshield, float, newhealth, float, amount, bool, didoverflow, float, overflowamount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyHealth, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldhealth, float, newhealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyShield, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldshield, float, newshield);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyResource, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldresource, float, newresource);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyStamina, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldstamina, float, newstamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyEnergy, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldenergy, float, newenergy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnModifyHydration, TEnumAsByte<ChangeType>, changetype, float, amount, float, oldhydration, float, newshydration);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of event delegates
////////////////////////////////////////////////////////////////////////////////////////////////////////

//We make our class blueprintable so we can use as a blueprint component
UCLASS(Blueprintable, ClassGroup = (Custom))
class BASICHEALTHSYSTEM_API UBasicHealthComponent : public UActorComponent
{
	GENERATED_BODY()

		

public:
	// Sets default values for this component's properties
	UBasicHealthComponent();

	

	//Select what type the owner of this component is
	UPROPERTY(Replicated, EditAnywhere, Category = "Death Settings")
		TEnumAsByte<OwnerTypeHealth> Type;

	//What happens when this component "Dies"
	UPROPERTY(Replicated, EditAnywhere, Category = "Death Settings")
		TEnumAsByte<DeathType> OnDeath;

	//Set new respawn locations or main menu level
	UPROPERTY(Replicated, EditAnywhere, Category = "Death Settings")
		FDeathValues DeathValues;

	//Components current health value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Health;

	//Components current shield value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Shield;

	//Components current stamina value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Stamina;

	//Components current resource value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Resource;

	//Components current energy value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Energy;

	//Components current Hydration value
	UPROPERTY(Replicated, EditAnywhere, Category = "Stats")
		FCYB_Values Hydration;

	//Components checks
	UPROPERTY(Replicated, EditAnywhere, Category = "Checks")
		FChecks Checks;

	//Component sounds
	UPROPERTY(Replicated, EditAnywhere, Category = "Sounds")
		FSounds Sounds;

	//Component anims
	UPROPERTY(Replicated, EditAnywhere, Category = "Anims")
		FAnimDetails Anims;

	//Component movement
	UPROPERTY(Replicated, EditAnywhere, Category = "Movement")
		FMovementDetails Movement;

	//Component media
	UPROPERTY(Replicated, EditAnywhere, Category = "Media")
		FStatMedia Media;

	//Low health audio component
	UPROPERTY(Replicated, EditAnywhere, Category = "Sounds|Health")
		UAudioComponent* HealthLowAudioComponent = nullptr;

	//Low shield audio component
	UPROPERTY(EditAnywhere, Category = "Sounds|Shield")
		UAudioComponent* ShieldLowAudioComponent = nullptr;

	//Low stamina audio component
	UPROPERTY(Replicated, EditAnywhere, Category = "Sounds|Stamina")
		UAudioComponent* StaminaLowAudioComponent = nullptr;

	//Timers used for overtime functions:- Don't recommend interfering with them.
	UPROPERTY(Replicated, EditAnywhere, Category = "Core")
		FTimerHandles TimerHandles;

	//Delegates used for overtime functions:- Don't recommend interfering with them.
	UPROPERTY(Replicated, EditAnywhere, Category = "Core")
	FTimerDels TimerDels;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start of functions
// 
//	These functions primarily get called from within other functions and may need certain data passed
// 	through to function correctly, so they're not delcared as UFUNCTIONS so they can't be called from
//  blueprints to avoid any unexpected behaviour
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Tick
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Replicates variables for multiplayer
		virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//Math functions
		float Add(float Current, float Amount);
		float Remove(float Current, float Amount);
		float Change(float Current, float Amount);

	//Sound functions
		void HealthHitSound();
		void ShieldHitSound();
		void HealthLowSound();
		void ShieldLowSound();
		void DeathSound();
		void ShieldBreakSound();
		void StaminaLowSound();

	//Death functions
		void CheckForAndResetChecks();

	//Anim functions
		void HitAnim();
		void DeathAnim();

	//Sprinting functions
		void StartSprinting();
		void StopSprinting();

	//Damage functions
	//	float CalculateDamageBuffs(float baseamount, TArray<float> buffs);
		//float CalculateDamageDebuffs(float baseamount, TArray<float> debuffs);

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

	//Get Actor Location-
	// 
	//Get component owners location
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		FVector GetActorLocation();
	
	//Set Low Audio Components-
	// 
	//Set references to audio components added to your character/pawn
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Sound"))
		void SetLowAudioComponents(UAudioComponent* HealthAudioComponent, UAudioComponent* ShieldAudioComponent, UAudioComponent* StaminaAudioComponent);

	//Set Sounds-
	//
	//Sets our low audio component sounds to our declared sounds
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Sound"))
		void SetSounds();

	//Set Anim Instance-
	//
	//Sets reference to our owners anim instance
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Anims"))
		void SetAnimInstance(UAnimInstance* instance);

	//Check For Death-
	//
	//Returns if this Components health is 0
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Damage"))
		bool CheckForDeath();

	//Has Sheild-
	//
	//Returns if this Component has Shield
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		bool HasShield();

	//Has Health-
	//
	//Returns if this Component has Health
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		bool HasHealth();

	//Is Stat Full-
	//
	//Returns if the selected stat is at full value.
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		bool IsStatFull(StatsType stat);

	//Get Stat Value As Percentage-
	//
	//Returns the selected stat value as a percentage.
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		float GetStatValueAsPercentage(StatsType stat);

	//Get Current Stat Value-
	//
	//Returns the current Components selected Stat Value
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		float GetCurrentStatValue(StatsType stat);

	//Get Max Stat Value-
	//
	//Returns the Max Components Stat Value
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		float GetMaxStatValue(StatsType stat);

	//Get Stat Media-
	//
	//Returns a selected stats media
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		UTexture2D* GetStatIcon(StatsType stat);

	//Get Stat Media-
	//
	//Returns a selected stats media
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		FColor GetStatColor(StatsType stat);

	//Get Respawn Location-
	//
	//Rerturns this Components Respawn Location
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		FVector GetRespawnLocation();

	//Get Respawn Rotation-
	//
	//Returns this Components Respawn Rotation
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		FRotator GetRespawnRotation();

	//Get Can Be Damaged-
	//
	//Returns if this Component can be Damaged
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		bool GetCanBeDamaged();

	//Modifies Health-
	//
	//Add: Adds to Current Health
	//Remove: Removes from Current Health
	//Change: Changes the Current Health
	//
	//Add and Remove are Clamped to 0 and Max Health, Change value is not Clamped, Meaning it can go above and below 0 and Max Health
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyHealth(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Shield-
	//
	//Add: Adds to Current Shield
	//Remove: Removes from Current Shield
	//Change: Changes the Current Shield
	//
	//Add and Remove are Clamped to 0 and Max Shield, Change value is not Clamped, Meaning it can go above and below 0 and Max Shield
	//Does NOT remove overflow from Health
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyShield(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Stamina-
	//
	//Add: Adds to Current Stamina
	//Remove: Removes from Current Stamina
	//Change: Changes the Current Stamina
	//
	//Add and Remove are Clamped to 0 and Max Stamina, Change value is not Clamped, Meaning it can go above and below 0 and Max Stamina
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyStamina(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Resource-
	//
	//Add: Adds to Current Resource
	//Remove: Removes from Current Resource
	//Change: Changes the Current Resource
	//
	//Add and Remove are Clamped to 0 and Max Resource, Change value is not Clamped, Meaning it can go above and below 0 and Max Resource
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyResource(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Energy-
	//
	//Add: Adds to Current Energy
	//Remove: Removes from Current Energy
	//Change: Changes the Current Energy
	//
	//Add and Remove are Clamped to 0 and Max Energy, Change value is not Clamped, Meaning it can go above and below 0 and Max Energy
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyEnergy(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Hydration-
	//
	//Add: Adds to Current Hydration
	//Remove: Removes from Current Hydration
	//Change: Changes the Current Hydration
	//
	//Add and Remove are Clamped to 0 and Max Hydration, Change value is not Clamped, Meaning it can go above and below 0 and Max Hydration
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 3, Category = "Basic|Health|Modify"))
		void ModifyHydration(ChangeType ChangeType, float Amount, bool debug);

	//Modifies Movement-
	//
	//Walking: Sets speed to walking speed and starts stamina regen
	//Crouching: Sets speed to crouching speed and starts stamina regen (You must have "bCanCrouch" in your characters BP set to true for it to work properly)
	//Sprinting: Sets speed to sprinting speed and starts stamina decrease
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Modify"))
		void ModifyMovement(MovementType MovementType, bool debug);

	//Sprinting-
	//
	//This function gets bound to the sprinting timer to be looped
	//Wouldn't recommend calling on it's own, if you need to use sprint please see @ModifyMovement
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void Sprinting();

	//Add To Stat Overtime-
	//
	//Add to selected stat overtime
	//(Defaults are set in the components class default settings)
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, Category = "Basic|Health|Overtime"))
		void AddToStatOvertime(StatsType stat, bool debug);

	//Remove from Stat Overtime-
	//
	//Remove from selected stat overtime
	//(Defaults are set in the components class default settings)
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, Category = "Basic|Health|Overtime"))
		void RemoveFromStatOvertime(StatsType stat, bool debug);

	//Stop Stat Overtime Increase-
	//
	//Stops the selected Stat increase
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, Category = "Basic|Health|Overtime"))
		void StopStatOvertimeIncrease(StatsType stat);

	//Stop Stat Overtime Decrease-
	//
	//Stops the selected Stat decrease
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, Category = "Basic|Health|Overtime"))
		void StopStatOvertimeDecrease(StatsType stat);
	//Stop All Overtime Timers-
	// 
	//Stops all overtime effects
	UFUNCTION(BlueprintCallable, meta = (AdvancedDisplay = 1, Category = "Basic|Health|Overtime"))
		void StopAllOvertimeTimers();
	//Modifies Max Stat Value-
	//
	//Changes the Max value of the selected stat.
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Modify"))
		void ModifyMaxStatValue(StatsType Stat, float Amount);

	//Modifies Respawn Location and Rotation-
	//
	//Changes the Location and Rotation of this components owners respawn.
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Modify"))
		void ModifyRespawnLocationAndRotation(FVector Location, FRotator Rotation);

	//Set Can Be Damaged-
	//
	//Changes if this components owner can be damaged.
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Modify"))
		void SetCanBeDamaged(bool TakeDamage);

	//Set Overtime Values-
	//
	//Sets selected stats overtime values.
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Overtime"))
		void SetOvertimeValues(StatsType stat, float overtimeIncrease, float overtimeDecrease, float increaseRate, float DecreaseRate);

	//Get Overtime Values-
	//
	//Gets selected stats overtime values.
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		void GetOvertimeValues(StatsType stat, float& overtimeIncrease, float& overtimeDecrease, float& increaseRate, float& DecreaseRate);

	//Is Overtime Active-
	//
	//Get if selected stat overtime is active.
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		void IsOvertimeActive(StatsType stat, bool& IncreaseTimer, bool& DecreaseTimer);

	//Get Owner Type-
	//
	//Returns if the owner of this component is a player or AI
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		OwnerTypeHealth GetOwnerType();

	//Get Death Anim Length-
	//
	//Returns the length of the set death animation
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Get"))
		float GetDeathAnimLength();

	//Set Death Delay To Death Anim Length-
	//
	//Sets the components death delay to the length of the set death animation
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Anims"))
		void SetDeathDelayToDeathAnimLength();

	//Deal Damage-
	//
	//Starts with Shield and overflows to Health, Also checks for Death.
	//
	//CAN BIND TO ADD YOUR OWN FUNCTIONALITY FOR WIDGETS & ETC!
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Deal Damage", AdvancedDisplay = 1, Category = "Basic|Health|Damage"))
		void DealDamage(float Amount, bool Debug);
	
	//Calculate Damage-
	//
	//Returns the damage after buff/debuff calculations
	//UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Damage"))
		//float CalculateDamage(float baseamount, TArray<float> buffs, TArray<float> debuffs);

	//Set Values-
	//
	//Sets the values without and checks or bindable events.
	//Used for helping with loading attributes for a SaveGame object
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Save/Load"))
		void SetValues(FCYB_Values newhealth, FCYB_Values newshield, FCYB_Values newresource, FCYB_Values newstamina, FCYB_Values newenergy, FCYB_Values newhydration);

	//Get Values-
	//
	//Get the values without checks or bindable events.
	//Used for helping with saving attributes for a SaveGame object
	UFUNCTION(BlueprintPure, meta = (Category = "Basic|Health|Save/Load"))
		void GetValues(FCYB_Values& currenthealth, FCYB_Values& currentshield, FCYB_Values& currentresource, FCYB_Values& currentstamina, FCYB_Values& currentenergy, FCYB_Values& currenthydration);

	//Start Jumping-
	//
	//Starts jumping, works inline with unreals built in jump functions.
	//Removes stamina cost from stamina.
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void StartJumping();

	//Stop Jumping-
	//
	//Stops jumping, works inline with unreals built in jump functions.
	//Starts stamina regen if if "Walking".
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void StopJumping();

	//Handle Death-
	//
	//Starts death function, use this to kill the components owner instantly.
	//(Gets called in Deal Damage if health hits 0)
	//CAN BIND TO ADD YOUR OWN FUNCTIONALITY FOR WIDGETS & ETC!
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Damage"))
		void HandleDeath();

	//DeathRespawn-
	//
	//Handles death when respawning, gets called in @HandleDeath.
	//Wouldn't recommend calling on it's own
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void DeathRespawn();

	//DeathMenu-
	//
	//Handles death when going back to a menu, gets called in @HandleDeath.
	//Wouldn't recommend calling on it's own
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void DeathMenu();

	//DeathWidget
	//
	//Handles death when showing a widget, gets called in @HandleDeath.
	//Wouldn't recommend calling on it's own
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void DeathWidget();

	//DeathRespawn
	//
	//Handles death when destorying the actor, gets called in @HandleDeath.
	//Wouldn't recommend calling on it's own
	UFUNCTION(BlueprintCallable, meta = (Category = "Basic|Health|Misc"))
		void DeathDestroy();

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

	//On Deal Damage-
	//
	//A bindable event that fires when the component takes damage.
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnDamageEvent OnDealDamage;
	//On Handle Death-
	//
	//A bindable event that fires when the component dies
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnDeathEvent OnHandleDeath;

	//On Modify
	//
	//A bindable event that fires when one of the modify nodes are being used
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyHealth OnModifyHealth;
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyShield OnModifyShield;
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyStamina OnModifyStamina;
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyResource OnModifyResource;
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyEnergy OnModifyEnergy;
	UPROPERTY(BlueprintAssignable, Category = "Basic|Health|BindableEvents")
		FOnModifyHydration OnModifyHydration;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//End of Bindable events
////////////////////////////////////////////////////////////////////////////////////////////////////////
};