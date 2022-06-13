#############################################################
# Required variables for each makefile
# Discard this section from all parent makefiles
# Expected variables (with automatic defaults):
#   CSRCS (all "C" files in the dir)
#   SUBDIRS (all subdirs with a Makefile)
#   GEN_LIBS - list of libs to be generated ()
#   GEN_IMAGES - list of object file images to be generated ()
#   GEN_BINS - list of binaries to be generated ()
#   COMPONENTS_xxx - a list of libs/objs in the form
#     subdir/lib to be extracted and rolled up into
#     a generated lib/image xxx.a ()
#
TARGET = eagle
#FLAVOR = release
FLAVOR = debug

#EXTRA_CCFLAGS += -u

ifndef APP_NAME
    $(error "Set the APP_NAME environment variable in your Makefile before including this Makefile")
endif


ifndef PDIR # {
GEN_IMAGES= eagle.app.v6.out
GEN_BINS= eagle.app.v6.bin
SPECIAL_MKTARGETS=$(APP_MKTARGETS)
SUBDIRS=    \
    modules	\
    apps/$(APP_NAME)    \
    driver	\
    spiffs	\
    platform	\
    mylibc	\
    cjson	\
    lua	\
    lpeg	\
    utils

endif # } PDIR

LDDIR = $(SDK_PATH)/ld

CCFLAGS += -Os

TARGET_LDFLAGS =		\
	-nostdlib		\
	-Wl,-EL \
	--longcalls \
	--text-section-literals

ifeq ($(FLAVOR),debug)
    TARGET_LDFLAGS += -g -Os
endif

ifeq ($(FLAVOR),release)
    TARGET_LDFLAGS += -g -O0
endif

COMPONENTS_eagle.app.v6 = \
	modules/libmodules.a	\
    apps/$(APP_NAME)/lib$(APP_NAME).a          \
    driver/libdriver.a	\
    spiffs/libspiffs.a	\
    platform/libplatform.a	\
    mylibc/libmylibc.a	\
    cjson/libcjson.a	\
    lua/liblua.a	\
    lpeg/liblpeg.a	\
    utils/libutils.a

SELECTED_MODULE_SYMS=$(filter %_module_selected %module_selected1,$(shell $(NM) modules/.output/$(TARGET)/$(FLAVOR)/lib/libmodules.a))

LINKFLAGS_eagle.app.v6 = \
	-L$(SDK_PATH)/lib        \
	-L$(SDK_PATH)libc/xtensa-lx106-elf/lib	\
	-Wl,--gc-sections   \
	-nostdlib	\
    -T$(LD_FILE)   \
	-Wl,--no-check-sections	\
    -u call_user_start	\
	-Wl,-static						\
	$(addprefix -u , $(SELECTED_MODULE_SYMS)) \
	-Wl,--start-group					\
	-lminic \
	-lc	\
	-lgcc					\
	-lhal					\
	-lphy	\
	-lpp	\
	-lnet80211	\
	-lwpa	\
	-lcrypto    \
	-lmain	\
	-lfreertos	\
	-llwip	\
	$(DEP_LIBS_eagle.app.v6)					\
	-Wl,--end-group

DEPENDS_eagle.app.v6 = \
                $(LD_FILE) \
                $(LDDIR)/eagle.rom.addr.v6.ld

#############################################################
# Configuration i.e. compile options etc.
# Target specific stuff (defines etc.) goes in here!
# Generally values applying to a tree are captured in the
#   makefile at its root level - these are then overridden
#   for a subtree within the makefile rooted therein
#

#UNIVERSAL_TARGET_DEFINES =		\

# Other potential configuration flags include:
#	-DTXRX_TXBUF_DEBUG
#	-DTXRX_RXBUF_DEBUG
#	-DWLAN_CONFIG_CCX
CONFIGURATION_DEFINES =	-DICACHE_FLASH	\
	-DLUA_OPTIMIZE_MEMORY=2	\
	-DMIN_OPT_LEVEL=2

DEFINES +=				\
	$(UNIVERSAL_TARGET_DEFINES)	\
	$(CONFIGURATION_DEFINES)

DDEFINES +=				\
	$(UNIVERSAL_TARGET_DEFINES)	\
	$(CONFIGURATION_DEFINES)


#############################################################
# Recursion Magic - Don't touch this!!
#
# Each subtree potentially has an include directory
#   corresponding to the common APIs applicable to modules
#   rooted at that subtree. Accordingly, the INCLUDE PATH
#   of a module can only contain the include directories up
#   its parent path, and not its siblings
#
# Required for each makefile to inherit from the parent
#

INCLUDES := $(INCLUDES) -I $(PDIR)include
sinclude $(SDK_PATH)/Makefile

.PHONY: FORCE
FORCE:

