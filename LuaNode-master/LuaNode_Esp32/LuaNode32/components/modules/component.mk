COMPONENT_ADD_INCLUDEDIRS := include

CFLAGS += -DdefaultThreadStack=1024 -DLUA_OPTIMIZE_MEMORY=2 -DMIN_OPT_LEVEL=2 -Wno-error=pointer-sign

