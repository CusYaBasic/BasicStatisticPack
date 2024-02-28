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


#include "WorldCurrency.h"
#include "BasicCurrencyComponent.h"

// Sets default values
AWorldCurrency::AWorldCurrency()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a mesh component and attach it to the root component, we use SetupAttachment over AttachToComponent when setting defaults in the constructor, use AttachToComponent after construction
	//Thanks to @Blenky for pointing this out
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	
	//Set the mobility to movable so gravity can effect it to give a drop vibe when it's spawned
	MeshComponent->SetMobility(EComponentMobility::Movable);

	//Make our mesh component the root
	SetRootComponent(MeshComponent);

	//Create a sphere component and attach it to the mesh component, we use SetupAttachment over AttachToComponent when setting defaults in the constructor, use AttachToComponent after construction
	//Thanks to @Blenky for pointing this out
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere"));
	TriggerSphere->SetupAttachment(MeshComponent);

	//Set the sphere and add the overlap event
	TriggerSphere->InitSphereRadius(120.0f);
	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AWorldCurrency::OnOverlapBegin);

	//Cast to our primitive component and set physics so gravity can effect it
	UPrimitiveComponent* prim = Cast<UPrimitiveComponent>(this->GetComponentByClass(UPrimitiveComponent::StaticClass()));
	prim->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AWorldCurrency::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldCurrency::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWorldCurrency::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//Check if our overlapping actor has a currency component
	if (IsValid(OtherActor->GetComponentByClass(UBasicCurrencyComponent::StaticClass())))
	{

		//Get a reference to our currency component
		UBasicCurrencyComponent* comp = Cast<UBasicCurrencyComponent>(OtherActor->GetComponentByClass(UBasicCurrencyComponent::StaticClass()));

		//Check if the currency drop is usable (we check that it's usable so multiple players can't pick up the same currency drop before it gets destroyed
		if (Details.CanUse)
		{
			//Set CanUse to false to avoid dupes
			Details.CanUse = false;

			//we use a enum to switch our flow depending on currency
			switch (Details.CurrencyType)
			{

				//if main currency
				case CurrencyTypes::M:

					//Add to the currency components main currency
					comp->ModifyCurrency(CurrencyType::Main_C, Details.Name, CurrencyChangeType::Add_C, Details.CurrentAmount, false);

					break;

				//if secondary currency
				case CurrencyTypes::S:

					//Add to the currency components secondary currency
					comp->ModifyCurrency(CurrencyType::Secondary_C, Details.Name, CurrencyChangeType::Add_C, Details.CurrentAmount, false);

					break;
				//if special currency
				case CurrencyTypes::Sp:

					//Add to the currency components special currency
					comp->ModifyCurrency(CurrencyType::Special_C, Details.Name, CurrencyChangeType::Add_C, Details.CurrentAmount, false);

					break;

			}

		}

		//Check if we should destory the spawned actor
		if (Details.CanDestroy)
		{
			Destroy();
		}
		
	}

		
	
}

//I didn't actually need this, but you guys might
void AWorldCurrency::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}