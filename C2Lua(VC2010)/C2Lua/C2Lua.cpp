#include "C2Lua.h"

const char* code_Grp[] = {
	"char* CFunction(int a,float b,const char* c);\r\n",
	"uint32_t millis();",
	"double getsum(float n1, float n2);",
	"char *getStr(void);",
	"unsigned long gpio_set(uint8_t pin, bool val);",
	"const char * UserInput();",
	"void Nop();",
	"int8_t* test1(userType* n1, UINT *n2, char* str);"
};

void toLua(const char* code)
{
	CheckOriFunctionInfo(code);
	String funcParam = CheckFunctionInfo(code);

	int paramNum = 0;
	if(funcParam != "void")
	{
		paramNum = CheckParamInfo(funcParam);
	}

	CreatLuaAPI(FunctionType, FunctionName, paramNum, CParamList);
}


int main(int argc, const char* argv[])
{
	for(int i = 0; i < __Sizeof(code_Grp); i++)
	{
		toLua(code_Grp[i]);
	}

	system("pause");
	return 0;
}
