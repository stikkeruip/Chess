// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

#include "PieceMovementComponent.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);	
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBlack(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialWhite(TEXT("Material'/Game/StarterContent/Props/Materials/M_MaterialSphere_Plain.M_MaterialSphere_Plain'"));
	MaterialB = MaterialBlack.Object;
	MaterialW = MaterialWhite.Object;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Pawn(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Castle(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
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
		StaticMeshComponent->SetMaterial(0, MaterialB);
	}
	if (Colour == EColour::C_White)
	{
		StaticMeshComponent->SetMaterial(0, MaterialW);
	}
}

void APiece::ChangeMesh(EPieceType Piece)
{
	if (Piece == EPieceType::PT_Pawn)
	{
		StaticMeshComponent->SetStaticMesh(PawnMesh);
	}
	if (Piece == EPieceType::PT_Castle)
	{
		StaticMeshComponent->SetStaticMesh(CastleMesh);
	}
}

void APiece::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MovementComponent = OtherActor->FindComponentByClass<UPieceMovementComponent>();

	if(MovementComponent && MovementComponent->GetColour() != FindComponentByClass<UPieceMovementComponent>()->GetColour())
		OtherActor->Destroy();
	
}


