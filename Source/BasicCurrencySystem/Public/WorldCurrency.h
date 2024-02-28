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
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "WorldCurrency.generated.h"



UENUM(Blueprintable)
enum CurrencyTypes
{

	M UMETA(DisplayName = "Main"),
	S UMETA(DisplayName = "Secondary"),
	Sp UMETA(DisplayName = "Special")

};

USTRUCT(Blueprintable)
struct FCurrencyDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Currency")
		TEnumAsByte<CurrencyTypes> CurrencyType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		int CurrentAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		bool CanUse = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency")
		bool CanDestroy = false;
};

UCLASS()
class BASICCURRENCYSYSTEM_API AWorldCurrency : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldCurrency();

	//Components main currency
	UPROPERTY(EditAnywhere, Category = "Currency")
		class UStaticMeshComponent* MeshComponent;

	//create trigger capsule
	UPROPERTY(EditAnywhere, Category = "Currency")
		class USphereComponent* TriggerSphere;

	//Details for the currency we are dropping
	UPROPERTY(EditAnywhere, Category = "Currency")
		FCurrencyDetails Details;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
