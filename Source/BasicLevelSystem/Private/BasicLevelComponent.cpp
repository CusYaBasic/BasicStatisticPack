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


#include "BasicLevelComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UBasicLevelComponent::UBasicLevelComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UBasicLevelComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UBasicLevelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBasicLevelComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replcate our variables
	DOREPLIFETIME(UBasicLevelComponent, Owner);
	DOREPLIFETIME(UBasicLevelComponent, MainLevel);
	DOREPLIFETIME(UBasicLevelComponent, PrimaryLevels);
	DOREPLIFETIME(UBasicLevelComponent, SecondaryLevels);
	DOREPLIFETIME(UBasicLevelComponent, LevelInfo);
	DOREPLIFETIME(UBasicLevelComponent, PrimaryLevelInfo);
	DOREPLIFETIME(UBasicLevelComponent, SecondaryLevelInfo);
	DOREPLIFETIME(UBasicLevelComponent, LevelDefaultsInfo);
	DOREPLIFETIME(UBasicLevelComponent, CanModifyXP);
	DOREPLIFETIME(UBasicLevelComponent, PlaySound);
	DOREPLIFETIME(UBasicLevelComponent, LevelUpSound);
	DOREPLIFETIME(UBasicLevelComponent, LevelDownSound);


}

int UBasicLevelComponent::Percentage(int x, int a, int b)
{
	//Returns percentage from a range of numbers (idk if thats the right terms, but you'll wanna use this for progress bar values)
	//bruhhh, it took me like 3 hours to figure this out so pls love me
	return ((x - a) * 100) / (b - a);
}

void UBasicLevelComponent::LoadMainLevel(FLevelValues Details)
{
	MainLevel = Details;
}

void UBasicLevelComponent::LoadPrimaryLevels(TArray<FLevelValues> Details)
{
	
	//For every element in the array param
	for (int i = 0; i < Details.Num(); i++)
	{
		//We check to see if it exists, if not add it
		if (!DoesPrimaryLevelExist(Details[i].Name))
		{
			PrimaryLevels.Add(Details[i]);
		}
		//If does exist replace it with our new details
		else
		{
			PrimaryLevels[GetPrimaryLevelIndex(Details[i].Name)] = Details[i];
		}
	}
}

void UBasicLevelComponent::LoadSecondaryLevel(TArray<FLevelValues> Details)
{
	//For every element in the array param
	for (int i = 0; i < Details.Num(); i++)
	{
		//We check to see if it exists, if not add it
		if (!DoesSecondaryLevelExist(Details[i].Name))
		{
			SecondaryLevels.Add(Details[i]);
		}
		//If does exist replace it with our new details
		else
		{
			SecondaryLevels[GetSecondaryLevelIndex(Details[i].Name)] = Details[i];
		}
	}
}

FLevelValues UBasicLevelComponent::GetMainLevelDetails()
{
	return MainLevel;
}

TArray<FLevelValues> UBasicLevelComponent::GetPrimaryLevelDetails()
{
	return PrimaryLevels;
}

TArray<FLevelValues> UBasicLevelComponent::GetSecondaryLevelDetails()
{
	return SecondaryLevels;
}



int UBasicLevelComponent::GetMainLevel()
{
	return MainLevel.Level;
}

int UBasicLevelComponent::GetMainLevelMaxLevel()
{
	return MainLevel.MaxLevel;
}

FString UBasicLevelComponent::GetMainLevelName()
{
	return MainLevel.Name;
}

int UBasicLevelComponent::GetMainLevelCurrentXP()
{
	return MainLevel.CurrentXP;
}

int UBasicLevelComponent::GetMainLevelNextLevelXP()
{
	return MainLevel.NextLevelXP;
}

int UBasicLevelComponent::GetMainLevelPreviousLevelXP()
{
	return MainLevel.PreviousLevelXP;
}

int UBasicLevelComponent::GetMainLevelMaxXP()
{
	return MainLevel.MaxXP;
}

int UBasicLevelComponent::GetPrimaryLevelMaxLevel(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].MaxLevel;
}

int UBasicLevelComponent::GetPrimaryLevel(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].Level;
}

int UBasicLevelComponent::GetPrimaryLevelCurrentXP(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP;
}

int UBasicLevelComponent::GetPrimaryLevelNextLevelXP(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP;
}

int UBasicLevelComponent::GetPrimaryLevelPreviousLevelXP(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP;
}

int UBasicLevelComponent::GetPrimaryLevelMaxXP(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)].MaxXP;
}

int UBasicLevelComponent::GetSecondaryLevelMaxLevel(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].MaxLevel;
}

int UBasicLevelComponent::GetSecondaryLevel(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].Level;
}

int UBasicLevelComponent::GetSecondaryLevelCurrentXP(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP;
}

int UBasicLevelComponent::GetSecondaryLevelNextLevelXP(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP;
}

int UBasicLevelComponent::GetSecondaryLevelPreviousLevelXP(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].PreviousLevelXP;
}

int UBasicLevelComponent::GetSecondaryLevelMaxXP(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)].MaxXP;
}

FLevelValues UBasicLevelComponent::GetLevelDefaults(FString name)
{
	FLevelValues defaults;
	FName LevelDefaultName = FName(*name);
	FLevelValues* Row = LevelDefaultsInfo->FindRow<FLevelValues>(FName(LevelDefaultName), "", true);
	if (Row)
	{
		defaults.Name = Row->Name;
		defaults.CurrentXP = Row->CurrentXP;
		defaults.NextLevelXP = Row->NextLevelXP;
		defaults.PreviousLevelXP = Row->PreviousLevelXP;
		defaults.MaxXP = Row->MaxXP;
		defaults.Level = Row->Level;
		defaults.MaxLevel = Row->MaxLevel;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Default Level not found!");
	}

	return defaults;
}

bool UBasicLevelComponent::DoesPrimaryLevelExist(FString name)
{

	bool HasLevel = false;

	for (int i = 0; i < PrimaryLevels.Num(); i++)
	{

		if (PrimaryLevels[i].Name == name)
		{
			HasLevel = true;
			return HasLevel;
		}

	}
	return HasLevel;
}

bool UBasicLevelComponent::DoesSecondaryLevelExist(FString name)
{

	bool HasLevel = false;

	for (int i = 0; i < SecondaryLevels.Num(); i++)
	{

		if (SecondaryLevels[i].Name == name)
		{
			HasLevel = true;
			return HasLevel;
		}

	}
	return HasLevel;
}

bool UBasicLevelComponent::IsMaxLevel(LevelType level, FString name)
{

	switch (level)
	{
	case LevelType::Main_L:
		if (GetMainLevel() >= GetMainLevelMaxLevel())
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case LevelType::Primary_L:
		if (GetPrimaryLevelByName(name).Level >= GetPrimaryLevelByName(name).MaxLevel)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;

	case LevelType::Secondary_L:
		if (GetSecondaryLevelByName(name).Level >= GetSecondaryLevelByName(name).MaxLevel)
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

FLevelValues UBasicLevelComponent::GetPrimaryLevelByName(FString name)
{
	return PrimaryLevels[GetPrimaryLevelIndex(name)];
}

int UBasicLevelComponent::GetPrimaryLevelIndex(FString name)
{

	bool HasLevel = false;

	for (int i = 0; i < PrimaryLevels.Num(); i++)
	{

		if (PrimaryLevels[i].Name == name)
		{
			HasLevel = true;
			return i;
		}

	}
	if (!HasLevel)
	{
		FString LevelString = "Cannot find level: " + name + ", Returned first indexed Level instead...";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
		return 0;
	}
	return 0;

}

FLevelValues UBasicLevelComponent::GetSecondaryLevelByName(FString name)
{
	return SecondaryLevels[GetSecondaryLevelIndex(name)];
}

int UBasicLevelComponent::GetSecondaryLevelIndex(FString name)
{

	bool HasLevel = false;

	for (int i = 0; i < SecondaryLevels.Num(); i++)
	{

		if (SecondaryLevels[i].Name == name)
		{
			HasLevel = true;
			return i;
		}
	
	}
	if (!HasLevel)
	{
		FString LevelString = "Cannot find level: " + name + ", Returned first indexed Level instead..";
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
		return 0;
	}
	return 0;

}

//I HOPE YOU HAVE A GREAT DAY <3

void UBasicLevelComponent::ModifyXP(LevelType level, FString name, ChangeTypeLevel changetype, int amount, bool debug)
{
	if (CanModifyXP)
	{
		int oldvalue;
		switch (level)
		{

		case LevelType::Main_L:

			oldvalue = GetMainLevelCurrentXP();

			switch (changetype)
			{

				case ChangeTypeLevel::Add_L:
					MainLevel.CurrentXP = FMath::Clamp(MainLevel.CurrentXP + amount, 0, MainLevel.MaxXP);
					if (HasEnoughXPToLevel(MainLevel.CurrentXP, MainLevel.NextLevelXP))
					{
						LevelUp(LevelType::Main_L, "");
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetMainLevel()) + ", Current XP: " + FString::FromInt(GetMainLevelCurrentXP()) + "Next Level XP: " + FString::FromInt(GetMainLevelNextLevelXP()) + "Previous Level XP: " + FString::FromInt(GetMainLevelPreviousLevelXP());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
					break;

				case ChangeTypeLevel::Remove_L:
					MainLevel.CurrentXP = FMath::Clamp(MainLevel.CurrentXP - amount, 0, MainLevel.MaxXP);
					if (HasEnoughXPToDownLevel(MainLevel.CurrentXP, MainLevel.PreviousLevelXP))
					{
						LevelDown(LevelType::Main_L, "");
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetMainLevel()) + ", Current XP: " + FString::FromInt(GetMainLevelCurrentXP()) + "Next Level XP: " + FString::FromInt(GetMainLevelNextLevelXP()) + "Previous Level XP: " + FString::FromInt(GetMainLevelPreviousLevelXP());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
					break;

				case ChangeTypeLevel::Change_L:
					MainLevel.CurrentXP = FMath::Clamp(amount, 0, MainLevel.MaxXP);
					if (HasEnoughXPToLevel(MainLevel.CurrentXP, MainLevel.NextLevelXP))
					{
						LevelUp(LevelType::Main_L, "");
					}
					else if (HasEnoughXPToDownLevel(MainLevel.CurrentXP, MainLevel.PreviousLevelXP))
					{
						LevelDown(LevelType::Main_L, "");
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetMainLevel()) + ", Current XP: " + FString::FromInt(GetMainLevelCurrentXP()) + "Next Level XP: " + FString::FromInt(GetMainLevelNextLevelXP()) + "Previous Level XP: " + FString::FromInt(GetMainLevelPreviousLevelXP());
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
					break;

					OnModifyXP.Broadcast(changetype, oldvalue, GetMainLevelCurrentXP(), amount);

			}
		break;

		case LevelType::Primary_L:

			oldvalue = GetPrimaryLevelCurrentXP(name);

			switch (changetype)
			{
				case ChangeTypeLevel::Add_L:
					PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP = FMath::Clamp(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP + amount, 0, PrimaryLevels[GetPrimaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToLevel(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP))
					{
						LevelUp(LevelType::Primary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetPrimaryLevel(name)) + ", Current XP: " + FString::FromInt(GetPrimaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetPrimaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetPrimaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
				break;

				case ChangeTypeLevel::Remove_L:
					PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP = FMath::Clamp(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP - amount, 0, PrimaryLevels[GetPrimaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToDownLevel(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP))
					{
						LevelDown(LevelType::Primary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetPrimaryLevel(name)) + ", Current XP: " + FString::FromInt(GetPrimaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetPrimaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetPrimaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
					break;
				
				case ChangeTypeLevel::Change_L:
					PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP = FMath::Clamp(amount, 0, PrimaryLevels[GetPrimaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToLevel(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP))
					{
						LevelUp(LevelType::Primary_L, name);
					}
					else if (HasEnoughXPToDownLevel(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP))
					{
						LevelDown(LevelType::Primary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetPrimaryLevel(name)) + ", Current XP: " + FString::FromInt(GetPrimaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetPrimaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetPrimaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
					break;

					OnModifyXP.Broadcast(changetype, oldvalue, GetPrimaryLevelCurrentXP(name), amount);

			}
		break;

		case LevelType::Secondary_L:

			oldvalue = GetSecondaryLevelCurrentXP(name);

			switch (changetype)
			{

				case ChangeTypeLevel::Add_L:
					SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP = FMath::Clamp(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP + amount, 0, SecondaryLevels[GetSecondaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToLevel(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP))
					{
						LevelUp(LevelType::Secondary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetSecondaryLevel(name)) + ", Current XP: " + FString::FromInt(GetSecondaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetSecondaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetSecondaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
				break;

				case ChangeTypeLevel::Remove_L:
					SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP = FMath::Clamp(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP - amount, 0, SecondaryLevels[GetSecondaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToDownLevel(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP))
					{
						LevelDown(LevelType::Secondary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetSecondaryLevel(name)) + ", Current XP: " + FString::FromInt(GetSecondaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetSecondaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetSecondaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
				break;

				case ChangeTypeLevel::Change_L:
					SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP = FMath::Clamp(amount, 0, SecondaryLevels[GetSecondaryLevelIndex(name)].MaxXP);
					if (HasEnoughXPToLevel(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP))
					{
						LevelUp(LevelType::Secondary_L, name);
					}
					else if (HasEnoughXPToDownLevel(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP))
					{
						LevelDown(LevelType::Secondary_L, name);
					}
					if (debug)
					{
						FString LevelString = "Level: " + FString::FromInt(GetSecondaryLevel(name)) + ", Current XP: " + FString::FromInt(GetSecondaryLevelCurrentXP(name)) + "Next Level XP: " + FString::FromInt(GetSecondaryLevelNextLevelXP(name)) + "Previous Level XP: " + FString::FromInt(GetSecondaryLevelPreviousLevelXP(name));
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, LevelString);
					}
				break;

				OnModifyXP.Broadcast(changetype, oldvalue, GetSecondaryLevelCurrentXP(name), amount);

			}
		break;
		}
	}



}

bool UBasicLevelComponent::HasEnoughXPToLevel(int current, int amountNeeded)
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

bool UBasicLevelComponent::HasRequiredLevel(LevelType level, FString name, int levelneeded)
{

	switch (level)
	{

	case LevelType::Main_L:
		if (levelneeded > GetMainLevel())
		{
			return false;
		}
		else
		{
			return true;
		}
		break;

	case LevelType::Primary_L:
		if (levelneeded > PrimaryLevels[GetPrimaryLevelIndex(name)].Level)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;

	case LevelType::Secondary_L:
		if (levelneeded > SecondaryLevels[GetSecondaryLevelIndex(name)].Level)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;	

	}
	return false;
}

bool UBasicLevelComponent::HasEnoughXPToDownLevel(int current, int amountNeeded)
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

void UBasicLevelComponent::SetCanModifyXP(bool canmodify)
{
	CanModifyXP = canmodify;
}

bool UBasicLevelComponent::GetCanModifyXP()
{
	return CanModifyXP;
}

int UBasicLevelComponent::GetLevelXPValueAsPercentage(LevelType level, FString name)
{

	switch (level)
	{

	case LevelType::Main_L:

		return Percentage(MainLevel.CurrentXP, MainLevel.PreviousLevelXP, MainLevel.NextLevelXP) * 100;
		break;

	case LevelType::Primary_L:

		return Percentage(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP, PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP) * 100;
		break;

	case LevelType::Secondary_L:

		return Percentage(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].PreviousLevelXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP) * 100;
		break;

	}
	return 0;
}

float UBasicLevelComponent::GetLevelXPValueForProgressBar(LevelType level, FString name)
{

	switch (level)
	{

	case LevelType::Main_L:

		return float(Percentage(MainLevel.CurrentXP, MainLevel.PreviousLevelXP, MainLevel.NextLevelXP)) / 100;
		break;

	case LevelType::Primary_L:

		return float(Percentage(PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP, PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP, PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP)) / 100;
		break;

	case LevelType::Secondary_L:

		return float(Percentage(SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP, SecondaryLevels[GetSecondaryLevelIndex(name)].PreviousLevelXP, SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP)) / 100;
		break;

	}
	return 0;

}

int UBasicLevelComponent::GetXPLeftUntilLevelUpAsPercentage(LevelType level, FString name)
{

	switch (level)
	{

	case LevelType::Main_L:
		return 100 - GetLevelXPValueAsPercentage(level, "");
		break;

	case LevelType::Primary_L:
		return 100 - GetLevelXPValueAsPercentage(level, name);
		break;

	case LevelType::Secondary_L:
		return 100 - GetLevelXPValueAsPercentage(level, name);
		break;

	}
	return 0;

}

int UBasicLevelComponent::GetXPLeftUntilLevelUp(LevelType level, FString name)
{

	switch (level)
	{
	case LevelType::Main_L:
		return MainLevel.NextLevelXP - MainLevel.CurrentXP;
		break;

	case LevelType::Primary_L:
		return PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP - PrimaryLevels[GetPrimaryLevelIndex(name)].CurrentXP;
		break;

	case LevelType::Secondary_L:
		return SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP - SecondaryLevels[GetSecondaryLevelIndex(name)].CurrentXP;
		break;
	}
	return 0;
}

bool UBasicLevelComponent::IsPlayer()
{

	switch (Owner)
	{
		case OwnerTypeLevel::Player_L:
			return true;
		break;

		case OwnerTypeLevel::AI_L:
			return false;
		break;
	}

	return true;
}

void UBasicLevelComponent::LevelUp(LevelType level, const FString& name)
{

	FString NextLevelString;
	FName NextLevelName;
	FLevelInfo* Row;

	switch (level)
	{

	case LevelType::Main_L:
		if (!IsMaxLevel(LevelType::Main_L, ""))
		{
			MainLevel.Level++;
			NextLevelString = FString::FromInt(MainLevel.Level);
			NextLevelName = FName(*NextLevelString);
			Row = LevelInfo->FindRow<FLevelInfo>(FName(NextLevelName), "", true);
			if (Row)
			{
				MainLevel.NextLevelXP = Row->NextLevelXP;
				MainLevel.PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Next Level not found!");
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Max Level!");
		}
		break;

	case LevelType::Primary_L:
		if (!IsMaxLevel(LevelType::Primary_L, name))
		{
			PrimaryLevels[GetPrimaryLevelIndex(name)].Level++;
			NextLevelString = FString::FromInt(PrimaryLevels[GetPrimaryLevelIndex(name)].Level);
			NextLevelName = FName(*NextLevelString);
			Row = PrimaryLevelInfo->FindRow<FLevelInfo>(FName(NextLevelName), "", true);
			if (Row)
			{
				PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP = Row->NextLevelXP;
				PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Next Level not found!");
			}
		}
		break;

	case LevelType::Secondary_L:
		if (!IsMaxLevel(LevelType::Secondary_L, name))
		{
			SecondaryLevels[GetSecondaryLevelIndex(name)].Level++;
			NextLevelString = FString::FromInt(SecondaryLevels[GetSecondaryLevelIndex(name)].Level);
			NextLevelName = FName(*NextLevelString);
			Row = SecondaryLevelInfo->FindRow<FLevelInfo>(FName(NextLevelName), "", true);
			if (Row)
			{
				SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP = Row->NextLevelXP;
				SecondaryLevels[GetSecondaryLevelIndex(name)].PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Next Level not found!");
			}
		}
		break;

	}

	if (PlaySound == true && IsValid(LevelUpSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LevelUpSound, GetOwner()->GetActorLocation() , 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}

	OnLevelUp.Broadcast();

}

void UBasicLevelComponent::LevelDown(LevelType level, const FString& name)
{

	FString PreviousLevelString;
	FName PreviousLevelName;
	FLevelInfo* Row;

	switch (level)
	{
	case LevelType::Main_L:
		if (GetMainLevel() == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Min Level!");
		}
		else
		{
			MainLevel.Level--;
			PreviousLevelString = FString::FromInt(MainLevel.Level);
			PreviousLevelName = FName(*PreviousLevelString);
			Row = LevelInfo->FindRow<FLevelInfo>(FName(PreviousLevelName), "", true);
			if (Row)
			{
				MainLevel.NextLevelXP = Row->NextLevelXP;
				MainLevel.PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Previous Level not found!");
			}
		}
		break;

	case LevelType::Primary_L:
		if (GetPrimaryLevelByName(name).Level == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Min Level!");
		}
		else
		{
			PrimaryLevels[GetPrimaryLevelIndex(name)].Level--;
			PreviousLevelString = FString::FromInt(PrimaryLevels[GetPrimaryLevelIndex(name)].Level);
			PreviousLevelName = FName(*PreviousLevelString);
			Row = LevelInfo->FindRow<FLevelInfo>(FName(PreviousLevelName), "", true);
			if (Row)
			{
				PrimaryLevels[GetPrimaryLevelIndex(name)].NextLevelXP = Row->NextLevelXP;
				PrimaryLevels[GetPrimaryLevelIndex(name)].PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Previous Level not found!");
			}
		}
		break;

	case LevelType::Secondary_L:
		if (GetSecondaryLevelByName(name).Level == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Min Level!");
		}
		else
		{
			SecondaryLevels[GetSecondaryLevelIndex(name)].Level--;
			PreviousLevelString = FString::FromInt(SecondaryLevels[GetSecondaryLevelIndex(name)].Level);
			PreviousLevelName = FName(*PreviousLevelString);
			Row = LevelInfo->FindRow<FLevelInfo>(FName(PreviousLevelName), "", true);
			if (Row)
			{
				SecondaryLevels[GetSecondaryLevelIndex(name)].NextLevelXP = Row->NextLevelXP;
				SecondaryLevels[GetSecondaryLevelIndex(name)].PreviousLevelXP = Row->PreviousLevelXP;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Previous Level not found!");
			}
		}
		break;
	}

	if (PlaySound == true && IsValid(LevelDownSound) == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LevelDownSound, GetOwner()->GetActorLocation() , 1.0f, 1.0f, 0.0f, nullptr, nullptr);
	}

	OnLevelDown.Broadcast();

}
	