#include "Object.h"
Object::Object()
{
 	pos.dx=0.0;
	pos.dy=0.0;
	FacingDirection=FACING_DOWN;
	Radius=0.0;
	Lable=0;
}

Object::~Object()
{

}
void Object::HittingEvent()
{
}

