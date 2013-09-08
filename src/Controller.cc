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
    switch(model->Window_Status)
	{
		case MAIN_MENU_STATUS:			//从这里开始是主菜单的键盘响应界面
        {
            
            
            break;
		}
        case MAIN_GAME_STATUS:			//从这里开始是主要游戏界面的响应
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
                case Qt::Key_Escape:
                    model->Window_Status = CALLING_MENU_STATUS;
                    break;
                default:
                    break;
            }
            if (!cheche->Leg_Condition)
            {
                cheche->Leg_Condition = 1;
                if (!cheche->Walking_Time_Tick) cheche->Walking_Time_Tick+=27;
            }
            break;
        }
		case DIALOGUE_STATUS:		//从这里开始是和NPC进行对话的状态下的键盘响应
		{
            switch(key)
            {
                case Qt::Key_Space:
                    model->ConverSeq->Counter++;
                    
                    break;
                default:
                    break;
                    
            }
            break;
        }
		case CALLING_MENU_STATUS:	//从这里开始是在游戏界面下按下菜单界面的键盘响应
        {
            
            switch(key)
            {
                case Qt::Key_Escape:
                    model->Window_Status = MAIN_GAME_STATUS;
                    
                    break;
                default:
                    break;
                    
            }
            break;
		}
        default:
			break;
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
		model->Drawing_Queue.push(Image_Info(0,0.5,1,0.5,model->ConverSeq->Conversation_Sequence[model->ConverSeq->Counter]));
		model->ConverSeq->Counter++;
		if (model->ConverSeq->Counter==model->ConverSeq->Conversation_Sequence.size())
		{
			delete(model-> ConverSeq);
			model->ConverSeq=NULL;
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
