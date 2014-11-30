#ifndef __SHAPES__
#define __SHAPES__

#include "Interface.h"

class Rectangle : virtual public ShapeIf {
	virtual void Draw() {
		std::cout<<"RectDraw()\n";
	}
	virtual ~Rectangle() { std::cout<<"~Rect\n"; }
};
class Circle : virtual public ShapeIf {
	virtual void Draw() {
		std::cout<<"Circle draw()\n";
	}
	virtual ~Circle() { std::cout<<"~Circle\n"; }
};
class Triangle : virtual public ShapeIf {
	virtual void Draw() {
		std::cout<<"Triangle draw()\n";
	}
	virtual ~Triangle() { std::cout<<"~Triangle\n"; }
};

#endif //_SHAPES_
