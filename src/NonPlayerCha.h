#include "Object.h" 
class NonPlayerCha:Public Object
{
   public:
	   NonPlayerCha();
	   ~NonPlayerCha();
	   int Conversation_Lable;//标记出对于这个NPC我们的对话进行到哪里了。	
	   int Map_Lable;	

}

NonPlayerCha::NonPlayerCha()
{
	Radius = 5.0;
	FacingDirection=FACING_DOWN;
	Lable = 1;
	Map_Lable = 0;
	Conversation_Lable = 0;
}
NonPlayerCha::~NonPlayerCha()
{

}
NonPlayerCha::HittingEvent
{
	Conversation_Lable = 1;
}
