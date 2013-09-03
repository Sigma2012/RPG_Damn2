#include "Controller.h"
#include "Model.h"
#include <QtGui/QKeyEvent>

Controller::Controller()
{
	model = Model::getInstance();
	}

Controller::~Controller()
{
	}

void Controller::key_press(int key)
{
	switch(key)
	{
	case Qt::Key_Down:
		model->y += 0.1f;
		break;
	case Qt::Key_Right:
		model->x += 0.1f;
		break;
	case Qt::Key_Left:
		model->x -= 0.1f;
		break;
	case Qt::Key_Up:
		model->y -= 0.1f;
		break;
	default:
		break;
		}
	}
