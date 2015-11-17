/* Author : Sandeep Kalra */
/* vim set ts=4 
 * g++  -std=c++1y -g -pthread $1.cpp
 */
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

using namespace std;

typedef void* (*functor)(void *);

enum eSystem
{
	eMaxMsgDataSz = 200
};

struct sMsg 
{
		int mCode;
		int mSubCode;
		int mParamType;
		int mLengthOfData;
		char mData[eSystem::eMaxMsgDataSz];
		bool mFree = true;
		sMsg() : mCode(0), mSubCode(0), mParamType(0) , mLengthOfData(0)
		{
			 memset(mData,0,eSystem::eMaxMsgDataSz); 
		}
		~sMsg() {}
		void Reset() 
		{ 
			memset(mData,0,eSystem::eMaxMsgDataSz); 
			mCode = mSubCode = mParamType = mLengthOfData = 0; 
		}
		bool IsFree() { return mFree; }
		void SetFree(bool vFree) 
		{ 
			mFree = vFree; 
			if(mFree) 
			{
				mCode = mSubCode = mParamType = mLengthOfData = 0; 
				memset(mData, 0, mLengthOfData);
			}
		}
		sMsg& operator=(const sMsg& rhs)
		{/* with pointer, take care and do *p_new = *p_old for this operator */
			mCode = rhs.mCode;
			mSubCode = rhs.mSubCode;
			mParamType = rhs.mParamType;
			mLengthOfData = rhs.mLengthOfData;
			if(mLengthOfData && mLengthOfData < eSystem::eMaxMsgDataSz) 
			{
				memcpy(mData, rhs.mData, mLengthOfData);
			}
			return *this;
		}
		bool operator==(const sMsg& rhs)
		{
			return (
					mCode == rhs.mCode &&
					mSubCode == rhs.mSubCode &&
					mParamType == rhs.mParamType &&
					mLengthOfData == rhs.mLengthOfData
			);
		}
};

class cPool {
	int mSz;
	sMsg ** mPool;
	public:
		cPool(int vSz) : mSz(vSz) , mPool(0) 
		{
			mPool = new sMsg*[vSz];
			for(int i = 0; i< vSz; ++i) 
			{
				mPool[i] = new sMsg();
			}
		}
		~cPool() 
		{
			for (int i =0 ; i < mSz; ++i) 
			{
				delete mPool[i];
			}
			delete[] mPool;
		}
		sMsg *Malloc() 
		{
			sMsg *p = 0; 
			for (int i =0; i < mSz; ++i) 
			{
				if(mPool[i]->IsFree()) 
				{
					p = mPool[i];
					mPool[i]->SetFree(false);
					break;
				}
			}
			return p;
		}
		void Free(sMsg * vArg) 
		{
			vArg->SetFree(true);
		}
};

class cQueue 
{
	sMsg **mMsgHolder;
	pthread_cond_t mCondHandle; /* cond = newmsg */
	pthread_condattr_t mCondAttrHandle;
	pthread_mutex_t mMutex;
	int mSz;
	int mReadHead;
	int mWriteHead;
	int mFilledCnt;
	bool flag = false;
public:
	cQueue(int vSz=20)
	{
		mMsgHolder = 0;
		mReadHead = 0;
		mWriteHead = 0;
		mFilledCnt = 0;
		mSz = vSz;
		pthread_condattr_init(&mCondAttrHandle);
		pthread_cond_init(&mCondHandle, &mCondAttrHandle);
		mMsgHolder = new sMsg*[vSz];
	}
	~cQueue()
	{
		pthread_cond_destroy(&mCondHandle);
		pthread_condattr_destroy(&mCondAttrHandle);
		if(mSz) delete [] mMsgHolder;
	}
	sMsg* deQueue(bool block=true)
	{
		sMsg *p = 0;
		pthread_mutex_lock(&mMutex);

		/* if blocking is true, then block if-and-only-if
		 * there is no data filled 
	 	 */
		if(block && mFilledCnt == 0) 
		{ 
			while(!flag) pthread_cond_wait(&mCondHandle, &mMutex);
		}
	
		if(mFilledCnt != 0) 
		{
			p  = mMsgHolder[mReadHead];
			mReadHead ++ ;
			if(mReadHead == mSz) mReadHead = 0;
			mFilledCnt -- ;
		}
		flag = false;
		pthread_mutex_unlock(&mMutex);
	}
	void enQueue(sMsg* p)
	{
	
		pthread_mutex_lock(&mMutex);
		
		if(mFilledCnt != mSz) 
		{		
			mMsgHolder[mWriteHead] = p;
			mWriteHead ++ ;
			if(mWriteHead == mSz) mWriteHead = 0;
			mFilledCnt ++ ;
			flag = true;
		}
		pthread_mutex_unlock(&mMutex);
		pthread_cond_signal(&mCondHandle);
	}
};

class cThreadModule 
{
	string  mName;
	functor mfStart;
	functor mfEnd;
	functor mfProcess;
	bool mbStarted;
	pthread_t mThreadHandle;
	pthread_attr_t mAttrHandle;
	cQueue *mpQueue;
	bool alive;
	public:
	void Kill() { alive = false;}
	bool isAlive() { return alive;}
	string &GetName() { return mName; }
	void EnQueue(sMsg *p) 
	{ 
		if(mpQueue) 
		{
			return mpQueue->enQueue(p);
		}
	}
	sMsg* DeQueue(bool block=true) 
	{
		if(mpQueue) return mpQueue->deQueue(block);
		return 0;
	}
	cThreadModule(string &&vName, functor vfStart, 
		functor vfEnd, functor vfProcess,
		int vQueueSz=20
		) : 
		mfStart(vfStart), mfEnd(vfEnd), mfProcess(vfProcess) ,mbStarted(false) , mpQueue(0), alive(true)
	{
		mName = move(vName); 
		if(vQueueSz) mpQueue = new cQueue(vQueueSz);
	}
	~cThreadModule() 
	{
		if(mbStarted) 
		{
			mfEnd(this);
			pthread_attr_destroy(&mAttrHandle);
		}
		if(mpQueue) delete mpQueue;
	}
	void Run() 
	{
		if(mbStarted) return;
		mfStart(this);
		pthread_attr_init(&mAttrHandle);
		pthread_create(&mThreadHandle, &mAttrHandle, mfProcess, this);
		mbStarted = true;
	}
	void Join() 
	{
		pthread_join(mThreadHandle , 0);
	}
};

/************************************************************************/
/*********************** sample thread-handlers *************************/
/************************************************************************/
cPool gPool(2000);

void *start(void * args)
{
	cThreadModule *mod = reinterpret_cast<cThreadModule*>(args);
	cout<<" starting thread ... "<< mod->GetName() <<endl;
}

void * process(void *args) 
{
	cThreadModule *mod = reinterpret_cast<cThreadModule*>(args);
	cout<<" processing thread ... "<< mod->GetName() <<endl;
	int iter = 0;
	while(mod->isAlive())
	{
		sMsg *msg = mod->DeQueue(true);
		if(msg) 
		{
			switch(msg->mCode)
			{
				case 1: /* kill */
					mod->Kill();
				break;
				default: break;
			}
		}
	}
}

void * end(void *args) 
{
	cThreadModule *mod = reinterpret_cast<cThreadModule*>(args);
	cout<<" ending thread ... "<< mod->GetName() <<endl;
}

/************************************************************************/
/**************************  usage  - main ******************************/
/************************************************************************/
int main() 
{
	cThreadModule w1(string("worker1"), start, end, process);
	cThreadModule w2(string("worker2"), start, end, process);
	cThreadModule p1(string("producer1"), start,end, process);
	cThreadModule p2(string("producer2"), start, end, process);

	w1.Run();
	w2.Run();
	p1.Run();
	p2.Run();


	w1.Join();
	w2.Join();
	p1.Join();
	p2.Join();
}

