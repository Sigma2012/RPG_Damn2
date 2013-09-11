#include <queue>
#include <vector>
#define MAIN_MENU_STATUS	1
#define MAIN_GAME_STATUS	2
#define DIALOGUE_STATUS		3
#define CALLING_MENU_STATUS 	4
#define FIGHTING_STATUS		5
#define EVENT_STATUS		6
#define NPC_SUM 20
#define ATTACK			"a"
#define MAGIC			"b"
#define ITEM 			"c"
using std::vector;
using std::queue;
//queue<int> Drawing_Queue;
class NonPlayerCharacter;
class Image_Info
{
	public:
		int Image_ID;
		float Up_x,Up_y;
		float Size_x,Size_y;
		Image_Info()
		{
			Image_ID = 0;
			Up_x = 0; Up_y = 0;
			Size_x = 0; Size_y = 0;
		}
		Image_Info(float UX,float UY,float sx,float sy,int II)
		{
			Image_ID = II;
			Up_x = UX;
			Up_y = UY;
			Size_x = sx;
			Size_y = sy;
		}
};
class Conversation_Information
{
	public:
		int Counter;							//记录现在已经到了第几个了
		vector<int> Conversation_Sequence;		//记录这个对话到底有哪些图片组成
};
class Event_Information
{
	public:
		int Counter;//记录对话框现在在第几个位置
		vector<int> Information_Sequence;
		int BlackMap_ID;
};
class Map_Container
{
	public:
		int map_num_for_this;
		int map_id;
		float lx,ly;
};
class Model
{
public:
	~Model();
	static Model* getInstance();
	queue<Image_Info> Drawing_Queue;
	float map_x, map_y;					//贴图用地图坐标
	float cha_x, cha_y;					//贴图用主角坐标
	Conversation_Information* ConverSeq;//当这个指针不为空的时候，说明此时此刻有对话
	Event_Information* EventSeq;		//当这个指针不为空的时候，说明此时此刻有事件
	int map_num;						//地图标签,测试状态下地图标签为-1
	int Window_Status;					//标签，表明现在是出于一个什么样的状态，测试状态下这个为1
	int cha_num;						//主角贴图判断标签
	int fight_num;						//战斗地图贴图判断标签	
	int save[100];
    NonPlayerCharacter* NPC_Saver;      //指针，之后会指向一个存了NPC的数组
    int NPC_Sum;
	int map_id[20];
	int sta_num;                        //开始界面标签
	int sta_id;
	int callmenu_num;					//呼出菜单标签
	int callmenu_id;
	int cha_id;
	int cha_fight_id;					//战斗界面的主角贴图标签
	int Last_Key;
 	Map_Container MapSaver[30];			//地图的储存信息
	private:
	static Model* instance_;
	Model(); 
};
