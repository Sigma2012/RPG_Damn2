
class Model;
class Character;
class Controller
{
public:
	Controller();
	~Controller();
	void key_press(int key);
	void update_queue();

private:
	Model *model;
	Character *cheche;
	};
