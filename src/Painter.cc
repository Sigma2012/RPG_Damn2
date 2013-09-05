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
		id_ = save[0];
    else if(cheche->FacingDirection == 2)
		id_ = save[1];
	else if(cheche->FacingDirection == 3)
		id_ = save[2];
	else if(cheche->FacingDirection == 4)
		id_ = save[3];
	//id_map = loadImage("scene.png");
	fillImage(cheche->pos.dx, cheche->pos.dy, 0.3f, 0.3f, id_);
}

void Painter::init()
{
    save[0]=loadImage("1.png");
    save[1]=loadImage("2.png");
    save[2]=loadImage("3.png");
    save[3]=loadImage("4.png");
    
	if(cheche->FacingDirection == 1)
		id_ = save[0];
    else if(cheche->FacingDirection == 2)
		id_ = save[1];
	else if(cheche->FacingDirection == 3)
		id_ = save[2];
	else if(cheche->FacingDirection == 4)
		id_ = save[3];
	id_map = loadImage("scene.png");
}
