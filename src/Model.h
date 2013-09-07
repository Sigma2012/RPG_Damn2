#include <queue>
#include <vector>
using std::vector;
using std::queue;
//queue<int> Drawing_Queue; 
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
	int Counter;							//记录现在已经到了第几个了
	vector<int> Conversation_Sequence;		//记录这个对话到底有哪些图片组成
};
class Model
{
public:
	~Model();
	static Model* getInstance();
	queue<Image_Info> Drawing_Queue;
	float map_x, map_y;//贴图用地图坐标
	float cha_x, cha_y;//贴图用主角坐标
	Conversation_Information* ConverSeq;
	int map_num;//地图标签
	int cha_num;//角色朝向标签
	int save[16];
	int map_id;
	int cha_id;
	private:
	static Model* instance_;
	Model();
};
