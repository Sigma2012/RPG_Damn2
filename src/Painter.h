#include <tr1/functional>

typedef std::tr1::function<void(float, float, float, float, int)> funv4f1i;
typedef std::tr1::function<int(const char *)> funi1p;
struct paint_func
{
	funv4f1i fillImage;
	funi1p loadImage;
};
	
class Model;
class Character;
class Painter
{
public:
	Painter(paint_func &func);
	~Painter();

	void paint();
	void init();

private:
	funv4f1i fillImage;
	funi1p loadImage;
	Model* model;
	Character * cheche;
	const char *filename;
	int id_;
	int save[16];
	int id_map;
};
