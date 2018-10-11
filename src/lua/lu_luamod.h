#pragma once

#include "CLuaWorker.hpp"
#include <luamod.h>
#include <extdll.h>
#include <meta_api.h>
#include <string>
#include <stdexcept>
#include <utils.h>

#ifdef __linux__
#include <pthread.h>
//#define SECT pthread_mutex_t
//#define lock_init(x) pthread_mutex_init(x, NULL)
//#define lock_free(x) pthread_mutex_destroy(x)
//#define lock_lock(x) pthread_mutex_lock(x)
//#define lock_unlock(x) pthread_mutex_unlock(x)
#else
#include <windows.h>
//#define SECT CRITICAL_SECTION
//#define lock_init(x) InitializeCriticalSection(x)
//#define lock_free(x) DeleteCriticalSection(x)
//#define lock_lock(x) EnterCriticalSection(x)
//#define lock_unlock(x) LeaveCriticalSection(x)
#endif

namespace lu_luamod {
    void init_api(lua_State *L);
    int l_set_task(lua_State *L);
    int l_del_task(lua_State* L);
    int l_load_plugin(lua_State *L);
    //players[]
    int l_get_authid_by_edict(lua_State *L);
};