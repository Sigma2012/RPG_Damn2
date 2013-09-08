#include <QtGui/QApplication>
#include "GLWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GLWindow window;
	window.setWindowTitle(QObject::tr("Adventure Of Hust"));
	window.resize(800, 600);
	window.show();
	return app.exec();
	}
