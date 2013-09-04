#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
using namespace std;
class item
{
	public:
		item();
		~item();
		virtual void _using_item()=0;
	    virtual void _num_decreas()=0;
		virtual void _take_effect()=0;
		int item_type_flag;
		int item_num;
		/*
			0  : 空道具
			1  : 使用回复类道具
			2  : 使用攻击类道具
			3  : 装备类道具 
		*/
};
item::item()
{
	item_type_flag = 0;
	item_num = 0;
}
item::~item()
{
	
}
class water:public item
{
 	public:
		water();
		~water();	
		virtual void _using_item();
		virtual void _num_decreas();
		virtual void _take_effect();
}
water::water()
{
	item_type_flag =1；
		
}
water::~water()
{

}
water::_num_decreas()
{

}

