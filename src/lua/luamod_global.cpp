#include "luamod_global.h"
#include "build.h"

void lu_luamod::init_api(lua_State *L)
{
    lua_pushstring(L, LM_buildversion());
    lua_setglobal(L, "LUAMOD_VERSION");

    lua_pushstring(L, MOD_PATH);
    lua_setglobal(L, "MOD_PATH");

#if !defined(XASH3D)
    lua_pushstring(L, "goldsrc");
#else
    lua_pushstring(L, "xash3d");
#endif
    lua_setglobal(L, "ENGINE");

    lua_pushlightuserdata(L, gpMetaGlobals);
    lua_setglobal(L, "METAMOD_GLOBALS");

    lua_pushlightuserdata(L, gpGlobals);
    lua_setglobal(L, "GAME_GLOBALS");

    lua_pushlightuserdata(L, &g_engfuncs);
    lua_setglobal(L, "ENGINE_FUNCTIONS");
}
