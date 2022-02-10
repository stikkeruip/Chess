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

	//SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	//SkeletalMeshComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(SkeletalMeshComponent);	
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBlack(TEXT("Material'/Game/StarterContent/Materials/M_Basic_Floor.M_Basic_Floor'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialWhite(TEXT("Material'/Game/StarterContent/Props/Materials/M_MaterialSphere_Plain.M_MaterialSphere_Plain'"));
	MaterialB = MaterialBlack.Object;
	MaterialW = MaterialWhite.Object;

	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialBlackPawn(TEXT("MaterialInstanceConstant'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Materials/Super/MI_Minion_Dusk_Super.MI_Minion_Dusk_Super'"));
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialWhitePawn(TEXT("Material'/Game/ParagonMinions/Characters/Minions/Down_Minions/Materials/Shared/M_Dawn_Minion_MASTER.M_Dawn_Minion_MASTER'"));
	//MaterialB_P = MaterialBlackPawn.Object;
	//MaterialW_P = MaterialWhitePawn.Object;

	
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Pawn(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Castle(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Bishop(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Queen(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Wedge_A.Shape_Wedge_A'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>King(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Knight(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Wedge_B.Shape_Wedge_B'"));
	PawnMesh = Pawn.Object;
	CastleMesh = Castle.Object;
	BishopMesh = Bishop.Object;
	QueenMesh = Queen.Object;
	KingMesh = King.Object;
	KnightMesh = Knight.Object;
	
	
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

void APiece::ChangeMaterial(EColour Colour, EPieceType Piece)
{
	if (Colour == EColour::C_Black)
	{
		StaticMeshComponent->SetMaterial(0, MaterialB);
	}
	if (Colour == EColour::C_White)
	{
		StaticMeshComponent->SetMaterial(0, MaterialW);
	}
	//if (Piece == EPieceType::PT_Pawn && Colour == EColour::C_Black)
	//{
	//	SkeletalMeshComponent->SetMaterial(0, MaterialB_P);
	//}
	//if (Piece == EPieceType::PT_Pawn && Colour == EColour::C_White)
	//{
	//	SkeletalMeshComponent->SetMaterial(0, MaterialW_P);
	//}
	
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
	if (Piece == EPieceType::PT_Bishop)
	{
		StaticMeshComponent->SetStaticMesh(BishopMesh);
	}
	if (Piece == EPieceType::PT_Queen)
	{
		StaticMeshComponent->SetStaticMesh(QueenMesh);
	}
	if (Piece == EPieceType::PT_King)
	{
		StaticMeshComponent->SetStaticMesh(KingMesh);
	}
	if (Piece == EPieceType::PT_Knight)
	{
		StaticMeshComponent->SetStaticMesh(KnightMesh);
	}
}

void APiece::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MovementComponent = OtherActor->FindComponentByClass<UPieceMovementComponent>();

	if(MovementComponent && MovementComponent->GetColour() != FindComponentByClass<UPieceMovementComponent>()->GetColour())
		OtherActor->Destroy();
	
}


