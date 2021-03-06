#include "luamod_engfuncs.h"
#include <cvar_manager.h>
#include <vector>

#ifdef REHLDS_SUPPORT
#include "ex_rehlds_api.h"
#endif

static const luaL_Reg enginefuncs_lib[] =
{
        {"precache_model", lu_engfuncs::l_pfnPrecacheModel},
        {"precache_sound", lu_engfuncs::l_pfnPrecacheSound},

        {"find_entity_by_string", lu_engfuncs::l_pfnFindEntityByString},
        {"find_entities_by_string", lu_engfuncs::l_pfnFindEntitiesByString},

        {"remove_entity", lu_engfuncs::l_pfnRemoveEntity},

        {"server_command", lu_engfuncs::l_pfnServerCommand},
        {"server_execute", lu_engfuncs::l_pfnServerExecute},
        {"client_command", lu_engfuncs::l_pfnClientCommand},

        {"set_client_key_value", lu_engfuncs::l_pfnSetClientKeyValue},
        {"info_key_value", lu_engfuncs::l_pfnInfoKeyValue},
        {"get_info_key_buffer", lu_engfuncs::l_pfnGetInfoKeyBuffer},

        {"message_begin", lu_engfuncs::l_pfnMessageBegin},
        {"message_end", lu_engfuncs::l_pfnMessageEnd},
        {"write_byte", lu_engfuncs::l_pfnWriteByte},
        {"write_char", lu_engfuncs::l_pfnWriteChar},
        {"write_short", lu_engfuncs::l_pfnWriteShort},
        {"write_long", lu_engfuncs::l_pfnWriteLong},
        {"write_angle", lu_engfuncs::l_pfnWriteAngle},
        {"write_coord", lu_engfuncs::l_pfnWriteCoord},
        {"write_string", lu_engfuncs::l_pfnWriteString},
        {"write_entity", lu_engfuncs::l_pfnWriteEntity},

        {"get_player_userid", lu_engfuncs::l_pfnGetPlayerUserId},
        {"get_player_stats", lu_engfuncs::l_pfnGetPlayerStats},
        {"get_player_authid", lu_engfuncs::l_pfnGetPlayerAuthId},

        {"cvar_register", lu_engfuncs::l_pfnRegister_Cvar},
        {"cvar_get_float", lu_engfuncs::l_pfnCVarGetFloat},
        {"cvar_get_string", lu_engfuncs::l_pfnCVarGetString},
        {"cvar_set_float", lu_engfuncs::l_pfnCVarSetFloat},
        {"cvar_set_string", lu_engfuncs::l_pfnCVarSetString},

        {"index_of_edict", lu_engfuncs::l_pfnIndexOfEdict},
        {"edict_of_index", lu_engfuncs::l_pfnPEntityOfEntIndex},

        {"reg_user_msg", lu_engfuncs::l_pfnRegUserMsg},

        {"client_printf", lu_engfuncs::l_pfnClientPrintf},
        {"add_server_command", lu_engfuncs::l_pfnAddServerCommand},
        {"server_print", lu_engfuncs::l_pfnServerPrint},

        {"query_client_cvar_value2", lu_engfuncs::l_pfnQueryClientCvarValue2},

        #ifdef REHLDS_SUPPORT
        // REHLDS
        #endif

        {NULL,NULL}
};

void lu_engfuncs::init_api(lua_State *L)
{
    luaL_register(L, "engine", enginefuncs_lib);
}

int lu_engfuncs::l_pfnPrecacheModel(lua_State *L)
{
    PRECACHE_MODEL(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnPrecacheSound(lua_State *L)
{
    PRECACHE_SOUND(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnFindEntityByString(lua_State *L)
{
    edict_t *e = luaL_checkedict(L, 1, true);
    const char *field = luaL_checkstring(L, 2);
    const char *value = luaL_checkstring(L, 3);
    edict_t *e2 = FIND_ENTITY_BY_STRING(e,  field, value);

    lua_pushedict(L, e2);
    return 1;
}

int lu_engfuncs::l_pfnFindEntitiesByString(lua_State *L)
{
    const edict_t *e0 = INDEXENT(0);
    edict_t *e = luaL_checkedict(L, 1, true);
    const char *field = luaL_checkstring(L, 2);
    const char *value = luaL_checkstring(L, 3);
    edict_t *e2 = FIND_ENTITY_BY_STRING(e,  field, value);

    if(e2 == e0)
    {
        // try to find woldspawn but its always have zero index
        if(!strcmp(value, "worlspawn") && !strcmp(field, "classname"))
            luaL_error(L, "try to find worlspawn");

        lua_newtable(L);
        return 1;
    }

    lua_newtable(L);

    int count = 1;

    lua_pushinteger(L, count++);
    lua_pushedict(L, e2);
    lua_settable(L,-3);

    while (true) {
        e2 = FIND_ENTITY_BY_STRING(e2, field, value);

        if(e2 != e0)
        {
            lua_pushinteger(L, count++);
            lua_pushedict(L, e2);
            lua_settable(L,-3);
        } else {
            break;
        }
    }

    return 1;
}

int lu_engfuncs::l_pfnRemoveEntity(lua_State *L)
{
    REMOVE_ENTITY(luaL_checkedict(L, 1, false));
    return 0;
}

int lu_engfuncs::l_pfnServerCommand(lua_State *L)
{
    SERVER_COMMAND(va("%s\n", luaL_checkstring(L, 1)));
    return 0;
}

int lu_engfuncs::l_pfnServerExecute(lua_State *L)
{
    SERVER_EXECUTE();
    return 0;
}

int lu_engfuncs::l_pfnClientCommand(lua_State *L)
{
    CLIENT_COMMAND(luaL_checkedict(L, 1, 0), "%s\n", luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnMessageBegin(lua_State *L)
{
    const float *origin = NULL;

    if( !lua_isnil(L, 3) )
    {
        origin = luaL_checkvec3_t(L, 3);
    }

    MESSAGE_BEGIN(luaL_checkinteger(L, 1), luaL_checkinteger(L, 2), origin, luaL_checkedict(L, 4, 1));
    return 0;
}

int lu_engfuncs::l_pfnMessageEnd(lua_State *L)
{
    MESSAGE_END();
    return 0;
}

int lu_engfuncs::l_pfnWriteByte(lua_State *L)
{
    WRITE_BYTE(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteChar(lua_State *L)
{
    WRITE_CHAR(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteShort(lua_State *L)
{
    WRITE_SHORT(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteLong(lua_State *L)
{
    WRITE_LONG(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteAngle(lua_State *L)
{
    WRITE_ANGLE(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteCoord(lua_State *L)
{
    WRITE_COORD(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteString(lua_State *L)
{
    WRITE_STRING(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteEntity(lua_State *L)
{
    WRITE_ENTITY(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnGetInfoKeyBuffer(lua_State *L)
{
    lua_pushlightuserdata(L, GET_INFOKEYBUFFER(luaL_checkedict(L, 1, 1)));
    return 1;
}

int lu_engfuncs::l_pfnInfoKeyValue(lua_State *L)
{
    lua_pushstring(L, INFOKEY_VALUE((char*)lua_touserdata(L, 1), luaL_checkstring(L, 2)));
    return 1;
}

int lu_engfuncs::l_pfnSetKeyValue(lua_State *L)
{
    g_engfuncs.pfnSetKeyValue((char*)lua_touserdata(L, 1), luaL_checkstring(L, 2), luaL_checkstring(L, 3));
    return 0;
}

int lu_engfuncs::l_pfnSetClientKeyValue(lua_State *L)
{
    g_engfuncs.pfnSetClientKeyValue(luaL_checkinteger(L, 1), (char*)lua_touserdata(L, 2), luaL_checkstring(L, 3), luaL_checkstring(L, 4));
    return 0;
}

int lu_engfuncs::l_pfnGetPlayerUserId(lua_State *L)
{
    lua_pushinteger(L, GETPLAYERUSERID(luaL_checkedict(L, 1, 0)));
    return 1;
}

/*
int lu_engfuncs::l_pfnGetPlayerWONId(lua_State *L)
{
    lua_pushinteger(L, g_engfuncs.pfnGetPlayerWONId())
}
*/

int lu_engfuncs::l_pfnGetPlayerStats(lua_State *L)
{
    int ping = 0;
    int packet_lost = 0;
    g_engfuncs.pfnGetPlayerStats(luaL_checkedict(L, 1, 0), &ping, &packet_lost);

    lua_newtable(L);
    lua_pushnumber(L, ping);
    lua_setfield(L, -2, "ping");
    lua_pushnumber(L, packet_lost);
    lua_setfield(L, -2, "packet_lost");
    return 1;
}

int lu_engfuncs::l_pfnGetPlayerAuthId(lua_State *L)
{
    lua_pushstring(L, GETPLAYERAUTHID(luaL_checkedict(L, 1, 0)));
    return 1;
}

int lu_engfuncs::l_pfnRegister_Cvar(lua_State *L)
{

    if(lua_isnumber(L, 2))
      {
          Cvar_Manager_Register(luaL_checkstring(L, 1), luaL_checknumber(L, 2), NULL);
      } else if(lua_isstring(L, 2))
      {
          Cvar_Manager_Register(luaL_checkstring(L, 1), 0, luaL_checkstring(L, 2));
      } else
      {
          luaL_argerror(L, 2, "Not a number or string");
      }

    return 0;
}

int lu_engfuncs::l_pfnCVarGetFloat(lua_State *L)
{
    lua_pushnumber(L, CVAR_GET_FLOAT(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarGetString(lua_State *L)
{
    lua_pushstring(L, CVAR_GET_STRING(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarSetFloat(lua_State *L)
{
    CVAR_SET_FLOAT(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnCVarSetString(lua_State *L)
{
    CVAR_SET_STRING(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnIndexOfEdict(lua_State *L)
{
    lua_pushinteger(L, g_engfuncs.pfnIndexOfEdict(luaL_checkedict(L, 1, 1)));
    return 1;
}

int lu_engfuncs::l_pfnPEntityOfEntIndex(lua_State *L)
{
    lua_pushedict(L, INDEXENT(luaL_checkinteger(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnRegUserMsg(lua_State *L)
{
    lua_pushinteger(L, REG_USER_MSG(luaL_checkstring(L, 1), luaL_checkinteger(L, 2)));
    return 1;
}

int lu_engfuncs::l_pfnClientPrintf(lua_State *L)
{
    int print_type = (int)luaL_checkinteger(L, 2);
    if (print_type < 0 || print_type > 3)
        luaL_argerror(L, 2, "unknown print type");
    CLIENT_PRINTF(luaL_checkedict(L, 1, 0), (PRINT_TYPE)print_type, luaL_checkstring(L, 3));
    return 0;
}

static void pfnConsoleCmd_callback()
{
    // Use this name for server commands callback
    if (worker_have_event(core, "pfnConsoleCmd")) {
        // Push table
        lua_newtable(core);
        for (int i = 0; i < CMD_ARGC(); i++) {
            lua_pushnumber(core, i + 1); // Key
            lua_pushstring(core, CMD_ARGV(i)); // Value
            lua_settable(core, -3);
        }
        lua_pushstring(core, CMD_ARGS());
        worker_pcall(core, 2, 0);
    }
}

int lu_engfuncs::l_pfnAddServerCommand(lua_State *L)
{
    REG_SVR_COMMAND(luaL_checkstring(L, 1), pfnConsoleCmd_callback);
    return 0;
}

int lu_engfuncs::l_pfnServerPrint(lua_State *L)
{
    SERVER_PRINT(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnQueryClientCvarValue2(lua_State *L)
{
    QUERY_CLIENT_CVAR_VALUE2(luaL_checkedict(L, 1, 0), luaL_checkstring(L, 2), (int)luaL_checkinteger(L, 3));
    return 0;
}
