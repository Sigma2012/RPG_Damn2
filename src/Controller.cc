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

float Controller::sqr(float a)
{
	return a*a;
}

float Controller::Pos_Distance(float ax,float ay,float bx,float by)
{
	return sqrt(sqr(ax-bx)+sqr(ay-by));
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
            float Virtual_x(cheche->pos.dx),Virtual_y(cheche->pos.dy);
			switch(key)
            {
                case Qt::Key_Down:
					cheche->FacingDirection = 3;
                    Virtual_y += 0.1f;
                    break; 
                case Qt::Key_Right:
					cheche->FacingDirection = 2;
                    Virtual_x += 0.1f;
                    break; 
                case Qt::Key_Left:
					cheche->FacingDirection = 4;
                    Virtual_x-= 0.1f; 
                    break;
                case Qt::Key_Up:
					cheche->FacingDirection = 1;
                    Virtual_y -= 0.1f;
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
#define Collision 0.01
			bool flag_for_event=0;
		    for (int i(0);i<model->NPC_Sum;++i)
			{
                float Distance = 10;
                Distance=Pos_Distance(model->NPC_Saver[i].pos.dx,
                                      model->NPC_Saver[i].pos.dy,
                                      Virtual_x,
                                      Virtual_y);
                if (Distance<Collision)//说明撞到了NPC
				{
					model->NPC_Saver[i].HittingEvent();
					flag_for_event = 1;
					model->Window_Status=DIALOGUE_STATUS;
					break;
				}
			}
            //说明我们没有撞到NPC，按照正常的方法去更新整个地图
			if (!flag_for_event)
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
    //从这里以下是为了判断人物是否要产生移动，如果有的话
	model->cha_num = 3-(cheche->Walking_Time_Tick/7);
	switch (cheche->FacingDirection)
	{
		case 1:model->cha_id = model->save[0+model->cha_num];break;
		case 2:model->cha_id = model->save[4+model->cha_num];break;
		case 3:model->cha_id = model->save[8+model->cha_num];break;
		case 4:model->cha_id = model->save[12+model->cha_num];break;
		default:break;
	}
    //从这里往下我们开始往贴图队列放置地图
	{
        model->Drawing_Queue.push(Image_Info(model->map_x, model->map_y,2,2,model->map_id));
	}
    //从这里往下我们开始往贴图队列放置玩家
	{
        model->Drawing_Queue.push(Image_Info(model->cha_x, model->cha_y,0.08f,0.145f,model->cha_id));
	}
    //从这里往下我们开始往贴图队列放置地图上的NPC
	{
        for (int i(0);i<model->NPC_Sum;++i)
		{
			if (model->NPC_Saver[i].Map_Belonging==model->map_num)
			{
				model->Drawing_Queue.push(Image_Info(pos_trans_x(model->NPC_Saver[i].pos.dx),pos_trans_y(model->NPC_Saver[i].pos.dy),0.08f,0.145f,model->NPC_Saver[i].Map_Drawing_Picture));
			}
		}
        
	}
    
    
    //从这里往下我们开始往贴图队列放置对话，如果有的话
	if ((model->ConverSeq!=NULL)&&(model->ConverSeq->Counter==model->ConverSeq->Conversation_Sequence.size()))
	{
		delete(model -> ConverSeq);
		model->ConverSeq=NULL;
		model->Window_Status = MAIN_GAME_STATUS;
	}
	
	if (model->ConverSeq!=NULL)
	{
		model->Drawing_Queue.push(Image_Info(0,0.5,1,0.5,model->ConverSeq->Conversation_Sequence[model->ConverSeq->Counter]));
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
