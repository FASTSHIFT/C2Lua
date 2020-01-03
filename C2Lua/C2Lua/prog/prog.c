#include "prog.h"

int func(int i)
{
	return i++;
}

static int Lua_func(lua_State *L)
{
    int n = luaL_checkinteger(L, 1);
    func(n);
    return 1;
}
