#include "Object.h"
 class Character:public Object
{
	public:
		Character();
		~Character();
		int Walking_Time_Tick;
		
}_Player;
Character::Character()
{
	Walking_Time_Tick = 0;
	FacingDirection = FACING_DOWN;
	Radius = 5.0;

}
Character::HittingEvent()
{
	
}
Character::~Character()
{

}
