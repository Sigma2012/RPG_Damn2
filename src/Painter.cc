#include "Painter.h"
#include "Model.h"
#include "Character.h"
#include "Controller.h"

NonPlayerCharacter Container[220];
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
	// 修改地图坐标由model和cotroller共同控制
	switch(model->map_num)
	{
	case 1:
	
		{
 			if (cheche->Leg_Condition)
			if (cheche->Walking_Time_Tick>0)
				cheche->Walking_Time_Tick--;
			if (cheche->Walking_Time_Tick % 14 == 0)
				cheche->Leg_Condition = 0;
		 	break;
		} 
	
	case 2:
 		{	
			if (cheche->Walking_Time_Tick>0)
				cheche->Walking_Time_Tick--;
		 	 	break;
		
		}
	
		default:
		break; 
	}
  			while (!model->Drawing_Queue .empty())
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
	model ->save[15]=loadImage("L4.png");
//	model->save[16]=loadImage("A1.png");
//	model->save[17]=loadImage("A2.png");
//	model->save[18]=loadImage("A3.png");
//	model->save[19]=loadImage("A4.png");
//	model->save[20]=loadImage("B1.png");
//	model->save[21]=loadImage("B2.png");
//	model->save[22]=loadImage("B3.png");
//	model->save[23]=loadImage("B4.png");
//	model->save[24]=loadImage("C1.png");
//	model->save[25]=loadImage("C2.png");
//	model->save[26]=loadImage("C3.png");
//	model->save[27]=loadImage("C4.png");
//	model->map_id[0]=loadImage("loading.png");
	model->map_id[1]=loadImage("main_scene.png");
//	model->map_id[2]=loadImage("fight_scene.png")i;
	model->map_id[3]=loadImage("Start0.png");
 	model->map_id[4]=loadImage("Start1.png");
	model->map_id[5]=loadImage("Start2.png");
	model->map_id[6]=loadImage("Start3.png");
	model->map_id[7]=loadImage("callingmenu0.png");
	model->map_id[8]=loadImage("callingmenu1.png");
	model->map_id[9]=loadImage("callingmenu2.png");
	model->map_id[10]=loadImage("main_scene1.png");
    //初始大地图ID 

	
    model->map_num =1;
	model->sta_id = model->map_id[3];
    //初始化地图下的各种信息。。。
	
	
	//1号地图是我们的大地图
	model->MapSaver[1].lx = 6;
	model->MapSaver[1].ly = 6;
	model->MapSaver[1].map_num_for_this = 1;
	model->MapSaver[1].map_id = model->map_id[1];
	//大地图贴图初始坐标
	model->map_x = -2.5f;
	model->map_y = -2.5f;
	//NPC初始化序列
    model->NPC_Saver = &Container[0]; 
	//以下开始读入NPC
	//以下用来读入空气墙	
    freopen("Iwall.txt","r",stdin);
	for (int i(0);i<model->NPC_Sum;++i) model->NPC_Saver[i].Map_Belonging=-100;
	
	for (int i(0);i<116;++i)
	{
		float a,b;
		model->NPC_Saver[219-i].Map_Belonging = 1;
		model->NPC_Saver[219-i].NPC_Type = 1+2;
		model->NPC_Saver[219-i].Map_Drawing_Picture = loadImage("iwall.png");
		scanf("%f %f",&a,&b);
		model->NPC_Saver[219-i].pos.dx=a/2480*6;
		model->NPC_Saver[219-i].pos.dy=b/1920*6;
	}
	fclose(stdin);
	//以下用来设置传送用NPC
	model->NPC_Saver[1].Map_Belonging = 1;
	model->NPC_Saver[1].Map_Drawing_Picture =loadImage("iwall.png");
	model->NPC_Saver[1].pos.dx= 2.4;
	model->NPC_Saver[1].pos.dy= 2.5;
	model->NPC_Saver[1].NPC_Type = Trans_Former;
	model->NPC_Saver[1].To_Map_Num = 10;
	model->NPC_Saver[1].Tr_x=0.5;
	model->NPC_Saver[1].Tr_y=0.5;	
	model->NPC_Saver[1].Tr_ma_x=-2.5;
	model->NPC_Saver[1].Tr_ma_y=-2.5;	
	//以下用来设置对话用NPC
	model->NPC_Saver[0].Map_Belonging = 1;	
	model->NPC_Saver[0].Map_Drawing_Picture =loadImage("NPC_0.png");
	model->NPC_Saver[0].Dialog_Sequence.push_back(loadImage("TD1.png"));
	model->NPC_Saver[0].pos.dx=2.5;
	model->NPC_Saver[0].pos.dy=2.5;
	model->NPC_Saver[0].NPC_Type=1;
	//以下代码段不知道可不可以删除
    if(cheche->FacingDirection == 1)
		model->cha_id = model->save[0];
    else if(cheche->FacingDirection == 2)
		model->cha_id = model->save[4];
	else if(cheche->FacingDirection == 3)
		model->cha_id = model->save[8];
	else if(cheche->FacingDirection == 4)
		model->cha_id = model->save[12];
}
