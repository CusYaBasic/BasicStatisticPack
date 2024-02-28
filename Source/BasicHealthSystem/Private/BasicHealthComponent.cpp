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


#include "BasicHealthComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Runtime\Engine\Classes\Kismet\GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UBasicHealthComponent::UBasicHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBasicHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UBasicHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBasicHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicates our variables for multiplayer
	DOREPLIFETIME(UBasicHealthComponent, Type);
	DOREPLIFETIME(UBasicHealthComponent, OnDeath);
	DOREPLIFETIME(UBasicHealthComponent, DeathValues);
	DOREPLIFETIME(UBasicHealthComponent, Health);
	DOREPLIFETIME(UBasicHealthComponent, Shield);
	DOREPLIFETIME(UBasicHealthComponent, Stamina);
	DOREPLIFETIME(UBasicHealthComponent, Resource);
	DOREPLIFETIME(UBasicHealthComponent, Energy);
	DOREPLIFETIME(UBasicHealthComponent, Hydration);
	DOREPLIFETIME(UBasicHealthComponent, Checks);
	DOREPLIFETIME(UBasicHealthComponent, Sounds);
	DOREPLIFETIME(UBasicHealthComponent, Anims);
	DOREPLIFETIME(UBasicHealthComponent, Movement);
	DOREPLIFETIME(UBasicHealthComponent, Media);
	DOREPLIFETIME(UBasicHealthComponent, HealthLowAudioComponent);
	DOREPLIFETIME(UBasicHealthComponent, StaminaLowAudioComponent);
	DOREPLIFETIME(UBasicHealthComponent, TimerHandles);
	DOREPLIFETIME(UBasicHealthComponent, TimerDels);
}

float UBasicHealthComponent::Add(float Current, float Amount)
{
	Current = Current + Amount;
	return Current;
}

float UBasicHealthComponent::Remove(float Current, float Amount)
{
	Current = Current - Amount;
	return Current;
}

float UBasicHealthComponent::Change(float Current, float Amount)
{
	Current = Amount;
	return Current;
}

void UBasicHealthComponent::DeathRespawn()
{
	//Get a reference to the components owner
	AActor* player = GetOwner();

	//Check if we're using death anims, if so play anim
	if (Anims.PlayDeathAnim)
	{
		DeathAnim();
	}
	//Move components owner to new location
	player->SetActorLocationAndRotation(GetRespawnLocation(), GetRespawnRotation(), false, 0, ETeleportType::None);

	//Stop our overtime increase/decrease
	StopAllOvertimeTimers();

	//Check if we're resetting our stats on death and if so reset them
	CheckForAndResetChecks();
}

void UBasicHealthComponent::DeathMenu()
{
	//Opens declared menu map
	UGameplayStatics::OpenLevel(GetWorld(), DeathValues.MainMenuLevelName);
}

void UBasicHealthComponent::DeathDestroy()
{
	//Get a reference to the components owner
	AActor* player = GetOwner();

	//Check if our owner is valid, is so destroy it
	if (IsValid(player) == true)
	{
		player->Destroy();
	}
}

void UBasicHealthComponent::DeathWidget()
{
	//Checks if our widget is valid, if so move it to the declared screen pos and add it to the viewport
	if (IsValid(DeathValues.Widget))
	{
		DeathValues.Widget->SetPositionInViewport(DeathValues.WidgetPos);
		DeathValues.Widget->AddToViewport(0);
	}
}

void UBasicHealthComponent::HealthHitSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(Sounds.HealthHitSound) == true && Sounds.PlayHealthHitSound == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sounds.HealthHitSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}
}

void UBasicHealthComponent::ShieldHitSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(Sounds.ShieldHitSound) == true && Sounds.PlayShieldHitSound == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Sounds.ShieldHitSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}
}

void UBasicHealthComponent::HealthLowSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(Sounds.HealthLowSound) == true && IsValid(HealthLowAudioComponent) == true && Sounds.PlayHealthLowSound == true)
	{
		HealthLowAudioComponent->Play();
	}
}

void UBasicHealthComponent::ShieldLowSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(Sounds.ShieldLowSound) == true && IsValid(ShieldLowAudioComponent) == true && Sounds.PlayShieldLowSound == true)
	{
		ShieldLowAudioComponent->Play();
	}
}

void UBasicHealthComponent::StaminaLowSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(Sounds.StaminaLowSound) == true && IsValid(StaminaLowAudioComponent) == true && Sounds.PlayStaminaLowSound == true)
	{
		StaminaLowAudioComponent->Play();
	}
}

void UBasicHealthComponent::DeathSound()
{
	//Check if our sound que is set and if we are playing sounds
	if (IsValid(HealthLowAudioComponent) == true && IsValid(Sounds.DeathSound) == true)
	{
		//We use the same component for our death sound as we do our low health, we just change the sound which gets changed back when death gets handled
		HealthLowAudioComponent->Stop();
		HealthLowAudioComponent->SetSound(Sounds.DeathSound);
		HealthLowAudioComponent->Play();
	}
}

void UBasicHealthComponent::ShieldBreakSound()
{
	//Plays sound at the components owners location
	UGameplayStatics::PlaySoundAtLocation(this, Sounds.ShieldBreakSound, GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
}

void UBasicHealthComponent::HitAnim()
{
	//Check if our anim instance and hit anim is valid and if so, play hit anim
	if (IsValid(Anims.AnimInstance) && IsValid(Anims.HitAnim))
	{
		Anims.AnimInstance->Montage_Play(Anims.HitAnim, 1.0f);
	}
}

void UBasicHealthComponent::DeathAnim()
{
	//Check if our anim instance and death anim is valid and if so, play death anim
	if (IsValid(Anims.AnimInstance) && IsValid(Anims.DeathAnim))
	{
		Anims.AnimInstance->Montage_Play(Anims.DeathAnim, 1.0f);
	}
}

void UBasicHealthComponent::SetLowAudioComponents(UAudioComponent* HealthAudioComponent, UAudioComponent* ShieldAudioComponent, UAudioComponent* StaminaAudioComponent)
{
	//Check if our components are valid and if so, set references to them
	if (IsValid(HealthAudioComponent) == true)
	{
		HealthLowAudioComponent = HealthAudioComponent;
	}
	if (IsValid(ShieldAudioComponent) == true)
	{
		ShieldLowAudioComponent = ShieldAudioComponent;
	}
	if (IsValid(StaminaAudioComponent) == true)
	{
		StaminaLowAudioComponent = StaminaAudioComponent;
	}
	//Once we have our refenences we can set our sound ques
	SetSounds();
}

void UBasicHealthComponent::SetSounds()
{
	//Check if our sound que is set and our component is valid, if so set components sound 
	if (IsValid(Sounds.HealthLowSound) == true && IsValid(HealthLowAudioComponent) == true)
	{
		HealthLowAudioComponent->SetSound(Sounds.HealthLowSound);
	}
	if (IsValid(Sounds.ShieldLowSound) == true && IsValid(ShieldLowAudioComponent) == true)
	{
		ShieldLowAudioComponent->SetSound(Sounds.ShieldLowSound);
	}
	if (IsValid(Sounds.StaminaLowSound) == true && IsValid(StaminaLowAudioComponent) == true)
	{
		StaminaLowAudioComponent->SetSound(Sounds.StaminaLowSound);
	}
}

void UBasicHealthComponent::SetAnimInstance(UAnimInstance* instance)
{
	//Sets our anim instance reference, needed to play anims
	if (IsValid(instance) == true)
	{
		Anims.AnimInstance = instance;
	}
}

FVector UBasicHealthComponent::GetActorLocation()
{
	//Gets location of the components actor
	return GetOwner()->GetActorLocation();
}

bool UBasicHealthComponent::CheckForDeath()
{
	//Checks if our health is 0
	if (GetCurrentStatValue(StatsType::Health_H) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBasicHealthComponent::HasShield()
{
	//Checks if our shield is 0
	if (Shield.Current > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBasicHealthComponent::HasHealth()
{
	//Checks if our health is 0
	if (Health.Current > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBasicHealthComponent::IsStatFull(StatsType stat)
{
	//We use a enum to change flow
	switch (stat)
	{

	//If enum equals health
	case StatsType::Health_H:

		//Check if current health is equal to max health
		if (Health.Current == Health.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	//If enum equals shield
	case StatsType::Shield_H:

		//Check if current shield is equal to max shield
		if (Shield.Current == Shield.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	//If enum equals stamina
	case StatsType::Stamina_H:

		//Checks if current stamina is equal to max stamina
		if (Stamina.Current == Stamina.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	//If enum equals resource
	case StatsType::Resource_H:

		//Checks if current resource is equal to max resource
		if (Resource.Current == Resource.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	//If enum equals energy
	case StatsType::Energy_H:

		//Checks if current energy is equal to max energy
		if (Energy.Current == Energy.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	
	//If enum equals hydration
	case StatsType::Hydration_H:

		//Checks if current hydration is equal to max hydration
		if (Hydration.Current == Hydration.Max)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	default:
		return false;
		break;
	}
}

float UBasicHealthComponent::GetStatValueAsPercentage(StatsType stat)
{
	//We use a enum to change the flow
	switch (stat)
	{
	case StatsType::Health_H:
		return Health.Current / Health.Max * 100;
		break;

	case StatsType::Shield_H:
		return Shield.Current / Shield.Max * 100;
		break;

	case StatsType::Stamina_H:
		return Stamina.Current / Stamina.Max * 100;
		break;

	case StatsType::Resource_H:
		return Resource.Current / Resource.Max * 100;
		break;

	case StatsType::Energy_H:
		return Energy.Current / Energy.Max * 100;
		break;

	case StatsType::Hydration_H:
		return Hydration.Current / Hydration.Max * 100;
		break;

	default:
		return Health.Current / Health.Max * 100;
		break;
	}
}

float UBasicHealthComponent::GetMaxStatValue(StatsType stat)
{
	//We use a enum to change the flow
	switch (stat)
	{
	case StatsType::Health_H:
		return Health.Max;
		break;

	case StatsType::Shield_H:
		return Shield.Max;
		break;

	case StatsType::Stamina_H:
		return Stamina.Max;
		break;

	case StatsType::Resource_H:
		return Resource.Max;
		break;

	case StatsType::Energy_H:
		return Energy.Max;
		break;

	case StatsType::Hydration_H:
		return Hydration.Max;
		break;
	default:
		return Health.Max;
		break;
	}
}

float UBasicHealthComponent::GetCurrentStatValue(StatsType stat)
{
	//We use a enum to change the flow
	switch (stat)
	{
	case StatsType::Health_H:
		return Health.Current;
		break;

	case StatsType::Shield_H:
		return Shield.Current;
		break;

	case StatsType::Stamina_H:
		return Stamina.Current;
		break;

	case StatsType::Resource_H:
		return Resource.Current;
		break;

	case StatsType::Energy_H:
		return Energy.Current;
		break;

	case StatsType::Hydration_H:
		return Hydration.Current;
		break;
	default:
		return Health.Current;
		break;
	}
}

UTexture2D* UBasicHealthComponent::GetStatIcon(StatsType stat)
{
	//We use a enum to change the flow
	switch (stat)
	{
	case StatsType::Health_H:
		return Media.HealthMedia.Icon;
		break;

	case StatsType::Shield_H:
		return Media.ShieldMedia.Icon;
		break;

	case StatsType::Resource_H:
		return Media.ResourceMedia.Icon;
		break;

	case StatsType::Stamina_H:
		return Media.StaminaMedia.Icon;
		break;

	case StatsType::Energy_H:
		return Media.EnergyMedia.Icon;
		break;

	case StatsType::Hydration_H:
		return Media.HydrationMedia.Icon;
		break;
	default:
		return Media.HealthMedia.Icon;
		break;
	}
}

FColor UBasicHealthComponent::GetStatColor(StatsType stat)
{
	//We use a enum to change the flow
	switch (stat)
	{
	case StatsType::Health_H:
		return Media.HealthMedia.Color;
		break;

	case StatsType::Shield_H:
		return Media.ShieldMedia.Color;
		break;

	case StatsType::Resource_H:
		return Media.ResourceMedia.Color;
		break;

	case StatsType::Stamina_H:
		return Media.StaminaMedia.Color;
		break;

	case StatsType::Energy_H:
		return Media.EnergyMedia.Color;
		break;

	case StatsType::Hydration_H:
		return Media.HydrationMedia.Color;
		break;
	default:
		return Media.HealthMedia.Color;
		break;
	}
}

FVector UBasicHealthComponent::GetRespawnLocation()
{
	return DeathValues.RespawnLocation;
}

FRotator UBasicHealthComponent::GetRespawnRotation()
{
	return DeathValues.RespawnRotation;
}

bool UBasicHealthComponent::GetCanBeDamaged()
{
	return Checks.CanBeDamaged;
}

void UBasicHealthComponent::ModifyHealth(ChangeType ChangeType, float Amount, bool debug)
{
	//We want to store our old health value before we make any changes so we can pass it to our bindable event
	float oldhealth = GetCurrentStatValue(StatsType::Health_H);

	//We use a enum to switch our flow
	switch (ChangeType)
	{

	//If our enum equals add
	case ChangeType::Add_H:

		//Add amount to health, clamped at max health
		Health.Current = FMath::Clamp(Add(Health.Current, Amount), 0.f, Health.Max);

		//If our health percentage is higher than the percentage declared in our sound struct stop playing our low health sound
		if (GetStatValueAsPercentage(StatsType::Health_H) > Sounds.HealthLowPercentage && IsValid(HealthLowAudioComponent) == true)
		{
			HealthLowAudioComponent->Stop();
		}
		break;

	//If our enum equals remove
	case ChangeType::Remove_H:
		//Remove amount from health, clamped to 0
		Health.Current = FMath::Clamp(Remove(Health.Current, Amount), 0.f, Health.Max);
		//Check if we died due to our health decrease timer
		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.HealthDecrease) && CheckForDeath())
		{
			HandleDeath();
		}
		break;

	//If our enum equals change
	case ChangeType::Change_H:
		//Change health to amount
		Health.Current = Change(Health.Current, Amount);
		break;
	}
	//If debug equals true, print a debug message to screen
	if (debug == true)
	{
		FString HealthString = "Health Was:" + FString::SanitizeFloat(oldhealth) + " " + "Current Health Is Now: " + FString::SanitizeFloat(Health.Current) + " " + "Health Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, HealthString);
	}
	//Fires bindable event which we can add logic to using blueprints
	OnModifyHealth.Broadcast(ChangeType, Amount, oldhealth, GetCurrentStatValue(StatsType::Health_H));
}


void UBasicHealthComponent::ModifyShield(ChangeType ChangeType, float Amount, bool debug)
{
	//We want to store our old shield value before we make any changes so we can pass it to our bindable event
	float oldshield = GetCurrentStatValue(StatsType::Shield_H);
	//We use a enum to change flow
	switch (ChangeType)
	{
	//If our enum equals add
	case ChangeType::Add_H:
		//Add amount to current shield, clamped at max health
		Shield.Current = FMath::Clamp(Add(Shield.Current, Amount), 0.f, Shield.Max);
		//Check if our sheild is abouve sheild low perentage if so, stop low shield sound
		if (GetStatValueAsPercentage(StatsType::Shield_H) > Sounds.ShieldLowPercentage && IsValid(ShieldLowAudioComponent) == true)
		{
			ShieldLowAudioComponent->Stop();
		}
		break;

	//If our enum equals remove
	case ChangeType::Remove_H:
		Shield.Current = FMath::Clamp(Remove(Shield.Current, Amount), 0.f, Shield.Max);
		break;

	//
	case ChangeType::Change_H:
		Shield.Current = Change(Shield.Current, Amount);
		break;
	}
	//
	if (debug == true)
	{
		FString ShieldString = "Current Shield Is Now: " + FString::SanitizeFloat(Shield.Current) + " " + "Shield Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, ShieldString);
	}
	//Fires bindable event which we can add logic to using blueprints
	OnModifyShield.Broadcast(ChangeType, Amount, oldshield, GetCurrentStatValue(StatsType::Shield_H));
}

void UBasicHealthComponent::ModifyStamina(ChangeType ChangeType, float Amount, bool debug)
{
	//
	float oldstamina = GetCurrentStatValue(StatsType::Stamina_H);
	//
	switch (ChangeType)
	{
	//
	case ChangeType::Add_H:
		//
		Stamina.Current = FMath::Clamp(Add(Stamina.Current, Amount), 0.f, Stamina.Max);
		//
		if (GetStatValueAsPercentage(StatsType::Stamina_H) > Sounds.StaminaLowPercentage && IsValid(HealthLowAudioComponent) == true)
		{
			StaminaLowAudioComponent->Stop();
		}
		//
		if (IsStatFull(StatsType::Stamina_H))
		{
			StopStatOvertimeIncrease(StatsType::Stamina_H);
		}
		break;

	//
	case ChangeType::Remove_H:
		//
		Stamina.Current = FMath::Clamp(Remove(Stamina.Current, Amount), 0.f, Stamina.Max);
		//
		if (GetStatValueAsPercentage(StatsType::Stamina_H) <= Sounds.StaminaLowPercentage)
		{
			StaminaLowSound();
		}
		break;

	//
	case ChangeType::Change_H:
		//
		Stamina.Current = Change(Stamina.Current, Amount);
		break;
	}
	//
	if (debug == true)
	{
		FString StaminaString = "Current Stamina Is Now: " + FString::SanitizeFloat(Stamina.Current) + " " + "Stamina Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, StaminaString);
	}
	//Fires bindable event which we can add logic to using blueprints
	OnModifyStamina.Broadcast(ChangeType, Amount, oldstamina, GetCurrentStatValue(StatsType::Shield_H));
}

void UBasicHealthComponent::ModifyResource(ChangeType ChangeType, float Amount, bool debug)
{

	float oldresource = GetCurrentStatValue(StatsType::Resource_H);

	switch (ChangeType)
	{
	case ChangeType::Add_H:
		Resource.Current = FMath::Clamp(Add(Resource.Current, Amount), 0.f, Resource.Max);
		break;
	case ChangeType::Remove_H:
		Resource.Current = FMath::Clamp(Remove(Resource.Current, Amount), 0.f, Resource.Max);
		break;
	case ChangeType::Change_H:
		Resource.Current = Change(Resource.Current, Amount);
		break;
	}

	if (debug == true)
	{
		FString ResourceString = "Current Resource Is Now: " + FString::SanitizeFloat(Resource.Current) + " " + "Resource Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, ResourceString);
	}

	//Fires bindable event which we can add logic to using blueprints
	OnModifyResource.Broadcast(ChangeType, Amount, oldresource, GetCurrentStatValue(StatsType::Shield_H));

}

void UBasicHealthComponent::ModifyEnergy(ChangeType ChangeType, float Amount, bool debug)
{

	float oldenergy = GetCurrentStatValue(StatsType::Energy_H);

	switch (ChangeType)
	{
	case ChangeType::Add_H:
		Energy.Current = FMath::Clamp(Add(Energy.Current, Amount), 0.f, Energy.Max);
		break;
	case ChangeType::Remove_H:
		Energy.Current = FMath::Clamp(Remove(Energy.Current, Amount), 0.f, Energy.Max);
		break;
	case ChangeType::Change_H:
		Energy.Current = Change(Energy.Current, Amount);
		break;
	}

	if (debug == true)
	{
		FString EnergyString = "Current Energy Is Now: " + FString::SanitizeFloat(Energy.Current) + " " + "Energy Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, EnergyString);
	}

	//Fires bindable event which we can add logic to using blueprints
	OnModifyEnergy.Broadcast(ChangeType, Amount, oldenergy, GetCurrentStatValue(StatsType::Shield_H));

}

void UBasicHealthComponent::ModifyHydration(ChangeType ChangeType, float Amount, bool debug)
{

	float oldhydration = GetCurrentStatValue(StatsType::Hydration_H);

	switch (ChangeType)
	{
	case ChangeType::Add_H:
		Hydration.Current = FMath::Clamp(Add(Hydration.Current, Amount), 0.f, Hydration.Max);
		break;
	case ChangeType::Remove_H:
		Hydration.Current = FMath::Clamp(Remove(Hydration.Current, Amount), 0.f, Hydration.Max);
		break;
	case ChangeType::Change_H:
		Hydration.Current = Change(Hydration.Current, Amount);
		break;
	}

	if (debug == true)
	{
		FString HydrationString = "Current Hydration Is Now: " + FString::SanitizeFloat(Hydration.Current) + " " + "Hydration Changed By: " + FString::SanitizeFloat(Amount) + " ";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, HydrationString);
	}

	//Fires bindable event which we can add logic to using blueprints
	OnModifyHydration.Broadcast(ChangeType, Amount, oldhydration, GetCurrentStatValue(StatsType::Shield_H));

}

void UBasicHealthComponent::ModifyMovement(MovementType MovementType, bool debug)
{

	ACharacter* OtherActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Movement.Movement = MovementType;
	if (IsValid(OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
	{

		UCharacterMovementComponent* comp = Cast<UCharacterMovementComponent>(OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass()));

		switch (Movement.Movement)
		{

		case MovementType::Walking_H:
			StopSprinting();
			if (IsValid(comp))
			{
				comp->MaxWalkSpeed = Movement.WalkingSpeed;
				if (comp->IsCrouching())
				{
					OtherActor->UnCrouch();
				}
			}
			break;

		case MovementType::Crouching_H:
			StopSprinting();
			if (IsValid(comp))
			{
				OtherActor->Crouch();
				comp->MaxWalkSpeedCrouched = Movement.CrouchingSpeed;
			}
			break;

		case MovementType::Sprinting_H:

			if (IsValid(comp))
			{
				if (comp->IsCrouching())
				{
					OtherActor->UnCrouch();
				}
				if (GetCurrentStatValue(StatsType::Stamina_H) >= Movement.MinSprintStamina)
				{
					comp->MaxWalkSpeed = Movement.SprintingSpeed;
					StopStatOvertimeIncrease(StatsType::Stamina_H);
					StartSprinting();
				}
			}
			break;
		}

	}

}

void UBasicHealthComponent::StartSprinting()
{
	StopStatOvertimeIncrease(StatsType::Stamina_H);
	TimerDels.SprintingDecrease.BindUFunction(this, FName("Sprinting"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandles.SprintingDecrease, TimerDels.SprintingDecrease, Stamina.DecreaseRate, true);
}

void UBasicHealthComponent::Sprinting()
{

	AActor* OtherActor = GetOwner();

	if (OtherActor->GetVelocity().Size() > 0.0f)
	{
		Stamina.Current = FMath::Clamp(Remove(Stamina.Current, Stamina.OvertimeDecrease), 0.f, Stamina.Max);
	}
	else
	{
		Stamina.Current = FMath::Clamp(Add(Stamina.Current, Stamina.OvertimeIncrease), 0.f, Stamina.Max);
	}
	if (GetCurrentStatValue(StatsType::Stamina_H) == 0)
	{
		ModifyMovement(MovementType::Walking_H, false);
	}

}

void UBasicHealthComponent::StopSprinting()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandles.SprintingDecrease);
	AddToStatOvertime(StatsType::Stamina_H, false);
}


void UBasicHealthComponent::StartJumping()
{
	if (Stamina.Current > Movement.JumpStaminaCost)
	{
		ACharacter* OtherActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (IsValid(OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
		{
			ModifyStamina(ChangeType::Remove_H, Movement.JumpStaminaCost, false);
			OtherActor->Jump();
		}
	}
}

void UBasicHealthComponent::StopJumping()
{

	if (Movement.Movement == MovementType::Walking_H)
	{
		AddToStatOvertime(StatsType::Stamina_H, false);
	}

	ACharacter* OtherActor = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (IsValid(OtherActor->GetComponentByClass(UCharacterMovementComponent::StaticClass())))
	{
		OtherActor->StopJumping();
	}


}

// HEY you! Yeah YOU..!! You're Beautiful <3

void UBasicHealthComponent::AddToStatOvertime(StatsType stat, bool debug)
{
	switch (stat)
	{
	case StatsType::Health_H:
		TimerDels.HealthIncrease.BindUFunction(this, FName("ModifyHealth"), ChangeType::Add_H, Health.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.HealthIncrease, TimerDels.HealthIncrease, Health.IncreaseRate, true);
		break;

	case StatsType::Shield_H:
		TimerDels.ShieldIncrease.BindUFunction(this, FName("ModifyShield"), ChangeType::Add_H, Shield.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.ShieldIncrease, TimerDels.ShieldIncrease, Shield.IncreaseRate, true);
		break;

	case StatsType::Stamina_H:
		TimerDels.StaminaIncrease.BindUFunction(this, FName("ModifyStamina"), ChangeType::Add_H, Stamina.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.StaminaIncrease, TimerDels.StaminaIncrease, Stamina.IncreaseRate, true);
		break;

	case StatsType::Resource_H:
		TimerDels.ResourceIncrease.BindUFunction(this, FName("ModifyResource"), ChangeType::Add_H, Resource.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.ResourceIncrease, TimerDels.ResourceIncrease, Resource.IncreaseRate, true);
		break;

	case StatsType::Energy_H:
		TimerDels.EnergyIncrease.BindUFunction(this, FName("ModifyEnergy"), ChangeType::Add_H, Energy.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.EnergyIncrease, TimerDels.EnergyIncrease, Energy.IncreaseRate, true);
		break;

	case StatsType::Hydration_H:
		TimerDels.HydrationIncrease.BindUFunction(this, FName("ModifyHydration"), ChangeType::Add_H, Hydration.OvertimeIncrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.HydrationIncrease, TimerDels.HydrationIncrease, Hydration.IncreaseRate, true);
		break;
	}
}

void UBasicHealthComponent::RemoveFromStatOvertime(StatsType stat, bool debug)
{
	switch (stat)
	{
	case StatsType::Health_H:
		TimerDels.HealthDecrease.BindUFunction(this, FName("ModifyHealth"), ChangeType::Remove_H, Health.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.HealthDecrease, TimerDels.HealthDecrease, Health.DecreaseRate, true);
		break;

	case StatsType::Shield_H:
		TimerDels.ShieldDecrease.BindUFunction(this, FName("ModifyShield"), ChangeType::Remove_H, Shield.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.ShieldDecrease, TimerDels.ShieldDecrease, Shield.DecreaseRate, true);
		break;

	case StatsType::Stamina_H:
		TimerDels.StaminaDecrease.BindUFunction(this, FName("ModifyStamina"), ChangeType::Remove_H, Stamina.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.StaminaDecrease, TimerDels.StaminaDecrease, Stamina.DecreaseRate, true);
		break;

	case StatsType::Resource_H:
		TimerDels.ResourceDecrease.BindUFunction(this, FName("ModifyResource"), ChangeType::Remove_H, Resource.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.ResourceDecrease, TimerDels.ResourceDecrease, Resource.DecreaseRate, true);
		break;

	case StatsType::Energy_H:
		TimerDels.EnergyDecrease.BindUFunction(this, FName("ModifyEnergy"), ChangeType::Remove_H, Energy.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.EnergyDecrease, TimerDels.EnergyDecrease, Energy.DecreaseRate, true);
		break;

	case StatsType::Hydration_H:
		TimerDels.HydrationDecrease.BindUFunction(this, FName("ModifyHydration"), ChangeType::Remove_H, Hydration.OvertimeDecrease, 0.f, debug);
		GetWorld()->GetTimerManager().SetTimer(TimerHandles.HydrationDecrease, TimerDels.HydrationDecrease, Hydration.DecreaseRate, true);
		break;
	}
}

void UBasicHealthComponent::StopStatOvertimeIncrease(StatsType stat)
{

	switch (stat)
	{

	case StatsType::Health_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.HealthIncrease);
		break;

	case StatsType::Shield_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.ShieldIncrease);
		break;

	case StatsType::Stamina_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.StaminaIncrease);
		break;

	case StatsType::Resource_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.ResourceIncrease);
		break;

	case StatsType::Energy_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.EnergyIncrease);
		break;

	case StatsType::Hydration_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.HydrationIncrease);
		break;

	}
}

void UBasicHealthComponent::StopStatOvertimeDecrease(StatsType stat)
{

	switch (stat)
	{

	case StatsType::Health_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.HealthDecrease);
		break;

	case StatsType::Shield_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.ShieldDecrease);
		break;

	case StatsType::Stamina_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.StaminaDecrease);
		break;

	case StatsType::Resource_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.ResourceDecrease);
		break;

	case StatsType::Energy_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.EnergyDecrease);
		break;

	case StatsType::Hydration_H:
		GetWorld()->GetTimerManager().ClearTimer(TimerHandles.HydrationDecrease);
		break;

	}

}

void UBasicHealthComponent::ModifyMaxStatValue(StatsType stat, float Amount)
{
	//Change our max stat value
	switch (stat)
	{

	case StatsType::Health_H:
		Health.Max = Amount;
		break;

	case StatsType::Shield_H:
		Shield.Max = Amount;
		break;

	case StatsType::Stamina_H:
		Stamina.Max = Amount;
		break;

	case StatsType::Resource_H:
		Resource.Max = Amount;
		break;

	case StatsType::Energy_H:
		Energy.Max = Amount;
		break;

	case StatsType::Hydration_H:
		Hydration.Max = Amount;
		break;

	}

	//MaxValue = Amount;
}

void UBasicHealthComponent::ModifyRespawnLocationAndRotation(FVector Location, FRotator Rotation)
{
	//Change our respawn location
	DeathValues.RespawnLocation = Location;
	DeathValues.RespawnRotation = Rotation;
}

void UBasicHealthComponent::SetCanBeDamaged(bool TakeDamage)
{
	//Change if we can take damage
	Checks.CanBeDamaged = TakeDamage;
}

void UBasicHealthComponent::SetOvertimeValues(StatsType stat, float overtimeIncrease, float overtimeDecrease, float increaseRate, float DecreaseRate)
{
	//Sets our overtime values
	switch (stat)
	{

	case StatsType::Health_H:
		Health.OvertimeIncrease = overtimeIncrease;
		Health.OvertimeDecrease = overtimeDecrease;
		Health.IncreaseRate = increaseRate;
		Health.DecreaseRate = DecreaseRate;
		break;

	case StatsType::Shield_H:
		Shield.OvertimeIncrease = overtimeIncrease;
		Shield.OvertimeDecrease = overtimeDecrease;
		Shield.IncreaseRate = increaseRate;
		Shield.DecreaseRate = DecreaseRate;
		break;

	case StatsType::Stamina_H:
		Stamina.OvertimeIncrease = overtimeIncrease;
		Stamina.OvertimeDecrease = overtimeDecrease;
		Stamina.IncreaseRate = increaseRate;
		Stamina.DecreaseRate = DecreaseRate;
		break;

	case StatsType::Resource_H:
		Resource.OvertimeIncrease = overtimeIncrease;
		Resource.OvertimeDecrease = overtimeDecrease;
		Resource.IncreaseRate = increaseRate;
		Resource.DecreaseRate = DecreaseRate;
		break;

	case StatsType::Energy_H:
		Energy.OvertimeIncrease = overtimeIncrease;
		Energy.OvertimeDecrease = overtimeDecrease;
		Energy.IncreaseRate = increaseRate;
		Energy.DecreaseRate = DecreaseRate;
		break;

	case StatsType::Hydration_H:
		Hydration.OvertimeIncrease = overtimeIncrease;
		Hydration.OvertimeDecrease = overtimeDecrease;
		Hydration.IncreaseRate = increaseRate;
		Hydration.DecreaseRate = DecreaseRate;
		break;
	}

}

void UBasicHealthComponent::GetOvertimeValues(StatsType stat, float& overtimeIncrease, float& overtimeDecrease, float& increaseRate, float& DecreaseRate)
{
	//Returns our ovetime values
	switch (stat)
	{

	case StatsType::Health_H:
		overtimeIncrease = Health.OvertimeIncrease;
		overtimeDecrease = Health.OvertimeDecrease;
		increaseRate = Health.IncreaseRate;
		DecreaseRate = Health.DecreaseRate;
		break;

	case StatsType::Shield_H:
		overtimeIncrease = Shield.OvertimeIncrease;
		overtimeDecrease = Shield.OvertimeDecrease;
		increaseRate = Shield.IncreaseRate;
		DecreaseRate = Shield.DecreaseRate;
		break;

	case StatsType::Stamina_H:
		overtimeIncrease = Stamina.OvertimeIncrease;
		overtimeDecrease = Stamina.OvertimeDecrease;
		increaseRate = Stamina.IncreaseRate;
		DecreaseRate = Stamina.DecreaseRate;
		break;

	case StatsType::Resource_H:
		overtimeIncrease = Resource.OvertimeIncrease;
		overtimeDecrease = Resource.OvertimeDecrease;
		increaseRate = Resource.IncreaseRate;
		DecreaseRate = Resource.DecreaseRate;
		break;

	case StatsType::Energy_H:
		overtimeIncrease = Energy.OvertimeIncrease;
		overtimeDecrease = Energy.OvertimeDecrease;
		increaseRate = Energy.IncreaseRate;
		DecreaseRate = Energy.DecreaseRate;
		break;

	case StatsType::Hydration_H:
		overtimeIncrease = Hydration.OvertimeIncrease;
		overtimeDecrease = Hydration.OvertimeDecrease;
		increaseRate = Hydration.IncreaseRate;
		DecreaseRate = Hydration.DecreaseRate;
break;

	}

}

void UBasicHealthComponent::IsOvertimeActive(StatsType stat, bool& IncreaseTimer, bool& DecreaseTimer)
{

	//Check if we currently have any overtime timers running
	switch (stat)
	{

	case StatsType::Health_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.HealthIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.HealthDecrease);
		break;

	case StatsType::Shield_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.ShieldIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.ShieldDecrease);
		break;

	case StatsType::Stamina_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.StaminaIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.StaminaDecrease);
		break;

	case StatsType::Resource_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.ResourceIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.ResourceDecrease);
		break;

	case StatsType::Energy_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.EnergyIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.EnergyDecrease);
		break;

	case StatsType::Hydration_H:
		IncreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.HydrationIncrease);
		DecreaseTimer = GetWorld()->GetTimerManager().IsTimerActive(TimerHandles.HydrationDecrease);
		break;

	}

}

void UBasicHealthComponent::StopAllOvertimeTimers()
{
	//Stop increase
	StopStatOvertimeIncrease(StatsType::Health_H);
	StopStatOvertimeIncrease(StatsType::Shield_H);
	StopStatOvertimeIncrease(StatsType::Resource_H);
	StopStatOvertimeIncrease(StatsType::Stamina_H);
	StopStatOvertimeIncrease(StatsType::Energy_H);
	StopStatOvertimeIncrease(StatsType::Hydration_H);

	//Stop decrease
	StopStatOvertimeDecrease(StatsType::Health_H);
	StopStatOvertimeDecrease(StatsType::Shield_H);
	StopStatOvertimeDecrease(StatsType::Resource_H);
	StopStatOvertimeDecrease(StatsType::Stamina_H);
	StopStatOvertimeDecrease(StatsType::Energy_H);
	StopStatOvertimeDecrease(StatsType::Hydration_H);
}

OwnerTypeHealth UBasicHealthComponent::GetOwnerType()
{
	return Type;
}

void UBasicHealthComponent::CheckForAndResetChecks()
{
	//Check if we are resetting our values back to default on death
	if (Checks.ResetHealth)
	{
		Health.Current = Health.Max;
	}
	if (Checks.ResetShield)
	{
		Shield.Current = Shield.Max;
	}
	if (Checks.ResetStamina)
	{
		Stamina.Current = Stamina.Max;
	}
	if (Checks.ResetResource)
	{
		Resource.Current = Resource.Max;
	}
	if (Checks.ResetEnergy)
	{
		Energy.Current = Energy.Max;
	}
	if (Checks.ResetHydration)
	{
		Hydration.Current = Hydration.Max;
	}

}

float UBasicHealthComponent::GetDeathAnimLength()
{

	//Returns the length of time the anim plays
	return Anims.DeathAnim->GetPlayLength();

}

void UBasicHealthComponent::SetDeathDelayToDeathAnimLength()
{
	
	//Sets our death delay to our anim length so our anim finishes before firing our death function
	DeathValues.DeathDelay = GetDeathAnimLength();

}

void UBasicHealthComponent::DealDamage(float Amount, bool Debug)
{
	//Checks if our component can take damage
	if (Checks.CanBeDamaged)
	{
		//Store values before changes so we can pass them to our bindable event
		float oldshield = GetCurrentStatValue(StatsType::Shield_H);
		float oldhealth = GetCurrentStatValue(StatsType::Health_H);

		//Local variables for overflow
		bool didoverflow = false;
		float Overflow = 0;

		//Check if we have shield
		if (HasShield())
		{
			//Check if amount is more than our shield value
			if (Amount > GetCurrentStatValue(StatsType::Shield_H))
			{
				//If amount is more, it means we have an overflow so we need to calculate how much our overflow is
				didoverflow = true;
				Overflow = Amount - GetCurrentStatValue(StatsType::Shield_H);

				//Because we're overflowing we need to set shield to 0
				Shield.Current = 0;

				//Check if we're using shield break sound, if so play sound
				if (Sounds.ShieldBreakSound)
				{
					ShieldBreakSound();
				}

				//Check if we're using hit anims, if so play anim
				if (Anims.PlayHitAnim)
				{
					HitAnim();
				}

				//Now that we've done the shield logic we can remove our overflow from health and play our hit sound if we're using it
				Health.Current = FMath::Clamp(Remove(Health.Current, Overflow), 0.f, Health.Max);
				HealthHitSound();

				//Check if our health is 0, if so fire death function
				if (CheckForDeath())
				{
					HandleDeath();
				}
			}
			//If amount is less than our shield value
			else
			{
				//Remove amount from shield and play our hit sound if we're using it
				Shield.Current = Remove(Shield.Current, Amount);
				ShieldHitSound();

				//Check if we're using hit anims, if so play anim
				if (Anims.PlayHitAnim)
				{
					HitAnim();
				}

				//Check if our shield percentage is less than our declared percentage, if so play low shield audio
				if (GetStatValueAsPercentage(StatsType::Shield_H) <= Sounds.ShieldLowPercentage)
				{
					ShieldLowSound();
				}
			}
		}
		//If we don't have shield
		else
		{
			//Play hit sound and remove amount from health
			HealthHitSound();
			Health.Current = FMath::Clamp(Remove(Health.Current, Amount), 0.f, Health.Max);

			//Check if we're using hit anims, if so play anim
			if (Anims.PlayHitAnim)
			{
				HitAnim();
			}

			//Check if our health percentage is lower than our declare percentage, if so play low health audio
			if (GetStatValueAsPercentage(StatsType::Health_H) <= Sounds.HealthLowPercentage)
			{
				HealthLowSound();
			}

			//Check if our health is 0, if so fire death function
			if (CheckForDeath())
			{
				HandleDeath();
			}
		}

		//Fires bindable event which we can add logic to using blueprints
		OnDealDamage.Broadcast(oldshield, oldhealth, GetCurrentStatValue(StatsType::Shield_H), GetCurrentStatValue(StatsType::Health_H), Amount, didoverflow, Overflow);
	}

	//Check if debug is true, if so print debug message
	if (Debug == true)
	{
		FString HealthString = "Damage taken: " + FString::SanitizeFloat(Amount) + " Shield is now: " + FString::SanitizeFloat(GetCurrentStatValue(StatsType::Shield_H)) + " Health is now: " + FString::SanitizeFloat(GetCurrentStatValue(StatsType::Health_H));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, HealthString);
	}

}

/*
experimental
*/
/*
float UBasicHealthComponent::CalculateDamage(float baseamount, TArray<float> buffs, TArray<float> debuffs)
{
	
	baseamount = baseamount + CalculateDamageBuffs(baseamount, buffs);
	baseamount = baseamount - CalculateDamageDebuffs(baseamount, debuffs);

	return baseamount;
}

float UBasicHealthComponent::CalculateDamageBuffs(float baseamount, TArray<float> buffs)
{

	float percentamount = 0.0f;
	float percentvalue = 0.0f;

	for (int i = 0; i < buffs.Num(); i++)
	{
		percentamount = percentamount + buffs[i];
	}

	percentamount = percentamount / 100;
	percentvalue = percentamount / baseamount * 100;

	return percentvalue;
}

float UBasicHealthComponent::CalculateDamageDebuffs(float baseamount, TArray<float> debuffs)
{

	float percentamount = 0.0f;
	float percentvalue = 0.0f;

	for (int i = 0; i < debuffs.Num(); i++)
	{
		percentamount = percentamount + debuffs[i];
	}

	percentamount = percentamount / 100;
	percentvalue = percentamount / baseamount * 100;

	return percentvalue;
}
*/


void UBasicHealthComponent::SetValues(FCYB_Values newhealth, FCYB_Values newshield, FCYB_Values newresource, FCYB_Values newstamina, FCYB_Values newenergy, FCYB_Values newhydration)
{

	Health = newhealth;
	Shield = newshield;
	Resource = newresource;
	Stamina = newstamina;
	Energy = newenergy;
	Hydration = newhydration;

}

void UBasicHealthComponent::GetValues(FCYB_Values& currenthealth, FCYB_Values& currentshield, FCYB_Values& currentresource, FCYB_Values& currentstamina, FCYB_Values& currentenergy, FCYB_Values& currenthydration)
{

	currenthealth = Health;
	currentshield = Shield;
	currentresource = Resource;
	currentstamina = Stamina;
	currentenergy = Energy;
	currenthydration = Hydration;

}


void UBasicHealthComponent::HandleDeath()
{
	//Get a reference to the components owner
	AActor* player = GetOwner();
	
	//Handle and Dele for death delay
	FTimerDelegate deathdel;
	FTimerHandle deathtimer;


	//Check if we're player death sounds, if so play death sound
	if (Sounds.PlayDeathSound)
	{
		DeathSound();
	}

	//Play death anim if valid
	DeathAnim();

	//Changes flow on enum state
	switch (OnDeath)
	{

	//If state equals respawn
	case DeathType::Respawn_H:

		//Check if our owner is valid, if so move actor and reset stats if needed
		if (IsValid(player) == true)
		{
		
			deathdel.BindUFunction(this, FName("DeathRespawn"));
			GetWorld()->GetTimerManager().SetTimer(deathtimer, deathdel, DeathValues.DeathDelay, false);

		}
		break;

	//If state equals main menu
	case DeathType::Main_Menu_H:

		deathdel.BindUFunction(this, FName("DeathMenu"));
		GetWorld()->GetTimerManager().SetTimer(deathtimer, deathdel, DeathValues.DeathDelay, false);
		
		break;

	//If state equals destroy
	case DeathType::Destroy_H:

		deathdel.BindUFunction(this, FName("DeathDestroy"));
		GetWorld()->GetTimerManager().SetTimer(deathtimer, deathdel, DeathValues.DeathDelay, false);

		break;

	//If state equals show widget
	case DeathType::Show_Widget_H:

		deathdel.BindUFunction(this, FName("DeathWidget"));
		GetWorld()->GetTimerManager().SetTimer(deathtimer, deathdel, DeathValues.DeathDelay, false);
		
		break;
	}

	//In our death sound function we change our sound que in our component, so we check if its valid and change it back
	if (IsValid(HealthLowAudioComponent) == true && IsValid(Sounds.HealthLowSound) == true)
	{
		HealthLowAudioComponent->SetSound(Sounds.HealthLowSound);
	}

	//Check if our low stamina is valid and stop it if its playing
	if (IsValid(StaminaLowAudioComponent) == true)
	{
		StaminaLowAudioComponent->Stop();
	}

	//Check if our low shield is valid and stop it if its playing
	if (IsValid(ShieldLowAudioComponent) == true)
	{
		StaminaLowAudioComponent->Stop();
	}

	//Check if our low health is valid and stop it if its playing
	if (IsValid(HealthLowAudioComponent) == true)
	{
		StaminaLowAudioComponent->Stop();
	}

	//Fires bindable event which we can add logic to using blueprints
	OnHandleDeath.Broadcast();
}