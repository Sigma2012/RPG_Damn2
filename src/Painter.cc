#include "Painter.h"
#include "Model.h"
#include "Character.h"
#include "Controller.h"
#include <cstdio>
#include <qsound.h>
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
	switch(model->Window_Status)
	{
	case MAIN_GAME_STATUS:
	
		{
 			if (cheche->Leg_Condition)
			if (cheche->Walking_Time_Tick>0)
				cheche->Walking_Time_Tick--;
			if (cheche->Walking_Time_Tick % 14 == 0)
				cheche->Leg_Condition = 0;
		 	break;
		} 
	case FIGHTING_STATUS:
		{
			if (cheche->Walking_Time_Tick>0)
				cheche->Walking_Time_Tick--;
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
    freopen("Coor.txt","w",stdout);
    printf("%f %f %f %f %f %f\n",model->cha_x,model->cha_y,model->map_x,model->map_y,cheche->pos.dx,cheche->pos.dy);
    fclose(stdout);
}

void Painter::init()
{
    QSound bells("wav/Track01.wav");
    bells.play();
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
        model->save[16]=loadImage("attack.png");
        model->save[17]=loadImage("attack1.png");
        model->save[18]=loadImage("attack2.png");
        model->save[19]=loadImage("attack.png");
	    model->save[20]=loadImage("Hitting.png");
        model->save[21]=loadImage("attack.png");
        model->save[22]=loadImage("attack.png");
        model->save[23]=loadImage("magic1.png");
        model->save[24]=loadImage("magic2.png");
        model->save[25]=loadImage("attack.png");
        model->save[26]=loadImage("Hitting.png");
        model->save[27]=loadImage("attack.png");

		model->save[28]=loadImage("attack.png");
        model->save[29]=loadImage("_Item_use.png");
        model->save[30]=loadImage("_Item_use.png");
        model->save[31]=loadImage("_Item_use.png");
		model->save[32]=loadImage("Hitting.png");
		model->save[33]=loadImage("attack.png");
		//        model->map_id[0]=loadImage("loading.png");
        model->map_id[1]=loadImage("main_scene.png");
        model->map_id[2]=loadImage("fight_scene.png");
        model->map_id[3]=loadImage("Start0.png");
        model->map_id[4]=loadImage("Start1.png");
        model->map_id[5]=loadImage("Start2.png");
        model->map_id[6]=loadImage("Start3.png");
        model->map_id[7]=loadImage("callingmenu0.png");
        model->map_id[8]=loadImage("callingmenu1.png");
        model->map_id[9]=loadImage("callingmenu2.png");
        model->map_id[10]=loadImage("main_scene1.png");
        model->map_id[11]=loadImage("_Library.png");//载入图书馆坐标
        model->map_id[12]=loadImage("_DoorWay1.png");//载入走廊1的坐标
        model->map_id[13]=loadImage("_DoorWay2.png");//载入走廊2的坐标
        model->map_id[14]=loadImage("_Empty_House.png");//载入小黑屋的坐标
    }
    //初始大地图ID

    model->map_num =1;
	model->sta_id = model->map_id[3];
    //初始化地图下的各种信息。。。
	
	
	//1号地图是我们的大地图
	{
        model->MapSaver[1].lx = 6;
        model->MapSaver[1].ly = 6;
        model->MapSaver[1].map_num_for_this = 1;
        model->MapSaver[1].map_id = model->map_id[1];
        //11号地图是我们的图书馆
        model->MapSaver[11].lx = 0.7;
        model->MapSaver[11].ly = 0.7;
        model->MapSaver[11].map_num_for_this = 11;
        model->MapSaver[11].map_id = model->map_id[11];
        //12号地图是我们的走廊1
        model->MapSaver[12].lx = 0.7;
        model->MapSaver[12].ly = 0.7;
        model->MapSaver[12].map_num_for_this = 12;
        model->MapSaver[12].map_id = model->map_id[12];
        //13号地图使我们的走廊2
        model->MapSaver[13].lx = 0.7;
        model->MapSaver[13].ly = 0.7;
        model->MapSaver[13].map_num_for_this = 13;
        model->MapSaver[13].map_id = model->map_id[13];
        //14号地图是我们的小黑屋
        model->MapSaver[14].lx = 0.7;
        model->MapSaver[14].ly = 0.7;
        model->MapSaver[14].map_num_for_this = 14;
        model->MapSaver[14].map_id = model->map_id[14];
    }
	//大地图贴图初始坐标
	model->map_x = 0.1f;
	model->map_y = 0.1f;
	//NPC初始化序列
    model->NPC_Saver = &Container[0]; 
	//以下开始读入NPC
	//以下用来读入空气墙
    int Iwall = loadImage("iwall.png");
    {
        freopen("Iwall.txt","r",stdin);
        for (int i(0);i<model->NPC_Sum;++i) model->NPC_Saver[i].Map_Belonging=-100;
        for (int i(0);i<116;++i)
        {
            float a,b;
            model->NPC_Saver[219-i].Map_Belonging = 1;
            model->NPC_Saver[219-i].NPC_Type = 1+2;
            model->NPC_Saver[219-i].Map_Drawing_Picture = Iwall;
            scanf("%f %f",&a,&b);
            model->NPC_Saver[219-i].pos.dx=a/2480*6;
            model->NPC_Saver[219-i].pos.dy=b/1920*6;
        }
        fclose(stdin);
	}
    //以下用来设置传送用NPC
    /*
        请任何加入了NPC的人在这个注释列表里面著名你的NPC的编号和NPC的类型、说明
        0:测试用普通NPC
        1:跳转用测试NPC，已经和谐
        2:测试用怪物
        3：图书馆到走廊1的传送NPC
        4:走廊1到走廊2的传送NPC
        5:走廊2到大地图的传送NPC
        6:大地图到小黑屋的传送NPC
     
        11:小黑屋到大地图的NPC
     
        12~20:预留的空气NPC以及剧情NPC的存储
     
        21~??：各种牛叉的怪物
    */
    {
        //这个部分是测试用NPC，现在我们已经和谐掉他了
        model->NPC_Saver[1].Map_Belonging = -1;
        model->NPC_Saver[1].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[1].pos.dx= 2.4;
        model->NPC_Saver[1].pos.dy= 2.5;
        model->NPC_Saver[1].NPC_Type = Trans_Former;
        model->NPC_Saver[1].To_Map_Num = 10;
        model->NPC_Saver[1].Tr_x=3.0;
        model->NPC_Saver[1].Tr_y=3.0;
        model->NPC_Saver[1].Tr_ma_x=-2.5;
        model->NPC_Saver[1].Tr_ma_y=-2.5;
        //这个部分是图书馆到走廊1的部分，注意到坐标转换参数我们还没有设置
        model->NPC_Saver[3].Map_Belonging = 11;
        model->NPC_Saver[3].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[3].pos.dx= 0.5;
        model->NPC_Saver[3].pos.dy= 0.6;
        model->NPC_Saver[3].NPC_Type = Trans_Former;
        model->NPC_Saver[3].To_Map_Num = 12;
        model->NPC_Saver[3].Tr_x = 0.55;
        model->NPC_Saver[3].Tr_y = 0.40;
        model->NPC_Saver[3].Tr_ma_x = -0.05;
        model->NPC_Saver[3].Tr_ma_y = 0.1;
	
    //这个部分是走廊1到走廊2的部分，注意到坐标转换我们还没有设置
        model->NPC_Saver[4].Map_Belonging = 12;
        model->NPC_Saver[4].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[4].pos.dx= 0.0;
        model->NPC_Saver[4].pos.dy= 0.5;
        model->NPC_Saver[4].NPC_Type = Trans_Former;
        model->NPC_Saver[4].To_Map_Num = 13;
        model->NPC_Saver[4].Tr_x= 0.6;
        model->NPC_Saver[4].Tr_y= 0.5;
        model->NPC_Saver[4].Tr_ma_x=-0.1;
        model->NPC_Saver[4].Tr_ma_y=0.0;
	
    //这个部分是走廊2到大地图的部分，请注意我们的坐标参数没有设置
        model->NPC_Saver[5].Map_Belonging = 13;
        model->NPC_Saver[5].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[5].pos.dx= 0.0;
        model->NPC_Saver[5].pos.dy= 0.5;
        model->NPC_Saver[5].NPC_Type = Trans_Former;
        model->NPC_Saver[5].To_Map_Num = 1;
        model->NPC_Saver[5].Tr_x = 2.2;
        model->NPC_Saver[5].Tr_y = 2.6;
        model->NPC_Saver[5].Tr_ma_x = -1.7;
        model->NPC_Saver[5].Tr_ma_y = -2.1;
	
    //这个部分是大地图走到小黑屋的部分，请注意我们的坐标参数没有设置
        model->NPC_Saver[6].Map_Belonging = 1;
        model->NPC_Saver[6].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[6].pos.dx= 1.75;
        model->NPC_Saver[6].pos.dy= 1.8;
        model->NPC_Saver[6].NPC_Type = Trans_Former;
        model->NPC_Saver[6].To_Map_Num = 14;
        model->NPC_Saver[6].Tr_x= 0.3;
        model->NPC_Saver[6].Tr_y= 0.55;
        model->NPC_Saver[6].Tr_ma_x= 0.2;
        model->NPC_Saver[6].Tr_ma_y= -0.05;
     
     //这个部分是小黑屋走到大地图的部分，请注意此处的坐标设置未完成
        model->NPC_Saver[11].Map_Belonging = 14;
        model->NPC_Saver[11].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[11].pos.dx= 0.3;
        model->NPC_Saver[11].pos.dy= 0.65;
        model->NPC_Saver[11].NPC_Type = Trans_Former;
        model->NPC_Saver[11].To_Map_Num = 1;
        model->NPC_Saver[11].Tr_x= 1.75;
        model->NPC_Saver[11].Tr_y= 1.80;
        model->NPC_Saver[11].Tr_ma_x= -1.25;
        model->NPC_Saver[11].Tr_ma_y= -1.30;
    }
    //这个部分是大地图
    
	//以下用来设置怪物
    {
        //2号怪物是测试用怪物，现在已经被和谐
        int MO1 = loadImage("_Monster_1.png");
        int MO2 = loadImage("_Monster_2.png");
        
        model->NPC_Saver[2].Map_Belonging= -1;
        model->NPC_Saver[2].Map_Drawing_Picture =loadImage("NPC_3.png");
        model->NPC_Saver[2].pos.dx= 1.6;
        model->NPC_Saver[2].pos.dy= 2.0;
        model->NPC_Saver[2].NPC_Type = 2;
        //21号之后。。怪物有点多
        model->NPC_Saver[21].Map_Belonging= 1;
        model->NPC_Saver[21].Map_Drawing_Picture =MO1;
        model->NPC_Saver[21].pos.dx= 3.9;
        model->NPC_Saver[21].pos.dy= 2.45;
        model->NPC_Saver[21].NPC_Type = 2;
        
        model->NPC_Saver[22].Map_Belonging= 1;
        model->NPC_Saver[22].Map_Drawing_Picture =MO1;
        model->NPC_Saver[22].pos.dx= 2.7;
        model->NPC_Saver[22].pos.dy= 2.45;
        model->NPC_Saver[22].NPC_Type = 2;
        
        model->NPC_Saver[23].Map_Belonging= 1;
        model->NPC_Saver[23].Map_Drawing_Picture =MO1;
        model->NPC_Saver[23].pos.dx= 2.55;
        model->NPC_Saver[23].pos.dy= 2.75;
        model->NPC_Saver[23].NPC_Type = 2;
        
        model->NPC_Saver[24].Map_Belonging= 1;
        model->NPC_Saver[24].Map_Drawing_Picture =MO1;
        model->NPC_Saver[24].pos.dx= 2.6;
        model->NPC_Saver[24].pos.dy= 3.25;
        model->NPC_Saver[24].NPC_Type = 2;
        
        model->NPC_Saver[25].Map_Belonging= 1;
        model->NPC_Saver[25].Map_Drawing_Picture =MO1;
        model->NPC_Saver[25].pos.dx= 3.05;
        model->NPC_Saver[25].pos.dy= 3.30;
        model->NPC_Saver[25].NPC_Type = 2;
        
        model->NPC_Saver[26].Map_Belonging= 1;
        model->NPC_Saver[26].Map_Drawing_Picture =MO1;
        model->NPC_Saver[26].pos.dx= 4.25;
        model->NPC_Saver[26].pos.dy= 3.5;
        model->NPC_Saver[26].NPC_Type = 2;
    
        model->NPC_Saver[27].Map_Belonging= 1;
        model->NPC_Saver[27].Map_Drawing_Picture =MO1;
        model->NPC_Saver[27].pos.dx= 2.95;
        model->NPC_Saver[27].pos.dy= 3.70;
        model->NPC_Saver[27].NPC_Type = 2;
        
        model->NPC_Saver[28].Map_Belonging= 1;
        model->NPC_Saver[28].Map_Drawing_Picture =MO2;
        model->NPC_Saver[28].pos.dx= 2.05;
        model->NPC_Saver[28].pos.dy= 3.7;
        model->NPC_Saver[28].NPC_Type = 2;
        
        model->NPC_Saver[29].Map_Belonging= 1;
        model->NPC_Saver[29].Map_Drawing_Picture =MO2;
        model->NPC_Saver[29].pos.dx= 3.55;
        model->NPC_Saver[29].pos.dy= 3.8;
        model->NPC_Saver[29].NPC_Type = 2;
        
        model->NPC_Saver[30].Map_Belonging= 1;
        model->NPC_Saver[30].Map_Drawing_Picture =MO2;
        model->NPC_Saver[30].pos.dx= 3.5;
        model->NPC_Saver[30].pos.dy= 2.15;
        model->NPC_Saver[30].NPC_Type = 2;
        
        model->NPC_Saver[31].Map_Belonging= 1;
        model->NPC_Saver[31].Map_Drawing_Picture =MO2;
        model->NPC_Saver[31].pos.dx= 4.10;
        model->NPC_Saver[31].pos.dy= 2.05;
        model->NPC_Saver[31].NPC_Type = 2;
        
        model->NPC_Saver[32].Map_Belonging= 1;
        model->NPC_Saver[32].Map_Drawing_Picture =MO2;
        model->NPC_Saver[32].pos.dx= 2.1;
        model->NPC_Saver[32].pos.dy= 1.65;
        model->NPC_Saver[32].NPC_Type = 2;
        
        model->NPC_Saver[33].Map_Belonging= 1;
        model->NPC_Saver[33].Map_Drawing_Picture =MO2;
        model->NPC_Saver[33].pos.dx= 2.9;
        model->NPC_Saver[33].pos.dy= 2.65;
        model->NPC_Saver[33].NPC_Type = 2;
        
        model->NPC_Saver[34].Map_Belonging= 1;
        model->NPC_Saver[34].Map_Drawing_Picture =MO2;
        model->NPC_Saver[34].pos.dx= 4.25;
        model->NPC_Saver[34].pos.dy= 2.95;
        model->NPC_Saver[34].NPC_Type = 2;
        
        model->NPC_Saver[35].Map_Belonging= 1;
        model->NPC_Saver[35].Map_Drawing_Picture =MO2;
        model->NPC_Saver[35].pos.dx= 2.8;
        model->NPC_Saver[35].pos.dy= 3.9;
        model->NPC_Saver[35].NPC_Type = 2;
        
    }
	//以下用来设置对话用NPC
	{
        //0号NPC是我们的测试用NPC，现在已经和谐
        model->NPC_Saver[0].Map_Belonging = -1;
        model->NPC_Saver[0].Map_Drawing_Picture =loadImage("NPC_0.png");
        model->NPC_Saver[0].Dialog_Sequence.push_back(loadImage("TD1.png"));
        model->NPC_Saver[0].pos.dx=2.55;
        model->NPC_Saver[0].pos.dy=2.45;
        model->NPC_Saver[0].NPC_Type=1;
        //12号NPC是我们的A对话NPC
        model->NPC_Saver[12].Map_Belonging = 11;
        model->NPC_Saver[12].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[12].Dialog_Sequence.push_back(loadImage("A1.png"));
        model->NPC_Saver[12].Dialog_Sequence.push_back(loadImage("A2.png"));
        model->NPC_Saver[12].Dialog_Sequence.push_back(loadImage("A3.png"));
        model->NPC_Saver[12].pos.dx=0.25;
        model->NPC_Saver[12].pos.dy=0.35;
        model->NPC_Saver[12].NPC_Type=1;
        //13号NPC是我们的B对话NPC，棒球男生
        model->NPC_Saver[13].Map_Belonging = 11;
        model->NPC_Saver[13].Map_Drawing_Picture =loadImage("2Dbaseballboy0.png");
        model->NPC_Saver[13].Dialog_Sequence.push_back(loadImage("B1.png"));
        model->NPC_Saver[13].Dialog_Sequence.push_back(loadImage("B2.png"));
        model->NPC_Saver[13].Dialog_Sequence.push_back(loadImage("B3.png"));
        model->NPC_Saver[13].Dialog_Sequence.push_back(loadImage("B4.png"));
        model->NPC_Saver[13].Dialog_Sequence.push_back(loadImage("B5.png"));
        model->NPC_Saver[13].pos.dx=0.5;
        model->NPC_Saver[13].pos.dy=0.4;
        model->NPC_Saver[13].NPC_Type=1;
        //14号是我们的C对话NPC,空气NPC
        model->NPC_Saver[14].Map_Belonging = 1;
        model->NPC_Saver[14].Map_Drawing_Picture =Iwall;
        model->NPC_Saver[14].Dialog_Sequence.push_back(loadImage("C1.png"));
        model->NPC_Saver[14].Dialog_Sequence.push_back(loadImage("C2.png"));
        model->NPC_Saver[14].Dialog_Sequence.push_back(loadImage("C3.png"));
        model->NPC_Saver[14].pos.dx=2.155555;
        model->NPC_Saver[14].pos.dy=2.65;
        model->NPC_Saver[14].NPC_Type=1;
        //15号是我们的D对话NPC，老爷爷
        model->NPC_Saver[15].Map_Belonging = 14;
        model->NPC_Saver[15].Map_Drawing_Picture =loadImage("grandpa2.png");
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D1.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D2.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D3.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D4.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D5.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D6.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D7.png"));
        model->NPC_Saver[15].Dialog_Sequence.push_back(loadImage("D8.png"));
        model->NPC_Saver[15].pos.dx=0.3;
		model->NPC_Saver[15].pos.dy=0.2;
        model->NPC_Saver[15].NPC_Type=1;
        
	}
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
