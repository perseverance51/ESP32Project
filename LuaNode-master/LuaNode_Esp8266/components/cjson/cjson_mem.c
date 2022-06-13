#include "cjson_mem.h"
#include "../lua/lauxlib.h"
//#include <stdio.h>
//#include "c_stdlib.h"

static lua_State *gL;
static const char errfmt[] = "cjson %salloc: out of mem (%d bytes)";

void cjson_mem_setlua (lua_State *L)
{
  gL = L;
}

/*void *cjson_mem_realloc(void *mem, int size)
{
	void *p;
	p = cjson_mem_malloc(size);
	if (p) {
		if (mem != NULL) {
			memcpy(p, mem, size);
			vPortFree(mem);
		}
	}
	return p;
}*/