#include "Painter.h"
#include "Model.h"
#include "Character.h"
#include "Controller.h"

NonPlayerCharacter Container[20];
Painter::Painter(paint_func &func)
{
	this->fillImage = func.fillImage;
	this->loadImage = func.loadImage;
	model = Model::getInstance();
	cheche = Character::getInstance();
	ctrl = new Controller;
	}
Painter::~Painter()
{
	delete ctrl;
	}

void Painter::paint()
{
	ctrl->update_queue();
	//修改地图坐标由model和cotroller共同控制
    if (cheche->Leg_Condition)
		if (cheche->Walking_Time_Tick>0)
			cheche->Walking_Time_Tick--;
	if (cheche->Walking_Time_Tick % 14 == 0)
		cheche->Leg_Condition = 0;
	while (!model->Drawing_Queue.empty())
	{
		fillImage(model->Drawing_Queue.front().Up_x,
				model->Drawing_Queue.front().Up_y,
				model->Drawing_Queue.front().Size_x,
				model->Drawing_Queue.front().Size_y,
				model->Drawing_Queue.front().Image_ID);
		model->Drawing_Queue.pop();
	}
}

void Painter::init()
{

	model->save[0]=loadImage("F1.png");
	model->save[1]=loadImage("F2.png");
	model->save[2]=loadImage("F3.png");
	model->save[3]=loadImage("F4.png");
	model->save[4]=loadImage("R1.png");
	model->save[5]=loadImage("R2.png");
	model->save[6]=loadImage("R3.png");
	model->save[7]=loadImage("R4.png");
	model->save[8]=loadImage("Z1.png");
	model->save[9]=loadImage("Z2.png");
	model->save[10]=loadImage("Z3.png");
	model->save[11]=loadImage("Z4.png");
	model->save[12]=loadImage("L1.png");
	model->save[13]=loadImage("L2.png");
	model->save[14]=loadImage("L3.png");
	model->save[15]=loadImage("L4.png");
    //初始大地图ID
    model->map_num = -1;
    model->Window_Status=MAIN_GAME_STATUS;
    //大地图贴图初始坐标
	model->map_x = -0.5f;
	model->map_y = -0.5f;
	//NPC初始化序列
    model->NPC_Saver = &Container[0]; 
	//以下开始读入NPC
    model->NPC_Saver[0].Map_Belonging = -1;	
	model->NPC_Saver[0].Map_Drawing_Picture =loadImage("NPC_0.png");
	model->NPC_Saver[0].Dialog_Sequence.push_back(loadImage("TD1.png"));
	model->NPC_Saver[0].pos.dx=1.5;
	model->NPC_Saver[0].pos.dy=1.5;
	//以下代码段不知道可不可以删除
    if(cheche->FacingDirection == 1)
		model->cha_id = model->save[0];
    else if(cheche->FacingDirection == 2)
		model->cha_id = model->save[4];
	else if(cheche->FacingDirection == 3)
		model->cha_id = model->save[8];
	else if(cheche->FacingDirection == 4)
		model->cha_id = model->save[12];
	model->map_id = loadImage("scene.png");
}
