#include <pthread.h>
#include <iostream>
#include <memory>
using namespace std;

class cLocks {
	pthread_mutex_t m;
	cLocks(const cLocks &) = delete; // Don't allow
	cLocks(const cLocks &&) = delete; // Don't allow
	cLocks const & operator = (cLocks const &); // Don't allow this.
	
public:
	cLocks() { pthread_mutex_init(&m, 0 ); cout<<"Taken"<<endl;}
	~cLocks() { pthread_mutex_destroy(&m); cout<<"Released"<<endl;}
	void LOCK() { pthread_mutex_lock(&m); }
	void UNLOCK() { pthread_mutex_unlock(&m); }
	void TRYLOCK() { pthread_mutex_trylock(&m); }
};


int main ()
{
	auto_ptr<cLocks> m1(new cLocks);
	m1->LOCK();
}
