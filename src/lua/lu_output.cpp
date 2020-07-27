#include "lu_output.h"

void lu_output::init_api(lua_State *L)
{
    lua_register(L, "print", print);
    lua_register(L, "log_console", log_console);
    lua_register(L, "log_message", log_message);
    lua_register(L, "log_error", log_error);
    lua_register(L, "log_developer", log_developer);
}

/* (-_-) */
int lu_output::print(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    ALERT(at_console, "%s\n", str);
    return 0;
}

/* log_console(message) */
int lu_output::log_console(lua_State *L)
{
    // int PLID = luaL_checkinteger(L, 1);
    const char *message = luaL_checkstring(L, 1);
    // LOG_CONSOLE(at_console, message);
    return 0;
}

/* log_message(message) */
int lu_output::log_message(lua_State *L)
{
    // int PLID = luaL_checkinteger(L, 1);
    const char *message = luaL_checkstring(L, 1);
    // LOG_MESSAGE(at_console, message);
    return 0;
}

/* log_error(message) */
int lu_output::log_error(lua_State *L)
{
    // int PLID = luaL_checkinteger(L, 1);
    const char *message = luaL_checkstring(L, 1);
    // LOG_ERROR(at_console, message);
    return 0;
}

/* log_developer(message) */
int lu_output::log_developer(lua_State *L)
{
    // int PLID = luaL_checkinteger(L, 1);
    const char *message = luaL_checkstring(L, 1);
    // LOG_DEVELOPER(at_console, message);
    return 0;
}
