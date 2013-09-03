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
		virtual void _using_item();
	    virtual void _num_decreas();
		virtual void _take_effect();
};
