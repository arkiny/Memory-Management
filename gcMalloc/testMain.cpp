// GC means Ginger Cat, Not Garbage Collector
// From IBM's Building your own memory manager for C/C++ projects Tutorial
// I am going to develop the tutorial memory manager from the tutorial page.
// Goal - Speed, Robust, User convenience, Poratbility
// Useful strategy
//  1. Requset Large Memory Chunks
//  2. Optimize Common Request Size
//  3. Pool deleted Memory containers.

// Default Malloc : 0.4958
// Customized new : 0.0359


#include "Common.h"

int main(int argc, char* argv[])
{
	Complex* array[1000];
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	LARGE_INTEGER StartTime;
	QueryPerformanceCounter(&StartTime);
	
	for (int i = 0; i < 5000; i++) {
		for (int j = 0; j < 1000; j++) {
			array[j] = new Complex(i, j);
		}
		for (int j = 0; j < 1000; j++) {
			delete array[j];
		}
	}
	
	LARGE_INTEGER EndTime;
	QueryPerformanceCounter(&EndTime);
	signed long long elapsed = EndTime.QuadPart - StartTime.QuadPart;
	double duringtime = (double)elapsed / (double)Frequency.QuadPart;

	std::cout << "Malloc Time : " << duringtime << std::endl;

	system("pause");
	return 0;
}