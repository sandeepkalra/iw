#ifndef __FACTORY__
#define __FACTORY__


#include "Shapes.h"
#include <string>

class ShapeFactory { 
	
	public:
		ShapeIf* Create(std::string type) {
			if(type == "triangle") return new Triangle;
			else if (type=="circle") return new Circle;
			else return new Rectangle;
		}
};



#endif //__FACTORY__
