#include <iostream>
#include "Factory.h"
using namespace std;


int main() {

	ShapeFactory factory;
	ShapeIf *circle = factory.Create("circle");
	circle->Draw();
	ShapeIf *rect = factory.Create("rectangle");
	rect->Draw();
	delete rect;
	delete circle;
}
