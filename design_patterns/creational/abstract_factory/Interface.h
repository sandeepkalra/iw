#ifndef __INTERFACE__
#define __INTERFACE__

#include <iostream>
#include <string>
using namespace std;



/* --------------- All about Shape ----------------------*/
 // Abstract Interface
class ShapeIf {
public:
	virtual void Draw() = 0 ;
	virtual ~ShapeIf() { }
};

// Definations
class Rectangle: public ShapeIf {
public:
	virtual void Draw() { cout<<"Rect Draw\n"; }
	virtual ~Rectangle() { cout<<"~Rect\n"; }
};


class Triangle: public ShapeIf {
public:
	virtual void Draw() { cout<<"Triangle Draw\n"; }
	virtual ~Triangle() { cout<<"~Triangle\n"; }
};

class Circle : public ShapeIf {
public:
	virtual void Draw() { cout<<"Circle Draw\n"; }
	virtual ~Circle() { cout<<"~Circle\n"; }
};

/* --------------- All about Color ----------------------*/
class ColorIf {
public:
	virtual void Fill() = 0 ; 
	virtual ~ColorIf() {}
};

class Blue: public ColorIf {
	virtual void Fill() { cout<<"Blue \n"; }
	virtual ~Blue() { cout<<"~Blue\n"; }
};

class Red: public ColorIf {
	virtual void Fill() { cout<<"Red \n"; }
	virtual ~Red() { cout<<"~Red\n"; }
};

class Green: public ColorIf {
	virtual void Fill() { cout<<"Green \n"; }
	virtual ~Green() { cout<<"~Green\n"; }
};

/* ------------------------ The factory of Factory ----------------*/
class FactoryIf {
public:
	virtual ColorIf *CreateColor(string s) = 0 ;
	virtual ShapeIf *CreateShape(string s) = 0 ;
	virtual ~FactoryIf() {} 
};

class ColorFactory : public FactoryIf {
public:
	ColorIf * CreateColor(string s) {
		if(s == "blue") return new Blue();
		else if(s == "red") return new Red();
		else return new Green();
	}
	ShapeIf * CreateShape(string s) {return 0;}
	virtual ~ColorFactory() { cout<<"~ColorFactory\n"; }
};

class ShapeFactory : public FactoryIf {
public:
	ShapeIf* CreateShape(string s) {
		if(s == "rectangle") return new Rectangle();
		else if(s == "circle") return new Circle();
		else return new Triangle();
	}
	ColorIf * CreateColor(string s) {return 0;}
	virtual ~ShapeFactory() { cout<<"~ShapeFactory\n"; }
};


class AbstractFactory {
public:
	virtual FactoryIf* GetFactory(string s) {
		if(s=="shape") return new ShapeFactory();
		else return new ColorFactory();
	}
};


#endif
