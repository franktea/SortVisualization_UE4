// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("StaticMesh'/Game/Mesh/box.box'"));
    if(Asset.Succeeded())
    {
        Mesh->SetStaticMesh(Asset.Object);
    }
    
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_Red;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_Green;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_Blue;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_Yellow;
        FConstructorStatics()
            : Color_Red(TEXT("Material'/Game/Material/Red.Red'"))
            , Color_Green(TEXT("Material'/Game/Material/Green.Green'"))
            , Color_Blue(TEXT("Material'/Game/Material/Blue.Blue'"))
            , Color_Yellow(TEXT("Material'/Game/Material/Yellow.Yellow'"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    RedMaterial = ConstructorStatics.Color_Red.Get();
    GreenMaterial = ConstructorStatics.Color_Green.Get();
    BlueMaterial = ConstructorStatics.Color_Blue.Get();
    YellowMaterial = ConstructorStatics.Color_Yellow.Get();
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
    Mesh->SetMaterial(0, YellowMaterial);
}

void AItem::SetDefaultColor()
{
    Mesh->SetMaterial(0, YellowMaterial);
}

void AItem::SetCurrentMaxColor()
{
    Mesh->SetMaterial(0, RedMaterial);
}

void AItem::SetHighlightColor()
{
    Mesh->SetMaterial(0, GreenMaterial);
}

void AItem::SetSortedColor()
{
    Mesh->SetMaterial(0, BlueMaterial);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

