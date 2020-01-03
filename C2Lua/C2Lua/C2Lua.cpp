#include "C2Lua.h"

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct {
	const char* ctype;
	const char* luafunc;
}Ctype2LuaFunc_TypeDef;

Ctype2LuaFunc_TypeDef TypeInfo_Grp[] = {
	{"unsigned", "integer" },//unsigned; uint; 
	{"uint",     "integer" },//uintx_t;
	{"int",      "integer" },//int; intx_t
	{"short",    "integer" },//short
	{"long",     "integer" },//long
	{"char",     "integer" },//char
	{"float",    "number"  },//float
	{"double",   "number"  },//double
};

const char code[] =
"\r\n    int * func     (    \r\n  int****a0_    ,  long   long   **b6  ,const uint8_t __c__    \r\n  )  ;   \r\n";

void PrintOriginFunctionInfo(const char* str)
{
	int len = strlen(str);
	printf("\r\n--------------------\r\n");
	printf(">>text:\r\n%s\r\n <size:%d>\r\n", str, len);
	printf("\r\n--------------------\r\n");
}

void GetNextParam(String param)
{
	param.trim();
//	printf("ParamSrc:<%s>-", param.c_str());

	int indexp = param.lastIndexOf('*');
	int index = param.lastIndexOf(' ');
//	printf("  indexp=%d,index=%d  ", indexp, index);
	index = MAX(index, indexp);
	
	String ParamName = param.substring(index + 1);
	printf("Name:<%s>-", ParamName.c_str());

	String ParamType = param.substring(0, index + 1);
	ParamType.trim();
	ParamType.replace(" ", "");
	printf("Type:<%s>\r\n", ParamType.c_str());
}

int CheckParamInfo(String functionParam)
{
	int ParamNum = 1;
	while (true)
	{
		printf("Param%d:", ParamNum);
		int index = functionParam.indexOf(',');
		if (index > 0)
		{
			String param = functionParam.substring(0, index);
			GetNextParam(param);
			functionParam = functionParam.substring(index + 1);
		}
		else
		{
			GetNextParam(functionParam);
			break;
		}
		ParamNum++;
	}
	return ParamNum;
}

String CheckFunctionInfo(String codeStr)
{
	codeStr.replace("\n", "");
	codeStr.replace("\r", "");
	codeStr.trim();

	/*函数返回值*/
	int indexp = codeStr.indexOf('*');
	int index = codeStr.indexOf(' ');
	index = MAX(indexp, index) + 1;
	String FunctionType = codeStr.substring(0, index);
	FunctionType.replace(" ","");
	printf("Type:<%s>\r\n", FunctionType.c_str());

	/*函数名*/
	codeStr = codeStr.substring(index);
	codeStr.trim();
	index = codeStr.indexOf('(');
	String FunctionName = codeStr.substring(0, index);
	FunctionName.trim();
	printf("Name:<%s>\r\n", FunctionName.c_str());

	/*函数参数*/
	codeStr = codeStr.substring(index);
	codeStr.trim();
	index = codeStr.indexOf(')');
	String FunctionParam = codeStr.substring(1, index);
	FunctionParam.trim();
	printf("Param:<%s>\r\n", FunctionParam.c_str());

	if (FunctionParam == "" || FunctionParam.indexOf("void") >= 0)
	{
		printf("no param");
		return "";
	}

	return FunctionParam;
}

int main(int argc, const char*argv[])
{
	PrintOriginFunctionInfo(code);
	String funcParam = CheckFunctionInfo(code);
	CheckParamInfo(funcParam);

	system("pause");
	return 0;
}
