#include "Object.h"
 class Character:public Object
{
	public:
		Character();
		~Character();
		int Walking_Time_Tick;
		virtual void HittingEvent();
}_Player;
Character::Character()
{
	Walking_Time_Tick = 0;
	FacingDirection = FACING_DOWN;
	Radius = 5.0;

}
void Character::HittingEvent()
{
	
}
Character::~Character()
{

}
