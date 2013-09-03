#include <QtGui/QKeyEvent>
#include "GLWindow.h"
#include "Painter.h"
#include "ImageLoader.h"
#include "Model.h"
#include "Controller.h"
using namespace std::tr1::placeholders;

GLWindow::GLWindow(QWidget *parents )
:QGLWidget(parents)
{
	paint_func func;
	func.fillRect = std::tr1::bind(&GLWindow::fillRect, this, _1, _2, _3, _4);
	func.setColor = std::tr1::bind(&GLWindow::setColor, this, _1, _2, _3, _4);
	func.fillImage = std::tr1::bind(&GLWindow::fillImage, this, _1, _2, _3, _4, _5);
	func.loadImage = std::tr1::bind(&GLWindow::loadImage, this, _1);
	painter = new Painter(func);
	model = Model::getInstance();
	ctrl = new Controller;
	image_loader = new ImageLoader;

	rect_x = 0.4f;
	rect_y = 0.0f;
	rect_width = 0.2f;
	rect_height = 0.75f;

	paint_timer = new QTimer;
	connect(paint_timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	process_timer = new QTimer;
	connect(process_timer, SIGNAL(timeout()), this, SLOT(on_process()));
}

GLWindow::~GLWindow()
{
	paint_timer->stop();
	process_timer->stop();
	delete paint_timer;
	delete process_timer;
	delete painter;
	delete image_loader;
	delete ctrl;
}
	
void GLWindow::initializeGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_BLEND);//allow alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//comment setting alpha
	setAutoBufferSwap(false);//swap buffer by hand(timer)
	painter->init();
	paint_timer->start(1000.0f/60);
 	process_timer->start(1000.0f/60);
}

void GLWindow::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//setColor(1.0f, 0.0f, 0.0f, 1.0f);
	painter->paint();
 	swapBuffers();
}

void GLWindow::keyPressEvent(QKeyEvent * event)
{
	ctrl->key_press(event->key());
	}

void GLWindow::_fillRect(float x, float y, float width, float height)
{
	glBegin(GL_POLYGON);
	glVertex3f(x, y, 0.0f);
	glVertex3f(x, y + height, 0.0f);
	glVertex3f(x + width, y + height, 0.0f);
	glVertex3f(x + width, y, 0.0f);
	glEnd();
	}

void GLWindow::fillRect(float x, float y, float width, float height)
{
	_fillRect(gl_x(x), gl_y(y), gl_width(width), gl_height(height));
	}

void GLWindow::_fillImage(float x, float y, float width, float height, int id)
{
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(id));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);glVertex3f(x, y, 0.0f);
	glTexCoord2f(0.0f, 1.0f);glVertex3f(x, y + height, 0.0f);
	glTexCoord2f(1.0f, 1.0f);glVertex3f(x + width, y + height, 0.0f);
	glTexCoord2f(1.0f, 0.0f);glVertex3f(x + width, y, 0.0f);
	glEnd();
	}

void GLWindow::fillImage(float x, float y, float width, float height,int id)
{
	_fillImage(gl_x(x), gl_y(y), gl_width(width), gl_height(height), id);
	}

int GLWindow::loadImage(const char* filename)
{
	std::string image_file("images/");
	image_file += filename;
	int id = image_loader->load(image_file.c_str());
	GLuint g_id;
	glGenTextures(1, &g_id);
	glBindTexture(GL_TEXTURE_2D, g_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	ImageLoader::PNG_PTR image = image_loader->get(id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width,image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image->data[0]);
	return static_cast<int>(g_id);
	}

void GLWindow::on_process()
{
	 rect_width += 0.01f/60;
	rect_height += 0.01f/60;
	}
