#define	FACING_UP    1
#define FACING_RIGHT 2
#define	FACING_DOWN	 3
#define FACING_LEFT  4
#include <cmath>
struct coordinate
{
	double dx,dy;
};
class Object
{
	public:
		Object();
		~Object();
		coordinate pos;						//中心坐标
		int FacingDirection;				//面朝方向，用于贴图的确定
		double Radius;						//碰撞半径
		int Lable;							//标签，标志这个是什么类型的东西，是NPC，怪物还是物品
		virtual void HittingEvent();		//碰撞的时候触发的事件

};
/*
	lable的取值：
		0：空类型
		

   */


