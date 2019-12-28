// Fill out your copyright notice in the Description page of Project Settings.


#include "Sorter.h"
#include "Item.h"
#include <algorithm>
#include <random>

// Sets default values
ASorter::ASorter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    RootComponent = Scene;
}

// Called when the game starts or when spawned
void ASorter::BeginPlay()
{
	Super::BeginPlay();
    
    SortArray.resize(ItemCount);
    for(size_t i = 0; i < SortArray.size(); ++i)
    {
        SortArray[i].first = i + 1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(SortArray.begin(), SortArray.end(), g);
    Loop_i = int(SortArray.size()) - 1;
    Loop_j = 0;
    
    for(int i = 0; i < ItemCount; ++i)
    {
        FVector Location = GetActorLocation();
        Location.Y += i * ItemWidth;
        AItem* Item = GetWorld()->SpawnActor<AItem>(Location, GetActorRotation());
        Item->SetActorScale3D(FVector(10.0f, 1.8f, 1.0*SortArray[i].first));
        SortArray[i].second = Item;
        Items.Add(Item);
    }
    
    FTimerHandle UnusedHandle;
    FTimerDelegate TimerCallback;
    TimerCallback.BindLambda([this](){ Stopped = false; });
    GetWorld()->GetTimerManager().SetTimer(UnusedHandle, TimerCallback, 5.0, false);
}

// Called every frame
void ASorter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(Stopped)
    {
        return;
    }
    
    Elapsed += DeltaTime;
    if(Elapsed < Interval)
    {
        return;
    }
    
    Elapsed = 0.0f;
    
    if(Loop_j >= Loop_i)
    {
        if(BiggerItem)
        {
            BiggerItem->SetSortedColor();
            BiggerItem = nullptr;
        }
        
        --Loop_i;
        if(Loop_i < 0)
        {
            SortArray[0].second->SetSortedColor();
            Stopped = true;
            return;
        }
        
        for(int i = 0; i < Loop_i; ++i)
        {
            SortArray[i].second->SetDefaultColor();
        }
        
        Loop_j = 0;
        return;
    }

    AItem* Bigger = nullptr;
    if(SortArray[Loop_j] > SortArray[Loop_j + 1])
    {
        Bigger = SortArray[Loop_j].second;
        SortArray[Loop_j + 1].second->SetHighlightColor();
        FVector L1 = SortArray[Loop_j].second->GetActorLocation();
        FVector L2 = SortArray[Loop_j + 1].second->GetActorLocation();
        SortArray[Loop_j + 1].second->SetActorLocation(L1);
        SortArray[Loop_j].second->SetActorLocation(L2);
        std::swap(SortArray[Loop_j], SortArray[Loop_j + 1]);
    }
    else
    {
        Bigger = SortArray[Loop_j + 1].second;
    }
    
    if(BiggerItem != Bigger)
    {
        if(BiggerItem)
        {
            BiggerItem->SetDefaultColor();
        }
        BiggerItem = Bigger;
        BiggerItem->SetCurrentMaxColor();
    }
    
    ++Loop_j;
}
