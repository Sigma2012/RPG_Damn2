#include "Object.h"
#include <vector>
using std::vector;
class NonPlayerCharacter:public Object
{
	int Map_Belonging;					//标记这个玩意属于哪个地图
	virtual void HittingEvent();
	vector<int> Dialog_Sequence;
};						 
