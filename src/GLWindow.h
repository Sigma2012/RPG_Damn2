#include <QtOpenGL/QGLWidget>
#include <QTimer>

class Painter;
class Model;
class ImageLoader;
class Controller;
class GLWindow: public QGLWidget
{
	Q_OBJECT
	//public slots:
	//void on_process();
public:
	GLWindow(QWidget *parents = 0);
	~GLWindow();
private:
	virtual void initializeGL();
	virtual void resizeGL(int width, int height);
	virtual void paintGL();
	virtual void keyPressEvent(QKeyEvent * event);

	inline float gl_x(float x)
	{
		return 2 * x - 1.0;
		}

	inline float gl_y(float y)
	{
		return 1.0 - y * 2;
		}

	inline float gl_width(float width)
	{
		return 2 * width;
		}

	inline float gl_height(float height)
	{
		return 2 * -height;
		}
	
	void _fillImage(float x, float y, float width, float height, int id);
	void fillImage(float x, float y, float width, float height, int id);
	int loadImage(const char* filename);

	QTimer *paint_timer;
	Painter *painter;
	Model* model;
	ImageLoader *image_loader;
	Controller * ctrl;
	};
