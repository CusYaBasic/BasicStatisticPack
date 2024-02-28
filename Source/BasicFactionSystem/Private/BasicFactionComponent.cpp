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


#include "BasicFactionComponent.h"
#include "Net/UnrealNetwork.h"

 // Sets default values for this component's properties
UBasicFactionComponent::UBasicFactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UBasicFactionComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UBasicFactionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBasicFactionComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBasicFactionComponent, Owner);
	DOREPLIFETIME(UBasicFactionComponent, Factions);
	DOREPLIFETIME(UBasicFactionComponent, FactionInfo);
	DOREPLIFETIME(UBasicFactionComponent, FactionDefault);
	DOREPLIFETIME(UBasicFactionComponent, FactionHostilityLevels);
	DOREPLIFETIME(UBasicFactionComponent, CanModifyReputation);
	DOREPLIFETIME(UBasicFactionComponent, PlaySound);
	DOREPLIFETIME(UBasicFactionComponent, FactionLevelUpSound);
	DOREPLIFETIME(UBasicFactionComponent, FactionLevelDownSound);


}

int UBasicFactionComponent::Percentage(int x, int a, int b)
{
	return ((x - a) * 100) / (b - a);
}

int UBasicFactionComponent::GetFactionLevel(FString name)
{
	return Factions[GetFactionIndex(name)].FactionLevel;
}

UTexture2D* UBasicFactionComponent::GetFactionIcon(FString name)
{
	return Factions[GetFactionIndex(name)].FactionIcon;
}

int UBasicFactionComponent::GetFactionMaxReputationLevel(FString name)
{
	return Factions[GetFactionIndex(name)].MaxFactionLevel;
}


int UBasicFactionComponent::GetFactionCurrentReputation(FString name)
{
	return Factions[GetFactionIndex(name)].CurrentFactionReputation;
}

int UBasicFactionComponent::GetFactionNextReputation(FString name)
{
	return Factions[GetFactionIndex(name)].NextFactionReputation;
}

int UBasicFactionComponent::GetFactionPreviousReputation(FString name)
{
	return Factions[GetFactionIndex(name)].PreviousFactionReputation;
}

int UBasicFactionComponent::GetFactionMaxReputation(FString name)
{
	return Factions[GetFactionIndex(name)].MaxReputation;
}

bool UBasicFactionComponent::IsMaxFactionLevel(FString name)
{

	if (GetFactionByName(name).FactionLevel >= GetFactionByName(name).MaxFactionLevel)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool UBasicFactionComponent::IsInFaction(FString name)
{

	bool HasFaction = false;

	for (int i = 0; i < Factions.Num(); i++)
	{

		if (Factions[i].Name == name)
		{
			HasFaction = true;
			return HasFaction;
		}

	}
	return HasFaction;
}

FFactionValues UBasicFactionComponent::GetFactionByName(FString name)
{

	return Factions[GetFactionIndex(name)];

}

int UBasicFactionComponent::GetFactionIndex(FString name)
{

	bool HasFaction = false;

	for (int i = 0; i < Factions.Num(); i++)
	{

		if (Factions[i].Name == name)
		{
			HasFaction = true;
			return i;
		}

	}
	if (HasFaction == false)
	{
		FString FactionString = "Cannot find Faction: " + name + ", Returned first indexed Faction instead...";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FactionString);
		return 0;
	}
	return 0;

}

//DON'T GIVE UP, YOU GOT THIS <3

void UBasicFactionComponent::ModifyReputation(FString name, ChangeTypeFaction changetype, int amount, bool debug)
{
	if (CanModifyReputation)
	{

		switch (changetype)
		{
		case ChangeTypeFaction::Add_F:
			Factions[GetFactionIndex(name)].CurrentFactionReputation = FMath::Clamp(Factions[GetFactionIndex(name)].CurrentFactionReputation + amount, 0, Factions[GetFactionIndex(name)].MaxReputation);
			if (HasEnoughReputationToLevel(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].NextFactionReputation))
			{
				FactionLevelUp(name);
			}
			if (debug)
			{
				FString FactionString = "Faction: " + GetFactionByName(name).Name + ", Current Rep: " + FString::FromInt(GetFactionCurrentReputation(name)) + "Next Faction Rep: " + FString::FromInt(GetFactionNextReputation(name)) + "Previous Faction Rep: " + FString::FromInt(GetFactionPreviousReputation(name));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FactionString);
			}
			break;

		case ChangeTypeFaction::Remove_F:
			Factions[GetFactionIndex(name)].CurrentFactionReputation = FMath::Clamp(Factions[GetFactionIndex(name)].CurrentFactionReputation - amount, 0, Factions[GetFactionIndex(name)].MaxReputation);
			if (HasEnoughReputationToDownLevel(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].PreviousFactionReputation))
			{
				FactionLevelDown(name);
			}
			if (debug)
			{
				FString FactionString = "Faction: " + GetFactionByName(name).Name + ", Current Rep: " + FString::FromInt(GetFactionCurrentReputation(name)) + "Next Faction Rep: " + FString::FromInt(GetFactionNextReputation(name)) + "Previous Faction Rep: " + FString::FromInt(GetFactionPreviousReputation(name));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FactionString);
			}
			break;

		case ChangeTypeFaction::Change_F:
			Factions[GetFactionIndex(name)].CurrentFactionReputation = FMath::Clamp(amount, 0, Factions[GetFactionIndex(name)].MaxReputation);
			if (HasEnoughReputationToLevel(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].NextFactionReputation))
			{
				FactionLevelUp(name);
			}
			else if (HasEnoughReputationToDownLevel(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].PreviousFactionReputation))
			{
				FactionLevelDown(name);
			}
			if (debug)
			{
				FString FactionString = "Faction: " + GetFactionByName(name).Name + ", Current Rep: " + FString::FromInt(GetFactionCurrentReputation(name)) + "Next Faction Rep: " + FString::FromInt(GetFactionNextReputation(name)) + "Previous Faction Rep: " + FString::FromInt(GetFactionPreviousReputation(name));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FactionString);
			}
			break;
		}
	}


}

bool UBasicFactionComponent::HasEnoughReputationToLevel(int current, int amountNeeded)
{
	if (current >= amountNeeded)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBasicFactionComponent::HasRequiredFactionLevel(FString name, int FactionLevelNeeded)
{


	if (FactionLevelNeeded > Factions[GetFactionIndex(name)].FactionLevel)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool UBasicFactionComponent::HasEnoughReputationToDownLevel(int current, int amountNeeded)
{
	if (current < amountNeeded)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UBasicFactionComponent::SetCanModifyReputation(bool canmodify)
{
	CanModifyReputation = canmodify;
}

bool UBasicFactionComponent::GetCanModifyReputation()
{
	return CanModifyReputation;
}

int UBasicFactionComponent::GetFactionReputationValueAsPercentage(FString name)
{
	return Percentage(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].PreviousFactionReputation, Factions[GetFactionIndex(name)].NextFactionReputation) * 100;
}

float UBasicFactionComponent::GetFactionReputationValueForProgressBar(FString name)
{

	return float(Percentage(Factions[GetFactionIndex(name)].CurrentFactionReputation, Factions[GetFactionIndex(name)].PreviousFactionReputation, Factions[GetFactionIndex(name)].NextFactionReputation)) / 100;

}

int UBasicFactionComponent::GetReputationLeftUntilFactionLevelUpAsPercentage(FString name)
{

	return 100 - GetFactionReputationValueAsPercentage(name);

}

int UBasicFactionComponent::GetReputationLeftUntilFactionLevelUp(FString name)
{

	return Factions[GetFactionIndex(name)].NextFactionReputation - Factions[GetFactionIndex(name)].CurrentFactionReputation;
}

bool UBasicFactionComponent::IsPlayer()
{

	switch (Owner)
	{
	case OwnerTypeFaction::Player_F:
		return true;
		break;

	case OwnerTypeFaction::AI_F:
		return false;
		break;
	}

	return true;
}

void UBasicFactionComponent::CheckForHostilityChange(FString name)
{

	FString level = FString::FromInt(Factions[GetFactionIndex(name)].FactionLevel);
	FName FactionLevel = FName(*level);
	FHostilityLevels* Row;

	Row = FactionHostilityLevels->FindRow<FHostilityLevels>(FName(FactionLevel), "", true);
	if (Row)
	{
		Factions[GetFactionIndex(name)].Hostility = Row->Hostility;
		OnHostilityChanged.Broadcast(name, Factions[GetFactionIndex(name)].Hostility);
	}

}

void UBasicFactionComponent::JoinFaction(FString name)
{
	if (!IsInFaction(name))
	{
		FFactionValues* Row;
		FFactionValues faction;

		FName FactionName = FName(*name);
		Row = FactionDefault->FindRow<FFactionValues>(FName(FactionName), "", true);
		if (Row)
		{
			faction.Name = Row->Name;
			faction.FactionIcon = Row->FactionIcon;
			faction.FactionLevel = Row->FactionLevel;
			faction.MaxFactionLevel = Row->MaxFactionLevel;
			faction.CurrentFactionReputation = Row->CurrentFactionReputation;
			faction.NextFactionReputation = Row->NextFactionReputation;
			faction.PreviousFactionReputation = Row->PreviousFactionReputation;
			faction.MaxReputation = Row->MaxReputation;
			faction.Hostility = Row->Hostility;
			Factions.Add(faction);
			OnFactionJoin.Broadcast(name);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Already in faction!");
	}
}

void UBasicFactionComponent::LeaveFaction(FString name)
{
	if (IsInFaction(name))
	{
		Factions.RemoveAt(GetFactionIndex(name));
		OnFactionLeave.Broadcast(name);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Not in faction!");
	}
}

void UBasicFactionComponent::FactionLevelUp(const FString& name)
{

	FString NextFactionString;
	FName NextFactionName;
	FFactionInfo* Row;


	if (!IsMaxFactionLevel(name))
	{
		Factions[GetFactionIndex(name)].FactionLevel++;
		NextFactionString = FString::FromInt(Factions[GetFactionIndex(name)].FactionLevel);
		NextFactionName = FName(*NextFactionString);
		Row = FactionInfo->FindRow<FFactionInfo>(FName(NextFactionName), "", true);
		if (Row)
		{
			Factions[GetFactionIndex(name)].NextFactionReputation = Row->NextFactionReputation;
			Factions[GetFactionIndex(name)].PreviousFactionReputation = Row->PreviousFactionReputation;
			CheckForHostilityChange(name);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Next Level not found!");
		}
	}

	if (PlaySound == true && IsValid(FactionLevelUpSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FactionLevelUpSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}

	OnFactionLevelUp.Broadcast();

}

void UBasicFactionComponent::FactionLevelDown(const FString& name)
{

	FString PreviousFactionString;
	FName PreviousFactionName;
	FFactionInfo* Row;

	if (GetFactionByName(name).FactionLevel == 1)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Min Faction!");
	}
	else
	{
		Factions[GetFactionIndex(name)].FactionLevel--;
		PreviousFactionString = FString::FromInt(Factions[GetFactionIndex(name)].FactionLevel);
		PreviousFactionName = FName(*PreviousFactionString);
		Row = FactionInfo->FindRow<FFactionInfo>(FName(PreviousFactionName), "", true);
		if (Row)
		{
			Factions[GetFactionIndex(name)].NextFactionReputation = Row->NextFactionReputation;
			Factions[GetFactionIndex(name)].PreviousFactionReputation = Row->PreviousFactionReputation;
			CheckForHostilityChange(name);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Previous Faction not found!");
		}
	}

	if (PlaySound == true && IsValid(FactionLevelDownSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FactionLevelDownSound, GetOwner()->GetActorLocation(), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}

	OnFactionLevelDown.Broadcast();

}

void UBasicFactionComponent::SetFactions(TArray<FFactionValues> faction)
{

	//For every element in the array param
	for (int i = 0; i < faction.Num(); i++)
	{
		//We check to see if it exists, if not add it
		if (!IsInFaction(faction[i].Name))
		{
			Factions.Add(faction[i]);
		}
		//If does exist replace it with our new details
		else
		{
			Factions[GetFactionIndex(faction[i].Name)] = faction[i];
		}
	}

}

void UBasicFactionComponent::GetFactions(TArray<FFactionValues> &faction)
{

	faction = Factions;

}