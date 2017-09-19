/*
** $Id: lfunc.h 157 2005-07-19 17:44:58Z frm $
** Auxiliary functions to manipulate prototypes and closures
** See Copyright Notice in lua.h
*/

#ifndef lfunc_h
#define lfunc_h


#include "lobject.h"


Proto *luaF_newproto (lua_State *L);
Closure *luaF_newCclosure (lua_State *L, int nelems);
Closure *luaF_newLclosure (lua_State *L, int nelems, TObject *e);
UpVal *luaF_findupval (lua_State *L, StkId level);
void luaF_close (lua_State *L, StkId level);
void luaF_freeproto (lua_State *L, Proto *f);
void luaF_freeclosure (lua_State *L, Closure *c);

const char *luaF_getlocalname (const Proto *func, int local_number, int pc);


#endif
