SOURCES +=	src/main.cc \
			src/GLWindow.cc \
			src/Painter.cc \
			src/ImageLoader.cc \
			src/lodepng.cc \
			src/Model.cc \
			src/Controller.cc
HEADERS +=	src/GLWindow.h \
			src/Painter.h \
			src/ImageLoader.h \
			src/lodepng.h \
			src/Model.h \
			src/Controller.h
QT += opengl
QUAKE_CXXFLAGS += -std=c++0x
CONFIG += qt debug
INCLUDEPATH += ./include
