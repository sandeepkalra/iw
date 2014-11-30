#include "Interface.h"

int main() {
	AbstractFactory f;
	FactoryIf *shapes = f.GetFactory("shape");
	ShapeIf* triangle = shapes->CreateShape("triangle");
	triangle->Draw();
	delete triangle;
	delete shapes;
}
