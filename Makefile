# -----------------------------------------------------------
ifeq "$(shell uname)" "Linux"
# -----------------------------------------------------------

MKDIR = mkdir -p $1
CD_DIR = cd $1

INSTALL_BIN = ./bin/affair
INSTALL_LIB_DBCP = ./lib/libdbcp.so
INSTALL_LIB_MYLIB = ./lib/libmylib.so
INSTALL_CONFIG = ./conf/config.json
INSTALL_SHELL = ./shell/affair
INSTALL_SHELL_SETUP = ./shell/affair.setup

INSTALL_BIN_DIR = /usr/local/bin/affair
INSTALL_LIB_DBCP_DIR = /usr/local/lib/libdbcp.so
INSTALL_LIB_MYLIB_DIR = /usr/local/lib/libmylib.so
INSTALL_CONFIG_DIR = /usr/local/etc/config.json
INSTALL_SHELL_DIR = /etc/init.d/affair

DIR = $(shell pwd | sed 's,^\(.*/\)\?\([^/]*\),\2,')

# -----------------------------------------------------------
else
# -----------------------------------------------------------
# Windows

MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
CD_DIR = cd $(subst /,\,$1)

INSTALL_BINS = .\bin\*
INSTALL_LIBS = .\lib\*

INSTALL_BIN_DIR = 
INSTALL_LIB_DIR = 

# -----------------------------------------------------------
endif
# -----------------------------------------------------------

all:
	$(call MKDIR, ./bin)
	$(call MKDIR, ./lib)
	$(call CD_DIR, ./src) && make
	$(call CD_DIR, ./tests) && make

clean:
	$(call CD_DIR, ./src) && make clean
	$(call CD_DIR, ./tests) && make clean

cleanall : clean
ifeq "$(shell uname)" "Linux"
	rm -rf ./lib/*
	rm -rf ./bin/*
else
	del /Q .\lib\*
	del /Q .\bin\*
endif

install:
	cp -rf $(INSTALL_BIN) $(INSTALL_BIN_DIR)
	cp -rf $(INSTALL_CONFIG) $(INSTALL_CONFIG_DIR)
	cp -rf $(INSTALL_SHELL) $(INSTALL_SHELL_DIR)
uninstall:
	rm -rf $(INSTALL_BIN_DIR)
	rm -rf $(INSTALL_CONFIG_DIR)
	rm -rf $(INSTALL_SHELL_DIR)
package:
	$(call CD_DIR, ..) &&  tar -zcvpf affair.tar.gz $(DIR)/$(INSTALL_BIN) $(DIR)/$(INSTALL_CONFIG) $(DIR)/$(INSTALL_SHELL) $(DIR)/$(INSTALL_SHELL_SETUP) $(DIR)/README
	mv ../affair.tar.gz .