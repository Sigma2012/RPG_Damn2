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
		cheche->pos.dy += 0.1f;
		cheche->FacingDirection = 3;
 		break;
	case Qt::Key_Right:
		cheche->pos.dx += 0.1f;
		cheche->FacingDirection = 2;
		break;
	case Qt::Key_Left:
		cheche->pos.dx -= 0.1f;
		cheche->FacingDirection = 4;
		break;
	case Qt::Key_Up:
		cheche->pos.dy -= 0.1f;
		cheche->FacingDirection = 1;
		break;
	default:
		break;
		}
	}
