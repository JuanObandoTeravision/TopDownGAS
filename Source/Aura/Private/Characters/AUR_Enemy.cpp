// Copyright Teravision Games


#include "Characters/AUR_Enemy.h"
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

AAUR_Enemy::AAUR_Enemy()
{
	bIsHighlighted = false;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::HighlightActor()
{
	bIsHighlighted = true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void AAUR_Enemy::UnHighlightActor()
{
	bIsHighlighted = false;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
