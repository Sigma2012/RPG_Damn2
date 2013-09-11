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
    int To_Map_Num;						//对于传送的NPC我们需要知道要传送到哪个地图
	float Tr_x,Tr_y,Tr_ma_x,Tr_ma_y;	//传送NPC传送的对应的地图和玩家的坐标:w
	virtual void HittingEvent();
    void Dialog_Begin();				//对话NPC的操作
	void Battle_Begin();				//战斗开始的标志
	void Transf_Begin();				//传送NPC的操作
	int Map_Drawing_Picture;			//这个NPC对应的地图上的标签
	int NPC_Type;						//标记NPC属于对话还是敌人还是空气墙
	coordinate monster_pos;					//战斗怪物坐标
	bool Exist_Flag;
	#define Normal_NPC		1
	#define Fighting_NPC	2
	#define Invisible_Wall	3
	#define Trans_Former	4
	vector<int> Dialog_Sequence;
    NonPlayerCharacter();
    ~NonPlayerCharacter();
private:
    Model* model;
    Character* cheche;
};
