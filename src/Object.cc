
Object::Object()
{
	pos.dx=0.0;
	pos.dy=0.0;
	FacingDirection=FACING_DOWN;
	Radius=0.0;
	Lable=0;
}
Object::~Object()
{
    
}
void Object::HittingEvent()
{
    
}
double sqr(const double x)
{
	return x*x;
}
double Distance_Of_Object(Object a,Object b)
{
	return sqrt(sqr((a.pos.dx-b.pos.dx))+sqr((a.pos.dy-b.pos.dy)));
}

double Pos_Distance(coordinate a,coordinate b)
{
	return sqrt(sqr(a.dx-b.dx)+sqr(a.dy-b.dy));
}
