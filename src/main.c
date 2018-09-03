#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/Exception.h"
#include "../include/Ultility.h"
#include "../include/ArrayList.h"
#include "../include/Register.h"

#define MAX_REGISTERS 1000UL	


extern FILE* PartitionCreate(void);
extern FILE* CreateTestFile(void* tupl);
extern void PartitionClose(FILE* file);
static unsigned partitionsCounter = 0;
static void PrintPartitions(void);

static int compare(Object obj1, Object obj2)
{
	int res;

	res = (((Register)obj1)->rField.bit.key - ((Register)obj2)->rField.bit.key);

	return res;
}

static void format(Object obj)
{
	printf("%i\n",((Register)obj)->rField.bit.key);
}

void SubstitutionSelection(FILE* file, int mregisters)
{
	FILE* partition;
	ArrayList registers;
	ArrayList frozenRegisters; 
	struct Register reg;
	Register r;
	bool endFile = false;
	int resWrite, resRead;

	registers = newArrayList(mregisters);
	frozenRegisters = newArrayList(mregisters); 

	ReWind(file);
	partition = PartitionCreate();
	partitionsCounter += 1;

	foreach_mRegisters(reg, file, mregisters)
	{
		insertSorted(registers, newRegister(reg), compare);
	}
	    
	do
	{
		r = removeTopList(registers);
		FileWrite(r, sizeof(struct Register), 1, partition, resWrite);
		FileRead(&reg, sizeof(struct Register),1, file, resRead);
		
		if(resRead > 0)
		{
			if((reg.rField.bit.key < r->rField.bit.key) && (getListSize(frozenRegisters) < mregisters))
			{
				reg.rField.bit.freeze = true;
				insertSorted(frozenRegisters, newRegister(reg), compare);
			}
			else if(getListSize(registers) < mregisters)
			{
				insertSorted(registers, newRegister(reg), compare);
			}
			else if(fullArrayList(frozenRegisters) == true && isEmpty(registers) == true )
			{
				Register temp;
				
				while(isEmpty(frozenRegisters))
				{
					temp = removeTopList(frozenRegisters);
					temp->rField.bit.freeze = false;
					insertSorted(registers,temp,compare);
				}
			}
		}
		else
		{
			if(!isEmpty(frozenRegisters))
			{
				Register temp;

				PartitionClose(partition);
				partition = PartitionCreate();
				partitionsCounter += 1;

				while(!isEmpty(frozenRegisters))
				{
					temp = removeTopList(frozenRegisters);
					temp->rField.bit.freeze = false;
					insertSorted(registers,temp,compare);
				}

				foreach_ArrayList(r, registers)
				{
				 	FileWrite(r, sizeof(struct Register), 1, partition, resWrite);
				}

				endFile = true;
			}
		}

	}while(endFile != true);

	PartitionClose(partition);
	destroyArrayList(registers);
	destroyArrayList(frozenRegisters);

}

void PrintPartitions(void)
{
	FILE* partition = NULL;
	char bufferStr[64];
	unsigned i;
	struct Register reg;

	for(i = 0; i < partitionsCounter; i++)
	{
		sprintf(bufferStr,"Partitions/Partition %u.bin",i);
		FileOpen(partition, bufferStr, "rb");
		puts(bufferStr);
		PrintFile(partition);
	}	
}

int main(int argc, char const *argv[])
{
	FILE* file;
	int nReg,mregisters;

	unsigned long long sizeReg = sizeof(struct Register);

	scanf("%i",&nReg);
	scanf("%i",&mregisters);
	void* tupl[3] = {&nReg, CreateAleatoryRegister, &sizeReg};

	file = CreateTestFile(&tupl);
	puts("Arquivo Test");
	PrintFile(file);
	
	SubstitutionSelection(file, mregisters);

	PrintPartitions();

	FileClose(file);


	return 0;
}