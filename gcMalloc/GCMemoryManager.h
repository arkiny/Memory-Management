#pragma once
#include "IGCMemoryManager.h"
// allocate
// 1. Create Free Store
// 2. if Free Store sold out, create new one
// 3. return the first free store and mark the next element as a free sotre

// free
// 1. Make the next filed in deleted point to the current free store
// 2. Mark the deleted pointer as the free store head


// override like this
//void* operator new(size_t size) 
//{
//	return gMemoryManager.allocate(size);
//}
//
//void* operator new[](size_t size)
//{
//	return gMemoryManager.allocate(size);
//}
//
//void operator delete(void* pointerToDelete)
//{
//	gMemoryManager.free(pointerToDelete);
//}
//
//void operator delete[](void* arrayToDelete)
//{
//	gMemoryManager.free(arrayToDelete);
//}

class GCMemoryManager :
	public IGCMemoryManager
{
	struct FreeStore
	{
		FreeStore *next;
	};
	void expandPoolSize();
	void cleanUp();
	FreeStore* freeStoreHead;
public:
	GCMemoryManager();
	virtual ~GCMemoryManager();
	
	// Inherited via IGCMemoryManager
	virtual void * allocate(size_t) override;

	virtual void  free(void *) override;
};

extern GCMemoryManager gMemoryManager;

// Test Complex Class
class Complex
{
public:
	Complex(double a, double b) : r(a), c(b) {}
	inline void * operator new(size_t size)
	{
		return gMemoryManager.allocate(size);
	}
	inline void operator delete(void * deleted)
	{
		gMemoryManager.free(deleted);
	}

private:
	double r;
	double c;
};
