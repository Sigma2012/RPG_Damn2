#include "ImageLoader.h"
#include <lodepng.h>
#include <assert.h>

ImageLoader::ImageLoader()
{
	}

ImageLoader::~ImageLoader()
{
	}

int ImageLoader::load(const char * filename)
{
	PNG * image = new PNG;
	unsigned int error = lodepng::decode(image->data, image->width, image->height, filename);
	assert(!error);
	images.push_back(image);
	return images.size() - 1;
	}

ImageLoader::PNG_PTR ImageLoader::get(int id)
{
	return images.at(id);
	}
