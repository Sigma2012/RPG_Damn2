#include "Character.h"
#include "Controller.h"
#include "Model.h"
#define NULL 0
Character * Character::instance_ = NULL;

Character::Character()
{
    //主角坐标初始化
	pos.dx = 0.3f;
	pos.dy = 0.3f;
	cha_pos.dx = 0.75f;		//战斗界面主角坐标
	cha_pos.dy = 0.75f;		//初始化
	///////////////////////
	Walking_Time_Tick = 0;
	attack_success = 0;           //判断主角是否攻击胜利 
	FacingDirection =FACING_DOWN;
	Radius = 5.0;
	HP=20;
	MP=10;
}
void Character::HittingEvent()
{
	
}
Character::~Character()
{

}

Character* Character::getInstance()
{
	if(instance_ == NULL)
		{
		instance_ = new Character;
		}
	return instance_;
}
NonPlayerCharacter::NonPlayerCharacter()
{
    model = Model::getInstance();
    cheche = Character::getInstance();
	Map_Belonging = 1;
    monster_pos.dx = 0.25f;
    monster_pos.dy = 0.25f;
	Exist_Flag = 1;
}
NonPlayerCharacter::~NonPlayerCharacter()
{
    
}
void NonPlayerCharacter::Battle_Begin()
{	
	model->map_num = 2 ;// 战斗界面
		

}
void NonPlayerCharacter::Dialog_Begin()
{
	model->ConverSeq = new(Conversation_Information);
	for (int i(0);i<Dialog_Sequence.size();++i)
		model->ConverSeq->Conversation_Sequence.push_back(Dialog_Sequence[i]);
	 model->ConverSeq->Counter = 0;
}
void NonPlayerCharacter::Transf_Begin()
{
	model->map_num =  To_Map_Num;
	model->map_x = Tr_ma_x;
	model->map_y = Tr_ma_y;
	cheche->pos.dx = Tr_x;
	cheche->pos.dy = Tr_y;
	model->cha_x = model->map_x + cheche->pos.dx;
	model->cha_y = model->map_y + cheche->pos.dy;
}
void NonPlayerCharacter::HittingEvent()
{
    model->Last_Hit_NPC_Pic = Map_Drawing_Picture;
	switch(NPC_Type)
	{
		case Normal_NPC:
				if (Exist_Flag == 2) return;
				Dialog_Begin();
                model->Window_Status = DIALOGUE_STATUS;
				Exist_Flag = 2;
			break; 
		case Fighting_NPC:
				Exist_Flag = 0;
				Battle_Begin();
			break; 
		case Invisible_Wall:

			break;
		case Trans_Former:
			Transf_Begin();
			break;
		default:
			break;	
	}
}

