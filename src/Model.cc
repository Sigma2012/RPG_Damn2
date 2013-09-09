#include "Model.h"
#define NULL 0
Model * Model::instance_ = NULL;
Model::Model()
{
	cha_x = 0.5f;
	cha_y = 0.5f;
	map_x = -1.0f;
	map_y = -1.0f;
	ConverSeq = NULL;
    NPC_Saver = NULL;
    NPC_Sum = 1;
	sta_num = 0;
	Window_Status = MAIN_MENU_STATUS;
	map_num = 3;
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
