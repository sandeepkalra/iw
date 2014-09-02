#include <iostream>
using namespace std;

enum class Colors : char{
	WHITE = 0,
	BLACK
};

Colors getReverse(Colors g) {
		switch (g) {
			case Colors::WHITE: return Colors::BLACK;
			case Colors::BLACK: return Colors::WHITE;
			default: return Colors::BLACK;
		}
}


int main()
{
	cout<< static_cast<int>(getReverse(Colors::BLACK))<<endl ;
}
