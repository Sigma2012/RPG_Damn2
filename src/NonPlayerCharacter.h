#include "Object.h"
class NonPlayerCharacter:public Object
{
	int Map_Belonging;					//标记这个玩意属于哪个地图
	virtual void HittingEvent();
	int Map_Drawing_Picture;
	vector<int> Dialog_Sequence;
	NonPlayerCharacter();
	~NonPlayerCharacter();
};						 
