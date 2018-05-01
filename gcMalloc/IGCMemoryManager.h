#pragma once

class IGCMemoryManager
{
public:
	virtual void* allocate(size_t) = 0;
	virtual void free(void*) = 0;
};
