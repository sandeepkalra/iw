#ifndef __CTHREAD_H__
#define __CTHREAD_H__

#include <pthread.h>


class CLock {
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
public:
	void Lock() {
		pthread_mutex_lock(&m);
	}
	void TryLock() {
		pthread_mutex_trylock(&m);
	}
	void UnLock() {
		pthread_mutex_unlock(&m);
	}
}


class CThread {
	CLock lock;
public:
	

}



#endif
