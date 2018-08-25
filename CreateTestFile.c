#include <stdio.h>
#include <stdlib.h>
#include "Exception.h"





FILE* CreateTestFile(void* tupl)
{
	FILE* newTestFile = NULL;
	unsigned i;
	int random;
	int n;
	void*(*func)(void);
	void* ptr;
	unsigned offset;
	int res;
	FileOpen(newTestFile, "TestFile.bin", "w+b");

	n = *((int*)(((void**)tupl)[0]));
	func = ((void*(*)(void))(((void**)tupl)[1]));
	offset = *((unsigned long *)(((void**)tupl)[2]));

	
	for(i = 0; i < n; i++)
	{
		ptr = func();
		FileWrite(ptr, sizeof(char), offset, newTestFile, res);
		free(ptr);
	}
	

	return newTestFile;
}