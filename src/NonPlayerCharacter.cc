#include "NonPlayerCharacter.h"
#include "Model.h"
NonPlayerCharacter::NonPlayerCharacter()
{
    model = Model::getInstance();
    Map_Belonging = 1;
}
NonPlayerCharacter::~NonPlayerCharacter()
{
    
}
void NonPlayerCharacter::HittingEvent()
{
    model->ConverSeq = new(Conversation_Information);
    for (int i(0);i<Dialog_Sequence.size();++i)
        model->ConverSeq->Conversation_Sequence.push_back(Dialog_Sequence[i]);
    model->ConverSeq->Counter = 0;
}