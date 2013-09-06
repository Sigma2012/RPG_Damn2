class Model
{
public:
	float width, height;
	float x, y;
	static Model* getInstance();
	~Model();

    //地图贴图坐标//////////
	float map_x, map_y;
	////////////////////////

private:
	static Model* instance_;
	Model();
	};
