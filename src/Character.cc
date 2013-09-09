#include "Character.h"
#include "Model.h"
#define NULL 0
Character * Character::instance_ = NULL;

Character::Character()
{
    //主角坐标初始化
	pos.dx = 1.0f;
	pos.dy = 1.0f;
	///////////////////////
	Walking_Time_Tick = 0;
	FacingDirection =FACING_DOWN;
	Radius = 5.0;
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
    Map_Belonging = 1;
}
NonPlayerCharacter::~NonPlayerCharacter()
{
    
}
void NonPlayerCharacter::Dialog_Begin()
{
	model->ConverSeq = new(Conversation_Information);
	for (int i(0);i<Dialog_Sequence.size();++i)
		model->ConverSeq->Conversation_Sequence.push_back(Dialog_Sequence[i]);
	model->ConverSeq->Counter = 0;
}
void NonPlayerCharacter::HittingEvent()
{
	switch(NPC_Type)
	{
		case Normal_NPC:
				Dialog_Begin();
			break;
		case Fighting_NPC:

			break;
		case Invisible_Wall:

			break;
		default:
			break;	
	}
}

