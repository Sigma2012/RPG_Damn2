
class Model;
class Character;
class Controller
{
public:
	Controller();
	~Controller();
	void key_press(int key);
	void update_queue();
	float pos_trans_x(float x);
	float pos_trans_y(float y);

private:
	Model *model;
	Character *cheche;
	};
