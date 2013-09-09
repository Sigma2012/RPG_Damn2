#include "Object.h"
class Character:public Object
{
	public:
		~Character();
		int Walking_Time_Tick;
		int FacingDirection;
		double Radius;
		virtual void HittingEvent();
		static Character* getInstance();
		int Leg_Condition;
		coordinate cha_pos;  			//战斗主角坐标
		int attack_success;
		int HP;
		int MP;
		
	private:
		static Character* instance_;
		Character();
};
#include <vector>
using std::vector;
class Model;
class NonPlayerCharacter:public Object
{
public:
    int Map_Belonging;					//标记这个玩意属于哪个地图
    virtual void HittingEvent();
    void Dialog_Begin();
	void Battle_Begin();
	int Map_Drawing_Picture;
	int NPC_Type;						//标记NPC属于对话还是敌人还是空气墙
	coordinate monster_pos;					//战斗怪物坐标
	#define Normal_NPC		1
	#define Fighting_NPC	2
	#define Invisible_Wall	3
    vector<int> Dialog_Sequence;
    NonPlayerCharacter();
    ~NonPlayerCharacter();
private:
    Model* model;
    
};
