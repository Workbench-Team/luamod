#pragma once
#include <luamod.h>

namespace lu_engfuncs {
void init_api(lua_State *L);
int l_pfnPrecacheModel(lua_State *L);
int l_pfnPrecacheSound(lua_State *L);
//
int l_pfnFindEntityByString(lua_State *L);
int l_pfnFindEntitiesByString(lua_State *L);
//
int l_pfnRemoveEntity(lua_State *L);
//
int l_pfnServerCommand(lua_State *L);
int l_pfnServerExecute(lua_State *L);
int l_pfnClientCommand(lua_State *L);
//
int l_pfnMessageBegin(lua_State *L);
int l_pfnMessageEnd(lua_State *L);
int l_pfnWriteByte(lua_State *L);
int l_pfnWriteChar(lua_State *L);
int l_pfnWriteShort(lua_State *L);
int l_pfnWriteLong(lua_State *L);
int l_pfnWriteAngle(lua_State *L);
int l_pfnWriteCoord(lua_State *L);
int l_pfnWriteString(lua_State *L);
int l_pfnWriteEntity(lua_State *L);
//
int l_pfnGetInfoKeyBuffer(lua_State *L);
int l_pfnInfoKeyValue(lua_State *L);
int l_pfnSetKeyValue(lua_State *L);
int l_pfnSetClientKeyValue(lua_State *L);
//
int l_pfnGetPlayerUserId(lua_State *L);
//int l_pfnGetPlayerWONId(lua_State *L);
int l_pfnGetPlayerStats(lua_State *L);
int l_pfnGetPlayerAuthId(lua_State *L);
//
int l_pfnRegister_Cvar(lua_State *L);
int l_pfnCVarGetFloat(lua_State *L);
int l_pfnCVarGetString(lua_State *L);
int l_pfnCVarSetFloat(lua_State *L);
int l_pfnCVarSetString(lua_State *L);
//
int l_pfnIndexOfEdict(lua_State *L);
int l_pfnPEntityOfEntIndex(lua_State *L);
//
int l_pfnRegUserMsg(lua_State *L);
//
int l_pfnClientPrintf(lua_State *L);
//
int l_pfnAddServerCommand(lua_State *L);
//
int l_pfnServerPrint(lua_State *L);
//
int l_pfnQueryClientCvarValue2(lua_State *L);
//
#ifdef REHLDS_SUPPORT
// REHLDS
#endif
} // namespace lu_engfuncs
