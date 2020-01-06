#include "C2Lua.h"

const char* code_Grp[] = {
	"char* CFunction(int a,float b,const char* c);",
	"uint32_t millis();",
	"double getsum(float n1, float n2);",
	"char *getStr(void);",
	"unsigned long gpio_set(uint8_t pin, bool val);",
	"const char * UserInput();",
	"void Nop();",
	"double* testFunc(float* n1, int* n2, const char* str);"
};


int main(int argc, const char* argv[])
{
	if(argc != 5)
	{
		printf("error param! example: -i xxx.h -o xxx.c");
		system("pause");
		return -1;
	}

	String inputFile,outputFile;
	for(int i = 0; i < argc; i++)
	{
		String argval = argv[i];
		printf("arg[%d]:%s\r\n",i, argval.c_str());
		if(argval == "-i")
		{
			inputFile = argv[i + 1];
		}
		else if(argval == "-o")
		{
			outputFile = argv[i + 1];
		}
	}
	LoadHeadFile(inputFile, outputFile);

	/*for(int i = 0; i < __Sizeof(code_Grp); i++)
	{
		toLua(code_Grp[i]);
	}*/

	system("pause");
	return 1;
}
