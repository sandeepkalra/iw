//============================================================================
// Name        : prototype.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
using namespace std;


class Shapes {
	string name;
	string color;
public:
	string getName() { return name; }
	string getColor(){ return color;}
	void setName(string s) { name = s ;}
	void setColor(string s){ color = s; }
	void Draw() { cout<<"shape- draw\n";}
	void Fill() { cout<<"shape- fill\n";}
	Shapes(const Shapes& copy) { // Copy Constructor.
		cout<<"copy called\n";
		color = copy.color;
		name = copy.name;
	}
	Shapes& operator= (const Shapes& shape) {
		cout<<"operator =\n";
		this->color = shape.color;
		this->name = shape.name;
		return *this;
	}
	Shapes(){}
	virtual ~Shapes() {cout<<"~Shapes\n";}
};

// Assume this is a class that has a high computation
// cost. We cache the value, and clone it from cache.
class Rect: public Shapes {
public:
	Rect(): Shapes() { }
	void Draw() {
		cout<<"rect-draw\n";
	}
	void Fill() {
			cout<<"rect-fill\n";
	}
};


class Prototypes {
	map<string , Shapes*> MyDb;
public:
	Shapes*  Clone(string i) {
		Shapes * shape =  MyDb[i];
		Shapes *p = new Shapes();
		*p = *shape;
		return p;
	}
	void PutPrototypeOf(string i, Shapes* shape) {
		MyDb.insert(pair<string,Shapes*>(i,shape));
	}
};


int main() {
	Prototypes cache;
	Shapes *p = new Rect();
	p->setColor("black");
	p->setName("MyTemplateRectangle");

	cache.PutPrototypeOf("rectangle",p);
	Shapes *q = cache.Clone("rectangle");
	if(p==q) cout<<"They are same\n";
	else cout<<"They are not same\n";


	cout<<" color of returned type is : "<< q->getColor() <<endl;
	cout<<" name of the returned type is:" << q->getName() <<endl;

	if(p) delete p;
	if(q) delete q;
	return 0;
}
