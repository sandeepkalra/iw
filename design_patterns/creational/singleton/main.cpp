#include <iostream>
#include <string> 
using namespace std;

class Singleton
{
private:
   static Singleton *instance;
   string name;
   Singleton() {}
   Singleton(Singleton const &);
   Singleton & operator=(Singleton const &);
public:
   static Singleton* GetInstance()
   {
	if(!instance) instance = new Singleton();
	return instance;
   }
   void SetName(string s) { name = s; }
   string GetName() { return name; }
};

Singleton * Singleton::instance = 0;


int main() {
	Singleton *a = Singleton::GetInstance();
	Singleton *b  = Singleton::GetInstance();
	a->SetName("A");
	b->SetName("B"); // if a & b are same, a->GetName must be "B"
	cout<<"A->getname = "<< a->GetName() << endl; 
}
