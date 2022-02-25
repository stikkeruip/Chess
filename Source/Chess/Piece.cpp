// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"

#include "PieceMovementComponent.h"

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	//StaticMeshComponent->SetupAttachment(RootComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	
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

	
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Pawn(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Castle(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Bishop(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Queen(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>King(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>Knight(TEXT("SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));
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
		SkeletalMeshComponent->SetMaterial(0, MaterialB);
	}
	if (Colour == EColour::C_White)
	{
		SkeletalMeshComponent->SetMaterial(0, MaterialW);
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
		SkeletalMeshComponent->SetSkeletalMesh(PawnMesh);
	}
	if (Piece == EPieceType::PT_Castle)
	{
		SkeletalMeshComponent->SetSkeletalMesh(CastleMesh);
	}
	if (Piece == EPieceType::PT_Bishop)
	{
		SkeletalMeshComponent->SetSkeletalMesh(BishopMesh);
	}
	if (Piece == EPieceType::PT_Queen)
	{
		SkeletalMeshComponent->SetSkeletalMesh(QueenMesh);
	}
	if (Piece == EPieceType::PT_King)
	{
		SkeletalMeshComponent->SetSkeletalMesh(KingMesh);
	}
	if (Piece == EPieceType::PT_Knight)
	{
		SkeletalMeshComponent->SetSkeletalMesh(KnightMesh);
	}
}

bool APiece::GetFirstMove()
{
	return this->FindComponentByClass<UPieceMovementComponent>()->GetFirstMove();
}


