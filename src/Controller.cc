#include "Controller.h"
#include "Model.h"
#include "Character.h"
#include <QtGui/QKeyEvent>
#define STEP 0.05

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
	model->Last_Key = key;
    switch(model->Window_Status)
	{
		case MAIN_MENU_STATUS:			//从这里开始是主菜单的键盘响应界面
        {
			switch(key)
			{
				case Qt::Key_Down:
					model->sta_num = (model->sta_num + 1) % 4;
					model->sta_id = model->map_id[model->sta_num + 3];
					break;
				case Qt::Key_Up:
					model->sta_num = (model->sta_num + 3) % 4;
					model->sta_id = model->map_id[model->sta_num + 3];
					break;
				case Qt::Key_Return:
					switch(model->sta_num)
					{
						case 0:
						case 1:
							model->Window_Status = MAIN_GAME_STATUS;
							model->map_num = 11;
				  			break;
						case 2:break;
						case 3:exit(0);
							break;
				 		}
				 	break;
				default:
				 	break;
			}
			break; 
		}
        case MAIN_GAME_STATUS:			//从这里开始是主要游戏界面的响应
        {
            float Virtual_x(cheche->pos.dx),Virtual_y(cheche->pos.dy);
			switch(key)
            {
                case Qt::Key_Down:
					cheche->FacingDirection = 3;
                    Virtual_y += STEP;
                     break; 
                case Qt::Key_Right:
					cheche->FacingDirection = 2;
                    Virtual_x += STEP;
                    break; 
                case Qt::Key_Left:
					cheche->FacingDirection = 4;
                    Virtual_x -= STEP; 
                    break;
                case Qt::Key_Up:
					cheche->FacingDirection = 1;
                    Virtual_y -= STEP;
                    break; 
                case Qt::Key_Escape:
					model->Before = model->map_num;	
                    model->Window_Status = CALLING_MENU_STATUS;
					model->map_num = 7;
                    break;
                default: 
                    break;
            }
            if (!cheche->Leg_Condition)
            {
                cheche->Leg_Condition = 1;
                 if (!cheche->Walking_Time_Tick) cheche->Walking_Time_Tick+=27;
            }
#define Collision 0.07
			bool flag_for_event=0;
		    for (int i(0);i<model->NPC_Sum;++i)
			{
				if ((model->NPC_Saver[i].Map_Belonging < -50)||(!model->NPC_Saver[i].Exist_Flag)||(model->map_num!=model->NPC_Saver[i].Map_Belonging)) continue;
                if ((model->NPC_Saver[i].NPC_Type==1)&&(model->NPC_Saver[i].Map_Drawing_Picture==model->NPC_Saver[219].Map_Drawing_Picture)&&(model->NPC_Saver[i].Exist_Flag==2)) continue;
                 float Distance = 10;
                Distance=Pos_Distance(model->NPC_Saver[i].pos.dx,
                                       model->NPC_Saver[i].pos.dy,
                                      Virtual_x,
                                      Virtual_y);
                if (Distance<Collision)//说明撞到了NPC
				{
			 		model->NPC_Saver[i].HittingEvent();
					switch(model->NPC_Saver[i].NPC_Type)
					{
						case Normal_NPC:
							flag_for_event = 1;
							break;
						case Fighting_NPC:
							model->Window_Status = FIGHTING_STATUS;
							flag_for_event = 1;
			 				break;
						case Invisible_Wall:
							flag_for_event = 1;
							break;
			 			default:break;
					}
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
                        cheche->pos.dy += STEP;
                        model->map_y -= STEP;
                        model->cha_x = pos_trans_x(cheche->pos.dx);
                        model->cha_y = pos_trans_y(cheche->pos.dy);
                         break;
                    case Qt::Key_Right:
                        cheche->FacingDirection = 2;
                        cheche->pos.dx += STEP;
                        model->map_x -= STEP;
                        model->cha_x = pos_trans_x(cheche->pos.dx);
                        model->cha_y = pos_trans_y(cheche->pos.dy);
                         break;
                    case Qt::Key_Left:
                        cheche->FacingDirection = 4;
                        cheche->pos.dx -= STEP;
                        model->map_x += STEP;
                        model->cha_x = pos_trans_x(cheche->pos.dx);
                        model->cha_y = pos_trans_y(cheche->pos.dy);
                        break;
                    case Qt::Key_Up:
                        cheche->FacingDirection = 1;
                        cheche->pos.dy -= STEP;
                        model->map_y += STEP;
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

		case FIGHTING_STATUS:        //从这里开始是战斗哦界面的键盘响应 
		{	
			switch(key)
			{
				case Qt::Key_A:
						if (cheche-> Walking_Time_Tick==0)	
						cheche->Walking_Time_Tick+=179;
						cheche->attack_success=cheche->attack_success+2;
					break; 
				case Qt::Key_B:
						if (cheche-> Walking_Time_Tick==0)
						cheche->Walking_Time_Tick+=179;
						cheche->attack_success=cheche->attack_success+4;
						cheche->MP=cheche->MP-1;
					break; 
				case Qt::Key_C:
						if (cheche-> Walking_Time_Tick==0)
						cheche->Walking_Time_Tick+=179;
						cheche->HP=cheche->HP+10;
						cheche->MP=cheche->MP+5;
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
                    model ->Window_Status = MAIN_GAME_STATUS;
					model->map_num = model->Before;
                    break;
				case Qt::Key_Down:
					model->callmenu_num = (model->callmenu_num + 1) % 3;
					model->callmenu_id = model->map_id[model->callmenu_num + 7];
					model->map_num = model->callmenu_num + 7;
					break;
				case Qt::Key_Up:
					model->callmenu_num = (model->callmenu_num + 2) % 3;
					model->callmenu_id = model->map_id[model->callmenu_num + 7];
					model->map_num = model->callmenu_num + 7;
					break;
				case Qt::Key_Return:
					switch(model->callmenu_num)
					{
						case 0:
						case 1:break;
						case 2:
							exit(0);
							break;
						}
					break;	
                default:
                    break;
                    
            }
            break;
		}
		case EVENT_STATUS:			//我们在这里触发了事件
		{
			switch(key)
			{
				case Qt::Key_Space:
					model->EventSeq->Counter++;
					break;
				default:
					break;
			}
		}
        default:
			break;
	}
}

void Controller::update_queue()
{	
	switch(model->Window_Status)
	{
		case MAIN_MENU_STATUS:
			model->Drawing_Queue.push(Image_Info(0.0f, 0.0f, 1.0f, 1.0f, model->sta_id));
			break; 
		case MAIN_GAME_STATUS:
		case DIALOGUE_STATUS:
		{
			//从这里 以下是为了判断人物是否要产生移动，如果有的话  
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
				model->Drawing_Queue.push(Image_Info(model->map_x,
                                                     model->map_y,
                                                     model->MapSaver[model->map_num].lx,
                                                     model->MapSaver[model->map_num].ly,
                                                     model->map_id[model->map_num]));
			}
			//从这里往下我们开始往贴图队列放置玩家
			{
				model->Drawing_Queue.push(Image_Info(model->cha_x, model->cha_y,0.08f,0.145f,model->cha_id));
			}	
			//从这里往下我们开始往贴图队列放置地图上的NPC
			{
				for (int i(0);i <model->NPC_Sum;++i)
				{
					if ((model->NPC_Saver[i].Map_Belonging<-50)||(!model->NPC_Saver[i].Exist_Flag)) continue;
					if (model->NPC_Saver[i].Map_Belonging==model->map_num)
					{
					model->Drawing_Queue.push(Image_Info(pos_trans_x(model->NPC_Saver[i].pos.dx),pos_trans_y(model->NPC_Saver[i].pos.dy),0.145f,0.145f,model->NPC_Saver[i].Map_Drawing_Picture));
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
			 	model->Drawing_Queue.push(Image_Info(0,0.656,1,0.344,model->ConverSeq->Conversation_Sequence[model->ConverSeq->Counter]));
			}
		 	 break;
		 }
		case CALLING_MENU_STATUS:
			model->Drawing_Queue.push(Image_Info(0.0f, 0.0f, 1.0f, 1.0f, model->map_id[model->map_num]));
			break;
		case FIGHTING_STATUS:
		{	
			model->cha_fight_id=model->save[16];
			model->cha_num = 5-(cheche->Walking_Time_Tick/30);
			if(model->Last_Key==Qt::Key_A)model->cha_fight_id = model->save[16+model->cha_num];
			if(model->Last_Key==Qt::Key_B)model->cha_fight_id = model->save[22+model->cha_num];
			else if(model->Last_Key==Qt::Key_C)model->cha_fight_id = model->save[28+model->cha_num];	
			model->Drawing_Queue.push(Image_Info(0.0f, 0.0f,1,1,model->map_id[model->map_num]));
            if (model->cha_num==4) model->Drawing_Queue.push(Image_Info(0.555f,0.555f,0.29f,0.29f,model->Last_Npc));//受攻击
				else model->Drawing_Queue.push(Image_Info(0.275f,0.185f,0.29f,0.29f,model->Last_Npc));//原地不动
            if(model->Last_Key==Qt::Key_C)
			{
				if(model->cha_num==1||model->cha_num==2||model->cha_num==3)
					model->Drawing_Queue.push(Image_Info(0.45f,0.45f,0.25f,0.145f,model->cha_fight_id));
				else model->Drawing_Queue.push(Image_Info(0.75f,0.75f,0.145f,0.145f,model->cha_fight_id)); 
			}
			else
            {

		 		if(model->cha_num == 1||model->cha_num== 2)model->Drawing_Queue.push(Image_Info (0.45f,0.35f,0.145f,0.145f,model->cha_fight_id));
			    else model->Drawing_Queue.push(Image_Info(0.75f,0.75f,0.145f,0.145f,model->cha_fight_id));
			}
			if(cheche->Walking_Time_Tick==0&&cheche->attack_success>=12)//请家豪把怪物“搞”出来
			{
 				model->map_num=1;   //转回大地图
	 		 	cheche->attack_success=0;//战斗伤害清零
				model->Window_Status=MAIN_GAME_STATUS;

	 		} 
			break;
		}
		case EVENT_STATUS:
		{

			if ((model->EventSeq!=NULL)&&(model->EventSeq->Counter==model->EventSeq->Information_Sequence.size()))
			{
				delete(model->EventSeq);
				model->EventSeq=NULL;
				model->Window_Status=MAIN_GAME_STATUS;
			}
			if (model->ConverSeq!=NULL)
			{
				model->Drawing_Queue.push(Image_Info(0,0,1.0,1.0,model->EventSeq->BlackMap_ID));
				model->Drawing_Queue.push(Image_Info(0,0.5,1,0.5,model->EventSeq->Information_Sequence[model->EventSeq->Counter]));
			}
			break; 
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
