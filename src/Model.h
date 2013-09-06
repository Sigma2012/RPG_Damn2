#include <queue>
std::queue;
queue<int> Drawing_Queue; 
class Model
{
public:
	float width, height;
	float x, y;
	static Model* getInstance();
	~Model();
	void Get_Drawing_Queue();

    //地图贴图坐标//////////
	float map_x, map_y;
	////////////////////////

	private:
	static Model* instance_;
	Model();
	};
