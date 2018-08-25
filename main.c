#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Exception.h"

extern FILE* PartitionCreate(void);
extern FILE* CreateTestFile(void* tupl);


typedef struct Register
{
	union
	{
		unsigned int;
		struct 
		{
			unsigned key:31;
			unsigned freeze:1;
		}bit;
	}rField;
}*Register;

void* CreateAleatoryRegister(void)
{
	Register newRegister;

	newRegister = (Register)malloc(sizeof(struct Register));

	newRegister->rField.bit.key = rand();
	newRegister->rField.bit.freeze = false;

	return newRegister;
}



int main(int argc, char const *argv[])
{
	FILE* file
	int nReg;
	unsigned long long sizeReg = sizeof(struct Register);

	scanf("%i",&nReg);


	void* tupl[3] = {&nReg, CreateAleatoryRegister, &sizeReg};

	file = CreateTestFile(&tupl);
	

	return 0;
}