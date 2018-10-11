#include "lu_engfuncs.hpp"
#include <vector>
#include <extdll.h>
#include <meta_api.h>

#ifdef REHLDS_SUPPORT
#include "ex_rehlds_api.h"
#endif

/*
int		(*pfnPrecacheModel)		(char* s);
int		(*pfnPrecacheSound)		(char* s);
int		(*pfnPrecacheGeneric)		(char* s);
 */

/*
void		(*pfnServerCommand)			(const char* str);
void		(*pfnServerExecute)			(void);
void		(*pfnClientCommand)			(edict_t* pEdict, const char* szFmt, ...);
 */

/*
void		(*pfnMessageBegin)			(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed);
void		(*pfnMessageEnd)			(void);
void		(*pfnWriteByte)				(int iValue);
void		(*pfnWriteChar)				(int iValue);
void		(*pfnWriteShort)			(int iValue);
void		(*pfnWriteLong)				(int iValue);
void		(*pfnWriteAngle)			(float flValue);
void		(*pfnWriteCoord)			(float flValue);
void		(*pfnWriteString)			(const char *sz);
void		(*pfnWriteEntity)			(int iValue);
 */

/*
void		(*pfnCVarRegister)			(cvar_t *pCvar);
float		(*pfnCVarGetFloat)			(const char *szVarName);
const char*	(*pfnCVarGetString)			(const char *szVarName);
void		(*pfnCVarSetFloat)			(const char *szVarName, float flValue);
void		(*pfnCVarSetString)			(const char *szVarName, const char *szValue);
cvar_t		(*pfnCVarGetPointer)		(const char *szVarName);
 */

/*
void		(*pfnClientPrintf)			( edict_t* pEdict, PRINT_TYPE ptype, const char *szMsg );
 */

void lu_engfuncs::init_api(lua_State *L) {
    lua_register(L, "precache_model", l_pfnPrecacheModel);
    lua_register(L, "precache_sound", l_pfnPrecacheSound);
    //lua_register(L, "precache_generic", l_pfnPrecacheGeneric);
    //
    lua_register(L, "server_command", l_pfnServerCommand);
    lua_register(L, "server_execute", l_pfnServerExecute);
    lua_register(L, "client_command", l_pfnClientCommand);
    //
    lua_register(L, "message_begin", l_pfnMessageBegin);
    lua_register(L, "message_end", l_pfnMessageEnd);
    lua_register(L, "write_byte", l_pfnWriteByte);
    lua_register(L, "write_char", l_pfnWriteChar);
    lua_register(L, "write_short", l_pfnWriteShort);
    lua_register(L, "write_long", l_pfnWriteLong);
    lua_register(L, "write_angle", l_pfnWriteAngle);
    lua_register(L, "write_coord", l_pfnWriteCoord);
    lua_register(L, "write_string", l_pfnWriteString);
    lua_register(L, "write_entity", l_pfnWriteEntity);
    //
    lua_register(L, "cvar_register", l_pfnRegister_Cvar);
    lua_register(L, "cvar_get_float", l_pfnCVarGetFloat);
    lua_register(L, "cvar_get_string", l_pfnCVarGetString);
    lua_register(L, "cvar_set_float", l_pfnCVarSetFloat);
    lua_register(L, "cvar_set_string", l_pfnCVarSetString);
    //
    lua_register(L, "client_printf", l_pfnClientPrintf);
    //
    #ifdef REHLDS_SUPPORT
    //REHLDS
    #endif
}

int lu_engfuncs::l_pfnPrecacheModel(lua_State *L) {
    PRECACHE_MODEL(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnPrecacheSound(lua_State *L) {
    PRECACHE_SOUND(luaL_checkstring(L, 1));
    return 0;
}
/*TODO: Удалить*/
//int lu_engfuncs::l_pfnPrecacheGeneric(lua_State *L) {
    // luaL_error(L, "SV_PrecacheGeneric: ( %s ). Precache can only be done in spawn functions.", luaL_checkstring(L, 1));
    //	PRECACHE_GENERIC(luaL_checkstring(L, 1));
    //return 1;
//}

int lu_engfuncs::l_pfnServerCommand(lua_State *L)
{
    char buff[256];
    snprintf(buff, 256,"%s\n", luaL_checkstring(L,1));
    SERVER_COMMAND(buff);
    return 0;
}

int lu_engfuncs::l_pfnServerExecute(lua_State *L)
{
    SERVER_EXECUTE();
    return 0;
}

int lu_engfuncs::l_pfnClientCommand(lua_State *L) {
    CLIENT_COMMAND((edict_t*) lua_touserdata(L, 1), "%s\n", luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnMessageBegin(lua_State *L) {
    //luaL_checktable(L, 3); // Origin
    std::vector<float> origin;

    lua_pushnil(L);
    while (lua_next(L, 3)) {
        lua_pushvalue(L, -1);
        origin.push_back(luaL_checknumber(L, -1));
        lua_pop(L, 2);
    }

    MESSAGE_BEGIN(
            luaL_checkinteger(L, 1), // DEST
            luaL_checkinteger(L, 2), // TYPE
            origin.data(), // ORIGIN
            (edict_t*) lua_touserdata(L, 4) // PLAYER
            );

    return 0;
}

int lu_engfuncs::l_pfnMessageEnd(lua_State *L) {
    MESSAGE_END();
    return 0;
}

int lu_engfuncs::l_pfnWriteByte(lua_State *L) {
    WRITE_BYTE(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteChar(lua_State *L) {
    WRITE_CHAR(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteShort(lua_State *L) {
    WRITE_SHORT(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteLong(lua_State *L) {
    WRITE_LONG(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteAngle(lua_State *L) {
    WRITE_ANGLE(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteCoord(lua_State *L) {
    WRITE_COORD(luaL_checknumber(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteString(lua_State *L) {
    WRITE_STRING(luaL_checkstring(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnWriteEntity(lua_State *L) {
    WRITE_ENTITY(luaL_checkinteger(L, 1));
    return 0;
}

int lu_engfuncs::l_pfnRegister_Cvar(lua_State *L) {
    cvar_t cvar_lua_mod = {luaL_checkstring(L, 1), (char*) luaL_checkstring(L, 2)};
    CVAR_REGISTER(&cvar_lua_mod);
    return 0;
}

int lu_engfuncs::l_pfnCVarGetFloat(lua_State *L) {
    lua_pushnumber(L, CVAR_GET_FLOAT(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarGetString(lua_State *L) {
    lua_pushstring(L, CVAR_GET_STRING(luaL_checkstring(L, 1)));
    return 1;
}

int lu_engfuncs::l_pfnCVarSetFloat(lua_State *L) {
    CVAR_SET_FLOAT(luaL_checkstring(L, 1), luaL_checknumber(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnCVarSetString(lua_State *L) {
    CVAR_SET_STRING(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
    return 0;
}

int lu_engfuncs::l_pfnClientPrintf(lua_State *L) {
    
    PRINT_TYPE ptype;
    
    int i = luaL_checkinteger(L, 2);
    
    if( i < 0 || i > 3) luaL_error(L, "Print type invalid");
    
    switch (i) {
            case 1:
                ptype = print_console;
            case 2:
                ptype = print_center;
            case 3:
                ptype = print_chat;
    }
    
    CLIENT_PRINTF((edict_t*) lua_touserdata(L, 1), ptype, luaL_checkstring(L, 3));
    return 0;
}
