#include "Model.h"
#define NULL 0
Model * Model::instance_ = NULL;
Model::Model()
{
	cha_x = 0.4f;
	cha_y = 0.4f;
	map_x = -0.5f;
	map_y = -0.5f;
	ConverSeq = NULL;
    NPC_Saver = NULL;
    NPC_Sum = 220;
	sta_num = 0;
	Window_Status = MAIN_MENU_STATUS;
	map_num = 3;
	callmenu_num = 0;
}

Model::~Model()
{
	}

Model* Model::getInstance()
{
	if(instance_ == NULL)
		instance_ = new Model;
	return instance_;
}
