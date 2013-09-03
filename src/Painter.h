#include <tr1/functional>

typedef std::tr1::function<void(float, float, float, float)> funv4f;
typedef std::tr1::function<void(float, float, float, float, int)> funv4f1i;
typedef std::tr1::function<int(const char *)> funi1p;
struct paint_func
{
	funv4f fillRect;
	funv4f setColor;
	funv4f1i fillImage;
	funi1p loadImage;
	};
	
class Model;
class Painter
{
public:
	Painter(paint_func &func);
	~Painter();

	void paint();
//	{
//		setColor(1.0f, 0.0f, 1.0f, 0.7f);
//		fillImage(0.3f, 0.1f, 0.35f, 0.2f, id_);
//		}
	void init();

private:
	funv4f fillRect;
	funv4f setColor;
	funv4f1i fillImage;
	funi1p loadImage;
	Model* model;
	const char *filename;
	int id_;
};
