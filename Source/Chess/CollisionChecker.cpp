// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionChecker.h"

// Sets default values
ACollisionChecker::ACollisionChecker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollisionChecker::BeginPlay()
{
	Super::BeginPlay();

	//make a box component that checks overlap
}

// Called every frame
void ACollisionChecker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionChecker::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check the locations of objects hit at given location, if it hits something before reaching its desired location, return false.
}

