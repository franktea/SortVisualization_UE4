// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <utility>
#include "Sorter.generated.h"

UCLASS()
class BUBBLESORT_API ASorter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASorter();

    UPROPERTY()
    class USceneComponent* Scene;
    
    UPROPERTY()
    TArray<class AItem*> Items;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
    const int ItemCount = 100;
    const int ItemWidth = 20; // 10cm
    std::vector<std::pair<int, class AItem*>> SortArray;
private: // variables for sorting
    /* my sort function
     void Sort(vector<int>& v)
     {
         for(int i = int(v.size()) - 1; i >= 0; --i)
         {
             for(int j = 0; j < i; ++j)
             {
                 if(v[j] > v[j+1])
                 {
                     swap(v[j], v[j+1]);
                 }
             }
         }
     }
     */
    bool Stopped = true;
    int Loop_i = 0;
    int Loop_j = 0;
    const float Interval = 0.016;
    float Elapsed = 0.0f;
    
    // compare two items each time
    //class AItem* SmallerItem = nullptr; // smaller item, set color to green
    class AItem* BiggerItem = nullptr; // bigger item, set color to red
};
