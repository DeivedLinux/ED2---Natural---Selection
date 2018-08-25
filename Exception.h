#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <setjmp.h>
#include <stdlib.h>


#define try    										\
													\
	exception_code = setjmp(exception_buffer);		\
	if(!exception_code)								


#define catch(ObjException)	else if(ObjException.code == exception_code)
#define throw(code) longjmp(exception_buffer, code)
#define finally else


#define PrintExceptionStdOut(Obj) printf("File: %s Funçao: %s %d %s, Exception Code: %lu\n",__FILE__, __FUNCTION__, __LINE__, Obj.message, Obj.code)



#define FileOpen(ptr, filename, mode)				\
													\
	try												\
	{												\
		ptr = fopen(filename, mode);				\
		if(ptr == NULL)								\
		{											\
			throw(__FileOpenException__);			\
		}											\
	}catch(FileOpenException)						\
	{												\
		PrintExceptionStdOut(FileOpenException);	\
	}


#define FileWrite(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fwrite(ptr, size, count, file);		\
			if(res != (size*count))						\
			{	printf("%i\n",res);							\
				ExceptionType = __FileWriteException__;	\
				throw(__FileWriteException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileWriteException)							\
	{													\
		PrintExceptionStdOut(FileWriteException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define FileRead(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fread(ptr, size, count, file);		\
			if(res != (size*count))						\
			{											\
				ExceptionType = __FileReadException__;	\
				throw(__FileReadException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileReadException)							\
	{													\
		PrintExceptionStdOut(FileReadException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define ReWind(file)									\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			rewind(file);								\
			if(ferror(file))							\
			{											\
				ObjExceptionType = __ReWindException__;	\
				throw(__ReWindException__);				\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(ReWindExeption)								\
	{													\
		PrintExceptionStdOut(ReWindExeption);			\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define FileSeek(file, offset, origin)					\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			fseek(file, offset, origin);				\
			if(ferror(file))							\
			{											\
				ObjExceptionType=__FileSeekException__; \
				throw(__FileSeekException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileSeekException)							\
	{													\
		PrintExceptionStdOut(FileSeekException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define ClearErr(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			clearerr(file);								\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
		exit(-1);										\
	}



#define FileClose(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			if(fclose(file))							\
			{											\
				throw(__FileCloseException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileCloseException)							\
	{													\
		PrintExceptionStdOut(FileCloseException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
		abort();										\
	}



extern const struct ObjException
{
	unsigned char* message;
	unsigned long code; 
}Exception;



extern enum ObjExceptionType
{
	__NoExceptionsOccurred = 255,
	__FileOpenException__ = 1,
	__FileReadException__,
	__FileFlushException__,		
	__MemoryAllocationException__,
	__FileWriteException__,
	__NullPointerException__,
	__EndOfFileException__,
	__FileReOpenException__,
	__FileSeekException__,
	__PrintException__,
	__ReWindException__,
	__ClearErrorsException__,
	__FileCloseException__
}ExceptionType;


extern jmp_buf exception_buffer; 						
extern unsigned long  exception_code;
			
extern enum ObjExceptionType ExceptionType;
extern const struct ObjException NullPointerException;
extern const struct ObjException FileOpenException;
extern const struct ObjException Exception;
extern const struct ObjException FileWriteException;
extern const struct ObjException FileReadException;
extern const struct ObjException ReWindExeption;
extern const struct ObjException FileSeekException;
extern const struct ObjException ClearErrorsException;
extern const struct ObjException FileCloseException;
#endif