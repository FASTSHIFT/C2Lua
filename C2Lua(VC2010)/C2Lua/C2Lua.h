#ifndef __C2LUA_H
#define __C2LUA_H

#include <stdio.h>
#include <stdint.h>
#include "WString.h"
#include "WCharacter.h"

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct {
	String ctype;
	String luafunc;
}Ctype2LuaFunc_TypeDef;

typedef struct {
	String type;
	String name;
}CParamList_TypeDef;

extern CParamList_TypeDef CParamList[100];
extern String FunctionType, FunctionName;

void CheckOriFunctionInfo(const char* str);
int CheckParamInfo(String functionParam);
String CheckFunctionInfo(String codeStr);

void CreatLuaAPI(String funcType, String funcName, int paramNum, CParamList_TypeDef* paramList);

#endif
