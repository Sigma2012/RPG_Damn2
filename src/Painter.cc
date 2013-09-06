#include "Painter.h"
#include "Model.h"
#include "Character.h"

Painter::Painter(paint_func &func)
{
	this->fillImage = func.fillImage;
	this->loadImage = func.loadImage;
	model = Model::getInstance();
	cheche = Character::getInstance();
	}
Painter::~Painter()
{
	}

void Painter::paint()
{
	//修改地图坐标由model和cotroller共同控制
	fillImage(model->map_x, model->map_y, 2, 2, id_map);
    
	if(cheche->FacingDirection == 1)
    {
		int number = 3-(cheche->Walking_Time_Tick/7);
        id_ = save[0+number];
    }
    else if(cheche->FacingDirection == 2)
	{
		int number = 3-(cheche->Walking_Time_Tick/7);
        id_ = save[4+number];
    }
    else if(cheche->FacingDirection == 3)
	{
		int number = 3-(cheche->Walking_Time_Tick/7);
        id_ = save[8+number];
    }
    else if(cheche->FacingDirection == 4)
	{
		int number = 3-(cheche->Walking_Time_Tick/7);
        id_ = save[12+number];
    }

    if (cheche->Leg_Condition)
		if (cheche->Walking_Time_Tick>0)cheche->Walking_Time_Tick--;
	if (cheche->Walking_Time_Tick % 14 == 0)cheche->Leg_Condition = 0;
		fillImage(cheche->pos.dx, cheche->pos.dy, 0.08f, 0.145f, id_);
}

void Painter::init()
{

    save[0]=loadImage("F1.png");
    save[1]=loadImage("F2.png");
    save[2]=loadImage("F3.png");
    save[3]=loadImage("F4.png");
    save[4]=loadImage("R1.png");
    save[5]=loadImage("R2.png");
    save[6]=loadImage("R3.png");
    save[7]=loadImage("R4.png");
    save[8]=loadImage("Z1.png");
    save[9]=loadImage("Z2.png");
    save[10]=loadImage("Z3.png");
    save[11]=loadImage("Z4.png");
    save[12]=loadImage("L1.png");
    save[13]=loadImage("L2.png");
    save[14]=loadImage("L3.png");
    save[15]=loadImage("L4.png");
   
    //大地图贴图初始坐标
	model->map_x = -0.5f;
	model->map_y = -0.5f;
    
    if(cheche->FacingDirection == 1)
		id_ = save[0];
    else if(cheche->FacingDirection == 2)
		id_ = save[4];
	else if(cheche->FacingDirection == 3)
		id_ = save[8];
	else if(cheche->FacingDirection == 4)
		id_ = save[12];
	id_map = loadImage("scene.png");
}
