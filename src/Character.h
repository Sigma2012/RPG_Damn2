#include "Object.h"
class Character:public Object
{
	public:
		~Character();
		int Walking_Time_Tick;
		int FacingDirection;
		double Radius;
		virtual void HittingEvent();
		static Character* getInstance();
		int Leg_Condition;
	private:
		static Character* instance_;
		Character();
};

