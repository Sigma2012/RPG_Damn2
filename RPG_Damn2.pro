SOURCES +=	src/main.cc \
			src/GLWindow.cc \
			src/Painter.cc \
			src/ImageLoader.cc \
			src/Model.cc \
			src/Controller.cc \
			src/Item.cc \
			src/Object.cc \
			src/Character.cc \
                        src/NonPlayerCharacter.cc
HEADERS +=	src/GLWindow.h \
			src/Painter.h \
			src/ImageLoader.h \
			src/Model.h \
			src/Controller.h \
			src/Item.h \
			src/Object.h \
			src/Character.h \
			src/NonPlayerCharacter.h

SOURCES += lib/lodepng.cc

HEADERS += include/lodepng.h

INCLUDEPATH += ./include

QT += opengl
QUAKE_CXXFLAGS += -std=c++0x
CONFIG += qt debug
