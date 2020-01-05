#include "C2Lua.h"

Ctype2LuaFunc_TypeDef TypeInfo_Grp[] = {
	{"char*",    "string"  },
	{"unsigned", "integer" },//unsigned; uint; 
	{"uint",     "integer" },//uintx_t;
	{"int",      "integer" },//int; intx_t
	{"short",    "integer" },//short
	{"long",     "integer" },//long
	{"char",     "integer" },//char
	{"float",    "number"  },//float
	{"double",   "number"  }//double
	
};

#define API_Start     "static int Lua_%s(lua_State* L)"
#define API_TAB       "    "
#define API_LINEFEED  "\r\n"
#define API_ANNOTATION(str)\
do{\
	printf(API_LINEFEED API_TAB"/* "str" */\r\n");\
}while(0)

String CheckLuaType(String CType)
{
	String type = "integer";
	for(int i = 0; i < __Sizeof(TypeInfo_Grp); i++)
	{
		if(CType.indexOf(TypeInfo_Grp[i].ctype) >= 0)
		{
			type =  TypeInfo_Grp[i].luafunc;
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

void CreatLuaAPI(String funcType, String funcName, int paramNum, CParamList_TypeDef* paramList)
{
	printf("\r\n--------"__FUNCTION__"---------\r\n");
	printf(API_Start,funcName.c_str());
	printf("\r\n{");

	/*printf("paramNum = %d\r\n", paramNum);
	for(int i = 0; i < paramNum; i++)
	{
		printf("paramList[%d]:%s-%s\r\n", i, paramList[i].type.c_str(), paramList[i].name.c_str());
	}*/

	/*检查形参*/
	if(paramNum > 0)
	{
		/*从lua获取形参*/
		API_ANNOTATION("get params from lua");
		for(int i = 0; i < paramNum; i++)
		{
			String luaType = CheckLuaType(paramList[i].type);

			String paramType = PointerProcess(paramList[i].type);

			printf(API_TAB);
			printf("%s %s = luaL_check%s(L, %d);\r\n",
				paramType.c_str(),
				paramList[i].name.c_str(),
				luaType.c_str(),
				i + 1
			);
		}
	}

	API_ANNOTATION("call c function");

	printf(API_TAB);
	int retnum = 0;
	if(funcType != "void")
	{
		String type = PointerProcess(funcType);
		printf("%s %s_retval = ",type.c_str(), funcName.c_str());
		retnum = 1;
	}

	if(IS_NUM_POINT(funcType))
	{
		printf("*");
	}
	printf("%s(",funcName.c_str());
	if(paramNum > 0)
	{
		for(int i = 0; i < paramNum; i++)
		{
			if(IS_NUM_POINT(paramList[i].type))
			{
				printf("&");
			}

			printf("%s",paramList[i].name.c_str());
			if(i < paramNum - 1)
				printf(", ");
		}
	}
	printf(");\r\n");

	if(retnum > 0)
	{
		API_ANNOTATION("push c function return value to lua");

		printf(API_TAB);
		printf("lua_push%s(L, %s_retval);\r\n",CheckLuaType(funcType).c_str(),funcName.c_str());
	}

	printf(API_TAB);
	printf("return %d;", retnum);
	printf("\r\n}\r\n");
}
