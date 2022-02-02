// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

#include "PieceMovementComponent.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StaticMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(SkeletalMeshComponent);	
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBlack(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialWhite(TEXT("Material'/Game/StarterContent/Props/Materials/M_MaterialSphere_Plain.M_MaterialSphere_Plain'"));
	MaterialB = MaterialBlack.Object;
	MaterialW = MaterialWhite.Object;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Pawn(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Castle(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	PawnMesh = Pawn.Object;
	CastleMesh = Castle.Object;
	
	
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APiece::BeginOverlap);
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APiece::ChangeMaterial(EColour Colour)
{
	if (Colour == EColour::C_Black)
	{
		SkeletalMeshComponent->SetMaterial(0, MaterialB);
	}
	if (Colour == EColour::C_White)
	{
		SkeletalMeshComponent->SetMaterial(0, MaterialW);
	}
}

void APiece::ChangeMesh(EPieceType Piece)
{
	if (Piece == EPieceType::PT_Pawn)
	{
		SkeletalMeshComponent->SetSkeletalMesh(PawnMesh);
	}
	if (Piece == EPieceType::PT_Castle)
	{
		SkeletalMeshComponent->SetSkeletalMesh(CastleMesh);
	}
}

void APiece::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MovementComponent = OtherActor->FindComponentByClass<UPieceMovementComponent>();

	if(MovementComponent && MovementComponent->GetColour() != FindComponentByClass<UPieceMovementComponent>()->GetColour())
		OtherActor->Destroy();
	
}


