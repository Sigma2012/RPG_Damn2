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
		
	private:
		static Character* instance_;
		Character();
};

