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

/* Better Choice */
class S {
	string name;
	S() {}
	S(S const&);
	S& operator=(S const&);
public:
	static S& GetInstance() {
		static S instance;
		return instance;
	}
   void SetName(string s) { name = s; }
   string GetName() { return name; }
	
	~S(){cout<<"~S\n"; }
};

int main() {
	Singleton *a = Singleton::GetInstance();
	Singleton *b  = Singleton::GetInstance();
	S& s1 = S::GetInstance();
	S& s2 = S::GetInstance();

	s1.SetName("A");
	s2.SetName("B"); // if s1 & s2 are same, a->GetName must be "B"
	cout<<"A->getname = "<< s1.GetName() << endl; 
}
