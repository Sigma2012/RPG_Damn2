#include "Character.h"
#define NULL 0
Character * Character::instance_ = NULL;

Character::Character()
{
	Walking_Time_Tick = 0;
	FacingDirection =FACING_DOWN;
	Radius = 5.0;
}
void Character::HittingEvent()
{
	
}
Character::~Character()
{

}

Character* Character::getInstance()
{
	if(instance_ == NULL)
		{
		instance_ = new Character;
		}
	return instance_;
}
