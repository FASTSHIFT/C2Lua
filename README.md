# C2Lua
> Lua接口全自动生成工具，支持指针、自定义数据类型。

## 1.解析C函数声明
```C
double* testFunc(float* n1, int n2, const char* str);
```

## 2.生成供Lua调用的绑定函数
```C
static int Lua_testFunc(lua_State* L)
{
    /* get params from lua */
    float n1 = luaL_checknumber(L, 1);
    int n2 = luaL_checkinteger(L, 2);
    const char* str = luaL_checkstring(L, 3);

    /* call c function */
    double testFunc_retval = *testFunc(&n1, n2, str);

    /* push c function return value to lua */
    lua_pushnumber(L, testFunc_retval);
    return 1;
}
```

## 3.Lua中调用
```lua
value = testFunc(3.14, 2, "hello C2Lua")
print(value)
```
