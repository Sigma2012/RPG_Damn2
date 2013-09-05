
class Model;
class Character;
class Controller
{
public:
	Controller();
	~Controller();
	void key_press(int key);

private:
	Model *model;
	Character *cheche;
	};
