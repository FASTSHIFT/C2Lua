#include "C2Lua.h"

CParam_TypeDef CurrentFunction;
CParam_TypeDef CParamList[100];

void CheckOriFunctionInfo(const char* str)
{
	PRINT_FUNC_NAME();
	printf("%s\r\n<size:%d>\r\n", str, strlen(str));
}

static void TypeParamSeparation(String param, String* type, String* name)
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
	/*ParamType.replace(" ","");
	if(ParamType.startsWith("const"))
	{
		ParamType.replace("const", "const ");
	}*/
	printf("Type:<%s>\r\n", ParamType.c_str());

	*type = ParamType;
	*name = ParamName;
}

static void AddNextParamToList(String param, int paramNum)
{
	if(paramNum < 1)
		return;

	String type, name;
	TypeParamSeparation(param, &type, &name);
	CParamList[paramNum - 1].type = type;
	CParamList[paramNum - 1].name = name;
}

int CheckParamInfo(String functionParam)
{
	PRINT_FUNC_NAME();
	int ParamNum = 1;

	while (true)
	{
		printf("Param%d:", ParamNum);
		/*寻找是否有下一个参数*/
		int index = functionParam.indexOf(',');
		if (index > 0)
		{
			String param = functionParam.substring(0, index);
			AddNextParamToList(param, ParamNum);
			functionParam = functionParam.substring(index + 1);
		}
		else
		{
			AddNextParamToList(functionParam, ParamNum);
			break;
		}
		ParamNum++;
	}

	return ParamNum;
}

String CheckFunctionInfo(String codeStr)
{
	PRINT_FUNC_NAME();
	codeStr.replace("\r","");
	codeStr.replace("\n","");
	codeStr.replace("\t","");
	codeStr.trim();

	/*函数*/
	int index = codeStr.indexOf('(');
	String Function = codeStr.substring(0, index);
	TypeParamSeparation(Function, &CurrentFunction.type, &CurrentFunction.name);

	/*函数参数*/
	codeStr = codeStr.substring(index);
	codeStr.trim();
	index = codeStr.indexOf(')');
	String FunctionParam = codeStr.substring(1, index);
	FunctionParam.trim();
	printf("Param:<%s>\r\n", FunctionParam.c_str());

	if (FunctionParam == "" || FunctionParam.indexOf("void") >= 0)
	{
		printf("<no param>");
		FunctionParam = "void";
	}

	return FunctionParam;
}
