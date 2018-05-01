#include "Common.h"
#include "GCMemoryManager.h"

const enum {PoolSize = 32};
GCMemoryManager gMemoryManager;

void GCMemoryManager::expandPoolSize()
{
	// TODO : be dynamic bucket
	size_t size = (sizeof(Complex) > sizeof(FreeStore*)) ?
		sizeof(Complex) : sizeof(FreeStore*);

	FreeStore* head = reinterpret_cast<FreeStore*>(new char[size]);
	freeStoreHead = head;

	for (int i = 0; i < PoolSize; i++)
	{
		head->next = reinterpret_cast<FreeStore*> (new char[size]);
		head = head->next;
	}
	head->next = nullptr;
}

void GCMemoryManager::cleanUp()
{
	FreeStore* nextPtr = freeStoreHead;
	for (; nextPtr; nextPtr = freeStoreHead)
	{
		freeStoreHead = freeStoreHead->next;
		delete[] nextPtr; // this was a char array
	}
}

GCMemoryManager::GCMemoryManager()
{
	freeStoreHead = nullptr;
	expandPoolSize();
}


GCMemoryManager::~GCMemoryManager()
{
}

void * GCMemoryManager::allocate(size_t)
{
	if (freeStoreHead == nullptr)
		expandPoolSize();

	FreeStore* head = freeStoreHead;
	freeStoreHead = head->next;
	return head;
}

void GCMemoryManager::free(void* tobeDeleted)
{
	FreeStore* head = static_cast<FreeStore*> (tobeDeleted);
	head->next = freeStoreHead;
	freeStoreHead = head;
}


