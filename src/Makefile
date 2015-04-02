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
LINK_exe = gcc -o $@ $^ $(LDFLAGS) $(LDLIBS) -mwindows
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

all.targets : libhttp_target

clean :
ifeq "$(shell uname)" "Linux"
	$(DELETE) $(subst \,/,$(clean.OBJ))
else
	$(DELETE) $(subst /,\,$(clean.OBJ))
endif

.PHONY: all clean distclean

# -----------------------------------------
# libhttp_target

libhttp_target.DLL = ./bin/libhttp$(d)
libhttp_target.OBJ = hash.o header_field.o header_field_list.o mempool.o request_header.o scanner.o
clean.OBJ += $(libhttp_target.DLL) 
clean.OBJ += $(libhttp_target.OBJ)

libhttp_target : libhttp_target.before $(libhttp_target.BIN) libhttp_target.after_always
libhttp_target : CFLAGS += -std=c99

ifeq "$(shell uname)" "Linux"
libhttp_target : INCLUDES += -I. -I../../include -I../../include/asio -I./include
libhttp_target : RCFLAGS += 
libhttp_target : LDFLAGS += -L/usr/lib/ -L/usr/local/lib -L/usr/lib64/ -L/usr/local/lib64/ -L/usr/lib/mysql -L/usr/local/lib/mysql/ -L/usr/lib64/mysql -L/usr/local/lib64/mysql/
libhttp_target : T_LDLIBS =  
else
libhttp_target : INCLUDES += 
libhttp_target : RCFLAGS +=
libhttp_target : LDFLAGS += 
libhttp_target : T_LDLIBS = 
endif

ifdef LMAKE
libhttp_target : CFLAGS -= -O1 -O2 -g -pipe
endif

libhttp_target.before :


libhttp_target.after_always : $(libhttp_target.DLL)

$(libhttp_target.DLL) : $(libhttp_target.OBJ)
	$(call MKDIR,$(dir $@))
	$(LINK_dll)
ifeq "$(shell uname)" "Linux"
	cp -rf $(libhttp_target.DLL) $(COPY_LIB_DIR)
else
	copy $(subst /,\,$(libhttp_target.DLL)) $(subst /,\,$(COPY_LIB_DIR))
endif