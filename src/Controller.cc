#include "Controller.h"
#include "Model.h"
#include "Character.h"
#include <QtGui/QKeyEvent>




Controller::Controller()
{
	model = Model::getInstance();
	cheche = Character::getInstance();
	}

Controller::~Controller()
{
	}

void Controller::key_press(int key)
{
    switch(key) 
	{
	case Qt::Key_Down:
		/*
        cheche->pos.dy += 0.1f;
		cheche->FacingDirection = 3;
 		*/
        //cheche->pos.dy += 0.1f;
        cheche->FacingDirection = 3;
        //////////////////////////////
        model->map_y -=0.1f;
        /////////////////////////////
        break;
	case Qt::Key_Right:
        //cheche->pos.dx += 0.1f;
        cheche->FacingDirection = 2;
        ///////////////////////////////////
        model->map_x -= 0.1f;
        ///////////////////////////////////
        break;
	case Qt::Key_Left:
        //cheche->pos.dx -= 0.1f;
        cheche->FacingDirection = 4;
        ///////////////////////////////////
        model->map_x += 0.1f;
        ///////////////////////////////////
        break;
	case Qt::Key_Up:
        //cheche->pos.dy -= 0.1f;
        cheche->FacingDirection = 1;
        //////////////////////////////////
        model->map_y += 0.1f;
        //////////////////////////////////
        break;
	default:
		break;
		}
    if (!cheche->Leg_Condition)
	{
	    cheche->Leg_Condition = 1;
		if (!cheche->Walking_Time_Tick) cheche->Walking_Time_Tick+=27;
	}
	}
