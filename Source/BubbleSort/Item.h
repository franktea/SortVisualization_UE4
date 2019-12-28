// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class BUBBLESORT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
    
    UPROPERTY(EditAnywhere, Category="Mesh")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY()
    class UMaterial* RedMaterial;
    
    UPROPERTY()
    class UMaterial* GreenMaterial;
    
    UPROPERTY()
    class UMaterial* BlueMaterial;
    
    UPROPERTY()
    class UMaterial* YellowMaterial;

    void SetDefaultColor();
    void SetCurrentMaxColor();
    void SetHighlightColor();
    void SetSortedColor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
