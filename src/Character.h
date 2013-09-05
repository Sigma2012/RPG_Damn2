class Object;
 class Character:public Object
{
	public:
		Character();
		~Character();
		int Walking_Time_Tick;
		virtual void HittingEvent();
}_Player;
