#include <vector>
struct PNG
{
	std::vector<unsigned char> data;
	unsigned int width, height;
	};

class ImageLoader
{
public:
	typedef PNG* PNG_PTR;
	ImageLoader();
	~ImageLoader();
	int load(const char* filename);
	PNG_PTR get(int id);

private:
	std::vector<PNG_PTR> images;
	};
