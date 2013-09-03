SOURCES += main.cc GLWindow.cc Painter.cc ImageLoader.cc lodepng.cc Model.cc Controller.cc
HEADERS += GLWindow.h Painter.h ImageLoader.h lodepng.h Model.h Controller.cc
QT += opengl
QUAKE_CXXFLAGS += -std=c++0x
CONFIG += qt debug
INCLUDEPATH += ./include \
