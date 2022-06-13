#include "module.h"
#include "lauxlib.h"
#include "c_string.h"

static int template_start( lua_State* L ) {
	printf("module template start\n");
	return 0;
}

static int template_stop( lua_State* L ) {
	printf("module template stop\n");
	return 0;
}

// Module function map
static const LUA_REG_TYPE template_map[] = {
	{ LSTRKEY( "start" ), LFUNCVAL( template_start ) },
	{ LSTRKEY( "stop" ), LFUNCVAL( template_stop ) },
	{ LNILKEY, LNILVAL }
};

LUANODE_MODULE(TEMPLATE, "template", template_map, NULL);