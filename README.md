# C2Lua
> C binding to Lua

## 1.自动解析C头文件内的函数声明
```C
int8_t* test1(userType* n1, UINT *n2, char* str);
···

## 2.生成供Lua调用的绑定函数
```C
static int Lua_test1(lua_State* L)
{
    /* get params from lua */
    userType n1 = luaL_checkinteger(L, 1);
    UINT n2 = luaL_checkinteger(L, 2);
    char* str = luaL_checkstring(L, 3);

    /* call c function */
    int8_t test1_retval = *test1(&n1, &n2, str);

    /* push c function return value to lua */
    lua_pushinteger(L, test1_retval);
    return 1;
}
···
