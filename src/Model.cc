#include "Model.h"
#define NULL 0
Model * Model::instance_ = NULL;
Model::Model()
{
	}

Model::~Model()
{
	}

Model* Model::getInstance()
{
	if(instance_ == NULL)
		instance_ = new Model;
	return instance_;
}
