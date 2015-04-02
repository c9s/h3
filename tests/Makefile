# -*- mode: Makefile; -*-
# -----------------------------------------
# project liboci

COPY_LIB_DIR = ../lib/
COPY_INC_DIR = ../include/

# -----------------------------------------------------------
ifeq "$(shell uname)" "Linux"
# -----------------------------------------------------------
e =
a = .a
d = .so
l = ./

CP = cp
LINK_exe = gcc -g -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_con = ar -vrus $@ $^
LINK_dll = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS) -static -static-libstdc++
LINK_lib = rm -f $@ && ar rcs $@ $^
COMPILE_c = gcc $(CFLAGS_C) -o $@ -c $< -I$(INCLUDES)
COMPILE_cpp = g++ $(CFLAGS) -o $@ -c $< -I$(INCLUDES)
COMPILE_rc =
MKDIR = mkdir -p $1
CREATE_DEF = 
CREATE_LIB = 
DELETE = rm -fv 

# -----------------------------------------------------------
else
# -----------------------------------------------------------
# Windows

SHELL = cmd
e = .exe
a = .lib
d = .dll
l =

CP = copy
LINK_exe = gcc -g -gstabs -o $@ $^ $(LDFLAGS) $(LDLIBS) -mwindows
LINK_con = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS)
LINK_dll = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS) -mwindows -shared
LINK_lib = rm -f $@ && ar rcs $@ $^
COMPILE_c = gcc $(CFLAGS_C) -o $@ -c $< -I$(INCLUDES)
COMPILE_cpp = g++ $(CFLAGS) -o $@ -c $< -I$(INCLUDES)
COMPILE_rc = windres $(RCFLAGS) -J rc -O coff -i $< -o $@ -I$(dir $<)
MKDIR = if not exist $(subst /,\,$1) mkdir $(subst /,\,$1)
CREATE_DEF = 
CREATE_LIB = -Wl,--out-implib,$(dir $@)$(notdir $(basename $@)).a
DELETE = del

endif

CFLAGS_C = $(CFLAGS)
CFLAGS = -fPIC -Wall -fexceptions -g -gstabs
INCLUDES = ../include
LDFLAGS = 
RCFLAGS = 
LDLIBS = $(T_LDLIBS)

%.o : %.c ; $(COMPILE_c)
%.o : %.cc ; $(COMPILE_cpp)
%.o : %.cpp ; $(COMPILE_cpp)
%.o : %.cxx ; $(COMPILE_cpp)
%.o : %.rc ; $(COMPILE_rc)
.SUFFIXES: .o .d .c .cc .cpp .cxx .rc

all: all.before all.targets all.after

all.before :
	-
all.after : $(FIRST_TARGET)

all.targets : test_target

clean :
ifeq "$(shell uname)" "Linux"
	$(DELETE) $(subst \,/,$(clean.OBJ))
else
	$(DELETE) $(subst /,\,$(clean.OBJ))
endif

.PHONY: all clean distclean

# -----------------------------------------
# test_target

test_target.BIN = ./bin/test$(e)
test_target.OBJ = parser.o
clean.OBJ += $(test_target.BIN) 
clean.OBJ += $(test_target.OBJ)

test_target : test_target.before $(test_target.BIN) test_target.after_always
test_target : CFLAGS += -std=c99

ifeq "$(shell uname)" "Linux"
test_target : INCLUDES += -I. -I../../include -I../../include/asio -I./include
test_target : RCFLAGS += 
test_target : LDFLAGS += -L/usr/lib/ -L/usr/local/lib -L/usr/lib64/ -L/usr/local/lib64/ -L/usr/lib/mysql -L/usr/local/lib/mysql/ -L/usr/lib64/mysql -L/usr/local/lib64/mysql/
test_target : T_LDLIBS =  
else
test_target : INCLUDES += -I. -I../include
test_target : RCFLAGS +=
test_target : LDFLAGS += -L../lib
test_target : T_LDLIBS = ../lib/libhttp.dll 
endif

ifdef LMAKE
test_target : CFLAGS -= -O1 -O2 -g -pipe
endif

test_target.before :


test_target.after_always : $(test_target.BIN)

$(test_target.BIN) : $(test_target.OBJ)
	$(call MKDIR,$(dir $@))
	$(LINK_exe)
ifeq "$(shell uname)" "Linux"
	cp -rf $(test_target.BIN) $(COPY_LIB_DIR)
else
	copy $(subst /,\,$(test_target.BIN)) $(subst /,\,$(COPY_LIB_DIR))
endif