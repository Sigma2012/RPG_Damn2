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
        cheche->FacingDirection = 3;
		cheche->pos.dy += 0.1f;
		model->map_y -= 0.1f;
		model->cha_x = pos_trans_x(cheche->pos.dx);
		model->cha_y = pos_trans_y(cheche->pos.dy);
        break;
	case Qt::Key_Right:
        cheche->FacingDirection = 2;
		cheche->pos.dx += 0.1f;
		model->map_x -= 0.1f;
		model->cha_x = pos_trans_x(cheche->pos.dx);
		model->cha_y = pos_trans_y(cheche->pos.dy);
        break;
	case Qt::Key_Left:
        cheche->FacingDirection = 4;
		cheche->pos.dx -= 0.1f;
		model->map_x += 0.1f;
		model->cha_x = pos_trans_x(cheche->pos.dx);
		model->cha_y = pos_trans_y(cheche->pos.dy);
        break;
	case Qt::Key_Up:
        cheche->FacingDirection = 1;
		cheche->pos.dy -= 0.1f;
		model->map_y += 0.1f;
		model->cha_x = pos_trans_x(cheche->pos.dx);
		model->cha_y = pos_trans_y(cheche->pos.dy);
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

void Controller::update_queue()
{
	model->cha_num = 3-(cheche->Walking_Time_Tick/7);
	switch (cheche->FacingDirection)
	{
		case 1:model->cha_id = model->save[0+model->cha_num];break;
		case 2:model->cha_id = model->save[4+model->cha_num];break;
		case 3:model->cha_id = model->save[8+model->cha_num];break;
		case 4:model->cha_id = model->save[12+model->cha_num];break;
		default:break;
	}
	model->Drawing_Queue.push(Image_Info(model->map_x, model->map_y,2,2,model->map_id));
	model->Drawing_Queue.push(Image_Info(model->cha_x, model->cha_y,0.08f,0.145f,model->cha_id));
	if (model->ConverSeq!=NULL)
	{
		model->Drawing_Queue.push(Image_Info(0,0.5,1,0.5,model->ConverSeq->Conversation_Sequence[Counter]));
		Counter++;
		if (Counter==model->ConverSeq->Conversation_Sequence.size())
		{
			delete(model->ConverSeq);
			ConverSeq=NULL;
		}
	}
}	

float Controller::pos_trans_x(float x)
{
	return model->map_x + x;
	}

float Controller::pos_trans_y(float y)
{
	return model->map_y + y;
	}
