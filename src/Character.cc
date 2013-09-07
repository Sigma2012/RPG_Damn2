#include "Character.h"
#define NULL 0
Character * Character::instance_ = NULL;

Character::Character()
{
    //主角坐标初始化
	pos.dx = 1.0f;
	pos.dy = 1.0f;
	///////////////////////
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
