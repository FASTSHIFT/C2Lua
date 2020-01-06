#include "C2Lua.h"

typedef struct {
	String ctype;
	String luafunc;
}Ctype2LuaFunc_TypeDef;

Ctype2LuaFunc_TypeDef TypeInfo_Grp[] = {
	{"char*",    "string"  },//string
	{"String",   "string"  },//Arduino String
	{"float",    "number"  },//float
	{"double",   "number"  }//double
};

#define API_PRINTF(format, ...)\
do{\
	if(fp)fprintf(fp, format, ##__VA_ARGS__);\
	printf(format, ##__VA_ARGS__);\
}while(0)

#define API_TAB       "    "
#define API_LINEFEED  "\n"
#define API_ANNOTATION(format, ...) API_PRINTF(API_LINEFEED API_TAB"/* "format" */" API_LINEFEED, ##__VA_ARGS__);

String CheckLuaType(String CType)
{
	String type = "integer";
	for(int i = 0; i < __Sizeof(TypeInfo_Grp); i++)
	{
		if(CType.indexOf(TypeInfo_Grp[i].ctype) >= 0)
		{
			type = TypeInfo_Grp[i].luafunc;
			break;
		}
	}
	return type;
}

#define IS_NUM_POINT(type) (type.endsWith("*") && type.indexOf("char") < 0)

static String PointerProcess(String type)
{
	if(IS_NUM_POINT(type))
	{
		type.replace("*","");
	}
	return type;
}

void CreatLuaAPI(CParam_TypeDef func, int paramNum, CParam_TypeDef* paramList, FILE* fp)
{
	PRINT_FUNC_NAME();

	/*函数名+形参*/
	/*static int Lua_xxx(lua_State* L)*/
	API_PRINTF(API_LINEFEED"static int Lua_%s(lua_State* L)", func.name.c_str());

	/*{*/
	API_PRINTF(API_LINEFEED"{");

	/*检查形参*/
	if(paramNum > 0)
	{
		/*从lua获取形参*/
		/*注释*/
		API_ANNOTATION("get %d param(s) from lua", paramNum);
		for(int i = 0; i < paramNum; i++)
		{
			/*匹配合适的Lua数据类型*/
			String luaType = CheckLuaType(paramList[i].type);

			/*匹配合适的参数接收数据类型 */
			String paramType = PointerProcess(paramList[i].type);

			/*x_t x = luaL_checkxxx(L, x);*/
			API_PRINTF(API_TAB);
			API_PRINTF("%s %s = luaL_check%s(L, %d);"API_LINEFEED,
				paramType.c_str(),
				paramList[i].name.c_str(),
				luaType.c_str(),
				i + 1
			);
		}
	}

	/*注释*/
	API_ANNOTATION("call c function");

	API_PRINTF(API_TAB);
	int retnum = 0;
	/*接收函数的返回值*/
	/*函数是否返回参数*/
	if(func.type != "void")
	{
		/*匹配合适的参数接收数据类型 */
		String type = PointerProcess(func.type);

		/*x_t x_retval = */
		API_PRINTF("%s %s_retval = ",type.c_str(), func.name.c_str());
		retnum = 1;
	}

	/*判断函数的返回值是否为指针类型，是的话加*号取实体*/
	if(IS_NUM_POINT(func.type))
	{
		API_PRINTF("*");
	}
	/*xfunc(*/
	API_PRINTF("%s(",func.name.c_str());
	/*函数是否有形参*/
	if(paramNum > 0)
	{
		for(int i = 0; i < paramNum; i++)
		{
			/*是否需要取地址*/
			if(IS_NUM_POINT(paramList[i].type))
			{
				API_PRINTF("&");
			}

			/*(&)x*/
			API_PRINTF("%s",paramList[i].name.c_str());

			/*如果不是最后一个形参就添加 , */
			if(i < paramNum - 1)
				API_PRINTF(", ");
		}
	}
	/*);*/
	API_PRINTF(");"API_LINEFEED);

	/*如果需要返回参数*/
	if(retnum > 0)
	{
		/*注释*/
		API_ANNOTATION("push c function return value to lua");

		/*lua_pushxxx(L, x_retval);*/
		API_PRINTF(API_TAB);
		API_PRINTF("lua_push%s(L, %s_retval);"API_LINEFEED,CheckLuaType(func.type).c_str(),func.name.c_str());
	}

	/*return 0(1); */
	API_PRINTF(API_TAB);
	API_PRINTF("return %d;", retnum);

	/*}*/
	API_PRINTF(API_LINEFEED"}"API_LINEFEED);
}

void toLua(const char* code, FILE* fp)
{
	CheckOriFunctionInfo(code);
	String funcParam = CheckFunctionInfo(code);

	int paramNum = 0;
	if(funcParam != "void")
	{
		paramNum = CheckParamInfo(funcParam);
	}

	CreatLuaAPI(CurrentFunction, paramNum, CParamList, fp);
}
