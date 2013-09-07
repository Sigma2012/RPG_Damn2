#include <queue>
using std::queue;
//queue<int> Drawing_Queue; 
class Model
{
public:
	~Model();
	static Model* getInstance();
	void Get_Drawing_Queue();

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
