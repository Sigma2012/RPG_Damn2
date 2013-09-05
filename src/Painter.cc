#include "Painter.h"
#include "Model.h"
#include "Character.h"

Painter::Painter(paint_func &func)
{
	this->fillRect = func.fillRect;
	this->setColor = func.setColor;
	this->fillImage = func.fillImage;
	this->loadImage = func.loadImage;
	//id_ = loadImage(filename);
	model = Model::getInstance();
	cheche = Character::getInstance();
	}
Painter::~Painter()
{
	}

void Painter::paint()
{
	setColor(1.0f, 0.0f, 1.0f, 0.7f);
	fillImage(0, 0, 2, 2, id_map);
	if(cheche->FacingDirection == 1)
		id_ = loadImage("1.png");
	else if(cheche->FacingDirection == 2)
		id_ = loadImage("2.png");
	else if(cheche->FacingDirection == 3)
		id_ = loadImage("3.png");
	else if(cheche->FacingDirection == 4)
		id_ = loadImage("4.png");
	id_map = loadImage("scene.png");
	fillImage(cheche->pos.dx, cheche->pos.dy, 0.3f, 0.3f, id_);
}

void Painter::init()
{
	if(cheche->FacingDirection == 1)
		id_ = loadImage("1.png");
	else if(cheche->FacingDirection == 2)
		id_ = loadImage("2.png");
	else if(cheche->FacingDirection == 3)
		id_ = loadImage("3.png");
	else if(cheche->FacingDirection == 4)
		id_ = loadImage("4.png");
	id_map = loadImage("scene.png");
	}
