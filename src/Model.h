#include <queue>
using std::queue;
//queue<int> Drawing_Queue; 
class Image_Info
{
	public:
		int Image_ID;
		int Up_x,Up_y;
		int Size_x,Size_y;
		Image_Info(int II,int UX,int UY,int sx,int sy)
		{
			Image_ID = II;
			Up_x = UX;
			Up_y = UY;
			Size_x = sx;
			Size_y = sy;
		}
};

class Model
{
public:
	~Model();
	static Model* getInstance();
	queue<Image_Info> Drawing_Queue;
	float map_x, map_y;//贴图用地图坐标
	float cha_x, cha_y;//贴图用主角坐标
	int map_num;//地图标签
	int cha_num;//角色朝向标签
	int save[16];
	int map_id;
	int cha_id;
	private:
	static Model* instance_;
	Model();
};
