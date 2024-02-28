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


#include "BasicCurrencyComponent.h"
#include "Net/UnrealNetwork.h"
#include "WorldCurrency.h"
#include "Engine/World.h"
#include "BasicCurrencyComponent.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>


 // Sets default values for this component's properties
UBasicCurrencyComponent::UBasicCurrencyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBasicCurrencyComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UBasicCurrencyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBasicCurrencyComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{

	//Replicate variables
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBasicCurrencyComponent, Owner);
	DOREPLIFETIME(UBasicCurrencyComponent, MainCurrency);
	DOREPLIFETIME(UBasicCurrencyComponent, SpecialCurrencies);
	DOREPLIFETIME(UBasicCurrencyComponent, SecondaryCurrencies);


}

int UBasicCurrencyComponent::GetMainCurrencyAmount()
{
	//Return the main currency current amount
	return MainCurrency.CurrentAmount;
}

int UBasicCurrencyComponent::GetMainCurrencyMaxAmount()
{
	//Return the main currency max amount
	return MainCurrency.MaxAmount;
}

FString UBasicCurrencyComponent::GetMainCurrencyName()
{
	//Return the main currency name
	return MainCurrency.Name;
}

UTexture2D* UBasicCurrencyComponent::GetMainCurrencyIcon()
{
	//Return the main currency image
	return MainCurrency.CurrencyImage;
}

bool UBasicCurrencyComponent::GetMainCurrencyPlaySound()
{
	//Return the main currency play sound bool
	return MainCurrency.PlaySound;
}

USoundCue* UBasicCurrencyComponent::GetMainCurrencyDropSound()
{
	//Return the main currency drop sound
	return MainCurrency.CurrencyDropSound;
}

USoundCue* UBasicCurrencyComponent::GetMainCurrencyIncreaseSound()
{
	//Return the main currency increase sound
	return MainCurrency.CurrencyIncreasedSound;
}

USoundCue* UBasicCurrencyComponent::GetMainCurrencyDecreaseSound()
{
	//Return the main currency decrease sound
	return MainCurrency.CurrencyDecreasedSound;
}

UStaticMesh* UBasicCurrencyComponent::GetMainCurrencyMesh()
{
	//Return the main currency mesh
	return MainCurrency.Mesh;
}

FCurrencyValues UBasicCurrencyComponent::GetSpecialCurrencyByName(FString name)
{
	//Return the special currency index
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)];
}

int UBasicCurrencyComponent::GetSpecialCurrencyIndex(FString name)
{

	//Bool to check if currency exists
	bool HasCurrency = false;

	//For each element in special currencies array
	for (int i = 0; i < SpecialCurrencies.Num(); i++)
	{

		//Check if the currency name is the same as the param name
		if (SpecialCurrencies[i].Name == name)
		{
			//If so currency exists so return the array index
			HasCurrency = true;
			return i;
		}

	}

	//If currency doesn't exist send a debug message stating so and return 0, I couldn't find a way to pass a NULL ref for the array if the currency doesn't exist so we just pass back the first currency which would be 0
	//You could pass back -1 but i'm not sure if that would crash the editor if it looks for a an unreachable index, i wasn't brave enough to find out so returning the first index is fine.
	if (!HasCurrency)
	{
		FString CurrencyString = "Cannot find Currency: " + name + ", Returned first indexed Currency instead..";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, CurrencyString);
		return 0;
	}

	//All routes need a return value, although it should never reach this return
	return 0;

}

int UBasicCurrencyComponent::GetSpecialCurrencyAmount(FString name)
{
	//Return the special currency current amount
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrentAmount;
}

int UBasicCurrencyComponent::GetSpecialCurrencyMaxAmount(FString name)
{
	//Return the special currency max amount
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].MaxAmount;
}

UTexture2D* UBasicCurrencyComponent::GetSpecialCurrencyIcon(FString name)
{
	//Return the special currency icon
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrencyImage;
}

bool UBasicCurrencyComponent::GetSpecialCurrencyPlaySound(FString name)
{
	//Return the special currency play sound bool
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].PlaySound;
}

USoundCue* UBasicCurrencyComponent::GetSpecialCurrencyDropSound(FString name)
{
	//Return the special currency drop sound
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDropSound;
}

USoundCue* UBasicCurrencyComponent::GetSpecialCurrencyIncreaseSound(FString name)
{
	//Return the special currency increase sound
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrencyIncreasedSound;
}

USoundCue* UBasicCurrencyComponent::GetSpecialCurrencyDecreaseSound(FString name)
{
	//Return the special currency deecrease sound
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDecreasedSound;
}

UStaticMesh* UBasicCurrencyComponent::GetSpecialCurrencyMesh(FString name)
{
	//Return the special currency mesh
	return SpecialCurrencies[GetSpecialCurrencyIndex(name)].Mesh;
}

FCurrencyValues UBasicCurrencyComponent::GetSecondaryCurrencyByName(FString name)
{
	//Return the special currency struct
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)];
}

int UBasicCurrencyComponent::GetSecondaryCurrencyIndex(FString name)
{

	bool HasCurrency = false;

	for (int i = 0; i < SecondaryCurrencies.Num(); i++)
	{

		if (SecondaryCurrencies[i].Name == name)
		{
			HasCurrency = true;
			return i;
		}

	}
	if (!HasCurrency)
	{
		FString CurrencyString = "Cannot find Currency: " + name + ", Returned first indexed Currency instead..";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, CurrencyString);
		return 0;
	}
	return 0;

}

int UBasicCurrencyComponent::GetSecondaryCurrencyAmount(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrentAmount;
}

int UBasicCurrencyComponent::GetSecondaryCurrencyMaxAmount(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].MaxAmount;
}

UTexture2D* UBasicCurrencyComponent::GetSecondaryCurrencyIcon(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyImage;
}

bool UBasicCurrencyComponent::GetSecondaryCurrencyPlaySound(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].PlaySound;
}

USoundCue* UBasicCurrencyComponent::GetSecondaryCurrencyDropSound(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDropSound;
}

USoundCue* UBasicCurrencyComponent::GetSecondaryCurrencyIncreaseSound(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyIncreasedSound;
}

USoundCue* UBasicCurrencyComponent::GetSecondaryCurrencyDecreaseSound(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDecreasedSound;
}

UStaticMesh* UBasicCurrencyComponent::GetSecondaryCurrencyMesh(FString name)
{
	return SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].Mesh;
}

bool UBasicCurrencyComponent::HasEnoughCurrency(CurrencyType currency, FString name, int amount)
{

	switch (currency)
	{

	case CurrencyType::Main_C:
		if (MainCurrency.CurrentAmount >= amount)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case CurrencyType::Secondary_C:
		if (GetSecondaryCurrencyAmount(name) >= amount)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case CurrencyType::Special_C:
		if (GetSpecialCurrencyAmount(name) >= amount)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	}
	return false;
}

FTransform UBasicCurrencyComponent::GetCurrencyDropLocation()
{
	FTransform loc = GetOwner()->GetActorTransform();
	loc.SetLocation(loc.GetLocation() + (loc.GetRotation().GetForwardVector() * 200));
	return loc;
}

//YOUR GAMES GUNNA BE GREAT, GIME ME A KEY ON RELEASE PLS

void UBasicCurrencyComponent::ModifyCurrency(CurrencyType currency, FString name, CurrencyChangeType changetype, int amount, bool debug)
{

	switch (currency)
	{

	case CurrencyType::Main_C:

		switch (changetype)
		{

		case CurrencyChangeType::Add_C:
			MainCurrency.CurrentAmount = FMath::Clamp(MainCurrency.CurrentAmount + amount, 0, MainCurrency.MaxAmount);

			if (MainCurrency.PlaySound == true && IsValid(MainCurrency.CurrencyIncreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MainCurrency.CurrencyIncreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Remove_C:
			MainCurrency.CurrentAmount = MainCurrency.CurrentAmount - amount;

			if (MainCurrency.PlaySound == true && IsValid(MainCurrency.CurrencyDecreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MainCurrency.CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Change_C:
			MainCurrency.CurrentAmount = amount;
			if (MainCurrency.PlaySound == true && IsValid(MainCurrency.CurrencyDropSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, MainCurrency.CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		}
		break;

	case CurrencyType::Secondary_C:

		switch (changetype)
		{

		case CurrencyChangeType::Add_C:
			SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrentAmount = FMath::Clamp(GetSecondaryCurrencyAmount(name) + amount, 0, GetSecondaryCurrencyMaxAmount(name));

			if (SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyIncreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyIncreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Remove_C:
			SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrentAmount = SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrentAmount - amount;

			if (SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDecreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Change_C:
			SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrentAmount = amount;

			if (SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDropSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;
		}
		break;

	case CurrencyType::Special_C:

		switch (changetype)
		{

		case CurrencyChangeType::Add_C:
			SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrentAmount = FMath::Clamp(GetSpecialCurrencyAmount(name) + amount, 0, GetSpecialCurrencyMaxAmount(name));

			if (SecondaryCurrencies[GetSpecialCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyIncreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyIncreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Remove_C:
			SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrentAmount = SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrentAmount - amount;

			if (SecondaryCurrencies[GetSpecialCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDecreasedSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;

		case CurrencyChangeType::Change_C:
			SpecialCurrencies[GetSpecialCurrencyIndex(name)].CurrentAmount = amount;

			if (SecondaryCurrencies[GetSpecialCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDropSound) == true)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
			}
			break;
		}
		break;
	}


	if (debug)
	{
		FString CurrencyString = "Currency changed by: " + FString::FromInt(amount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, CurrencyString);
	}

}

void UBasicCurrencyComponent::Purchase(CurrencyType currency, FString currencyname, int costamount, FString itemname, int amounttopurchase)
{

	int totalcostamount = costamount * amounttopurchase;

	switch (currency)
	{

	case CurrencyType::Main_C:
		if (HasEnoughCurrency(CurrencyType::Main_C, currencyname, totalcostamount))
		{
			MainCurrency.CurrentAmount = MainCurrency.CurrentAmount - totalcostamount;
			OnPurchaseSuccess.Broadcast(itemname, amounttopurchase);
		}
		else
		{
			OnPurchaseFailed.Broadcast();
		}

		if (MainCurrency.PlaySound == true && IsValid(MainCurrency.CurrencyDecreasedSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, MainCurrency.CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;

	case CurrencyType::Secondary_C:
		if (HasEnoughCurrency(CurrencyType::Secondary_C, currencyname, totalcostamount))
		{
			SecondaryCurrencies[GetSecondaryCurrencyIndex(currencyname)].CurrentAmount = SecondaryCurrencies[GetSecondaryCurrencyIndex(currencyname)].CurrentAmount - totalcostamount;
			OnPurchaseSuccess.Broadcast(itemname, amounttopurchase);
		}
		else
		{
			OnPurchaseFailed.Broadcast();
		}

		if (SecondaryCurrencies[GetSecondaryCurrencyIndex(currencyname)].PlaySound == true && IsValid(SecondaryCurrencies[GetSecondaryCurrencyIndex(currencyname)].CurrencyDecreasedSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSecondaryCurrencyIndex(currencyname)].CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;

	case CurrencyType::Special_C:
		if (HasEnoughCurrency(CurrencyType::Special_C, currencyname, totalcostamount))
		{
			SpecialCurrencies[GetSpecialCurrencyIndex(currencyname)].CurrentAmount = SpecialCurrencies[GetSpecialCurrencyIndex(currencyname)].CurrentAmount - totalcostamount;
			OnPurchaseSuccess.Broadcast(itemname, amounttopurchase);
		}
		else
		{
			OnPurchaseFailed.Broadcast();
		}

		if (SecondaryCurrencies[GetSpecialCurrencyIndex(currencyname)].PlaySound == true && IsValid(SecondaryCurrencies[GetSpecialCurrencyIndex(currencyname)].CurrencyDecreasedSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSpecialCurrencyIndex(currencyname)].CurrencyDecreasedSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;

	}

}

void UBasicCurrencyComponent::DropCurrency(CurrencyType currency, FString name, int amount, FTransform transform, bool debug)
{

	FVector Location = transform.GetLocation();
	FRotator Rotation = transform.Rotator();
	FActorSpawnParameters SpawnInfo;
	AWorldCurrency* drop = GetWorld()->SpawnActor<AWorldCurrency>(Location, Rotation, SpawnInfo);
	bool DidDrop = false;

	switch (currency)
	{
	case CurrencyType::Main_C:
		if (HasEnoughCurrency(CurrencyType::Main_C, name, amount))
		{

			drop->MeshComponent->SetStaticMesh(MainCurrency.Mesh);
			drop->Details.CurrencyType = CurrencyTypes::M;
			drop->Details.Name = name;
			drop->Details.CurrentAmount = amount;
			drop->Details.CanUse = true;
			drop->Details.CanDestroy = true;
			DidDrop = true;

		}

		if (MainCurrency.PlaySound == true && IsValid(MainCurrency.CurrencyDropSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, MainCurrency.CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;

	case CurrencyType::Secondary_C:
		if (HasEnoughCurrency(CurrencyType::Secondary_C, name, amount))
		{

			drop->MeshComponent->SetStaticMesh(GetSecondaryCurrencyByName(name).Mesh);
			drop->Details.CurrencyType = CurrencyTypes::S;
			drop->Details.Name = name;
			drop->Details.CurrentAmount = amount;
			drop->Details.CanUse = true;
			drop->Details.CanDestroy = true;
			DidDrop = true;

		}

		if (SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDropSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSecondaryCurrencyIndex(name)].CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;

	case CurrencyType::Special_C:
		if (HasEnoughCurrency(CurrencyType::Special_C, name, amount))
		{

			drop->MeshComponent->SetStaticMesh(GetSpecialCurrencyByName(name).Mesh);
			drop->Details.CurrencyType = CurrencyTypes::Sp;
			drop->Details.Name = name;
			drop->Details.CurrentAmount = amount;
			drop->Details.CanUse = true;
			drop->Details.CanDestroy = true;
			DidDrop = true;

		}

		if (SecondaryCurrencies[GetSpecialCurrencyIndex(name)].PlaySound == true && IsValid(SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDropSound) == true)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SecondaryCurrencies[GetSpecialCurrencyIndex(name)].CurrencyDropSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
		}
		break;
	}

	if (debug && DidDrop)
	{
		FString CurrencyString = "Currency dropped: " + FString::FromInt(amount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, CurrencyString);
	}

	if (debug && !DidDrop)
	{
		FString CurrencyString = "No items dropped";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, CurrencyString);
	}
}


bool UBasicCurrencyComponent::DoesSecondaryCurrencyExist(FString name)
{

	bool HasCurrency = false;

	for (int i = 0; i < SecondaryCurrencies.Num(); i++)
	{

		if (SecondaryCurrencies[i].Name == name)
		{
			HasCurrency = true;
			return HasCurrency;
		}

	}
	return HasCurrency;
}

bool UBasicCurrencyComponent::DoesSpecialCurrencyExist(FString name)
{

	bool HasCurrency = false;

	for (int i = 0; i < SpecialCurrencies.Num(); i++)
	{

		if (SpecialCurrencies[i].Name == name)
		{
			HasCurrency = true;
			return HasCurrency;
		}

	}
	return HasCurrency;
}

void UBasicCurrencyComponent::SetCurrencies(FCurrencyValues main, TArray<FCurrencyValues> secondary, TArray<FCurrencyValues> special)
{

	MainCurrency = main;

	//For every element in the array param
	for (int i = 0; i < secondary.Num(); i++)
	{
		//We check to see if it exists, if not add it
		if (!DoesSecondaryCurrencyExist(secondary[i].Name))
		{
			SecondaryCurrencies.Add(secondary[i]);
		}
		//If does exist replace it with our new details
		else
		{
			SecondaryCurrencies[GetSecondaryCurrencyIndex(secondary[i].Name)] = secondary[i];
		}
	}

	//For every element in the array param
	for (int i = 0; i < special.Num(); i++)
	{
		//We check to see if it exists, if not add it
		if (!DoesSpecialCurrencyExist(special[i].Name))
		{
			SpecialCurrencies.Add(special[i]);
		}
		//If does exist replace it with our new details
		else
		{
			SpecialCurrencies[GetSpecialCurrencyIndex(special[i].Name)] = special[i];
		}
	}


}

void UBasicCurrencyComponent::GetCurrencies(FCurrencyValues &main, TArray<FCurrencyValues> &secondary, TArray<FCurrencyValues> &special)
{
	main = MainCurrency;
	secondary = SecondaryCurrencies;
	special = SpecialCurrencies;
}