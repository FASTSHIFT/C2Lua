#ifndef __C2LUA_H
#define __C2LUA_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "WString\WString.h"
#include "WString\WCharacter.h"

#define __Sizeof(arr) (sizeof(arr)/sizeof(arr[0]))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define PRINT_FUNC_NAME() printf("\r\n--------"__FUNCTION__"--------\r\n")

typedef struct {
	String type;
	String name;
}CParam_TypeDef;

extern CParam_TypeDef CParamList[100];
extern CParam_TypeDef CurrentFunction;

void CheckOriFunctionInfo(const char* str);
int CheckParamInfo(String functionParam);
String CheckFunctionInfo(String codeStr);

void CreatLuaAPI(CParam_TypeDef func, int paramNum, CParam_TypeDef* paramList, FILE* fp);
void toLua(const char* code, FILE* fp);

bool LoadHeadFile(String inputPath, String outputPath);

#endif
