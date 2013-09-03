class Model
{
public:
	float width, height;
	float x, y;
	static Model* getInstance();
	~Model();

private:
	static Model* instance_;
	Model();
	};
