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

class cMsg 
{
		int mCode;
		int mSubCode;
		int mParamType;
		int mLengthOfData;
		char mData[eSystem::eMaxMsgDataSz];
		bool mFree = true;
	public:
		cMsg() : mCode(0), mSubCode(0), mParamType(0) , mLengthOfData(0)
		{
			 memset(mData,0,eSystem::eMaxMsgDataSz); 
		}
		~cMsg() {}
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
		cMsg& operator=(const cMsg& rhs)
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
		bool operator==(const cMsg& rhs)
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
	cMsg ** mPool;
	public:
		cPool(int vSz) : mSz(vSz) , mPool(0) 
		{
			mPool = new cMsg*[vSz];
			for(int i = 0; i< vSz; ++i) 
			{
				mPool[i] = new cMsg();
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
		cMsg *Malloc() 
		{
			cMsg *p = 0; 
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
		void Free(cMsg * vArg) 
		{
			vArg->SetFree(true);
		}
};

class cQueue 
{
	cMsg **mMsgHolder;
	pthread_cond_t mCondHandle; /* cond = newmsg */
	pthread_condattr_t mCondAttrHandle;
	pthread_mutex_t mMutex;
	int mSz;
	int mReadHead;
	int mWriteHead;
	int mCurrentSize;
	bool flag = false;
public:
	cQueue()
	{
		mMsgHolder = 0;
		mReadHead = 0;
		mWriteHead = 0;
		pthread_condattr_init(&mCondAttrHandle);
		pthread_cond_init(&mCondHandle, &mCondAttrHandle);
	}
	~cQueue()
	{
		pthread_cond_destroy(&mCondHandle);
		pthread_condattr_destroy(&mCondAttrHandle);
		if(mSz) delete [] mMsgHolder;
	}
	void Init(int vSz) 
	{
		mCurrentSize = mSz = vSz;
		mMsgHolder = new cMsg*[vSz];
	}
	int GetCurrentSize()
	{
		return mCurrentSize ;
	}
	cMsg* deQueue(bool block=true)
	{
		cMsg *p = 0;
		pthread_mutex_lock(&mMutex);
		if(block) {
			while(!flag) pthread_cond_wait(&mCondHandle, &mMutex);
		}
	
		if(mCurrentSize != 0) 
		{
			p  = mMsgHolder[mReadHead];
			mReadHead ++;
			if(mReadHead == mSz) mReadHead = 0;
			mCurrentSize ++;
		}	
		flag = false;
		pthread_mutex_unlock(&mMutex);
	}
	void enQueue(cMsg* p)
	{
	
		pthread_mutex_lock(&mMutex);
		
		if(mCurrentSize != mSz) 
		{		
			mMsgHolder[mWriteHead] = p;
			mWriteHead ++;
			if(mWriteHead == mSz) mWriteHead = 0;
			mCurrentSize --;
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
	cQueue mQueue;
	public:
	cThreadModule(string &&vName, functor vfStart, 
		functor vfEnd, functor vfProcess) : 
		mfStart(vfStart), mfEnd(vfEnd), mfProcess(vfProcess) ,mbStarted(false) 
	{ 
		mName = move(vName); 
	}
	~cThreadModule() 
	{
		if(mbStarted) 
		{
			mfEnd(0);
			pthread_attr_destroy(&mAttrHandle);
		}
	}
	void Run(void * vArgs = 0 ) 
	{
		if(mbStarted) return;
		mfStart(0);
		pthread_attr_init(&mAttrHandle);
		pthread_create(&mThreadHandle, &mAttrHandle, mfProcess, vArgs);
		mbStarted = true;
	}
	void Join() 
	{
		pthread_join(mThreadHandle , 0);
	}
};

/************************************************************************/

