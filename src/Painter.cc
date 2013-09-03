#include "Painter.h"
#include "Model.h"

Painter::Painter(paint_func &func)
		:filename("ok.png")
{
	this->fillRect = func.fillRect;
	this->setColor = func.setColor;
	this->fillImage = func.fillImage;
	this->loadImage = func.loadImage;
	//id_ = loadImage(filename);
	model = Model::getInstance();
	}

Painter::~Painter()
{
	}

void Painter::paint()
{
	setColor(1.0f, 0.0f, 1.0f, 0.7f);
	fillImage(model->x, model->y, 0.3f, 0.3f, id_);
	}

void Painter::init()
{
	id_ = loadImage(filename);
	}
