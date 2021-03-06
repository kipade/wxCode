# =========================================================================
#     This makefile was generated by
#     Bakefile 0.1.9 (http://bakefile.sourceforge.net)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C compiler 
CC = wcc386

# Standard flags for CC 
CFLAGS = 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS = 

# Standard linker flags 
LDFLAGS = 

# The LUA library main folder 
LUADIR = c:\lua



# -------------------------------------------------------------------------
# Do not modify the rest of this file!
# -------------------------------------------------------------------------

# Speed up compilation a bit:
!ifdef __LOADDLL__
!  loaddll wcc      wccd
!  loaddll wccaxp   wccdaxp
!  loaddll wcc386   wccd386
!  loaddll wpp      wppdi86
!  loaddll wppaxp   wppdaxp
!  loaddll wpp386   wppd386
!  loaddll wlink    wlink
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###


### Variables: ###

TOLUA_CFLAGS = -i=..\include -i=..\src\lib -i=..\src\bin -i=$(LUADIR)\include &
	$(CPPFLAGS) $(CFLAGS)
TOLUA_OBJECTS =  &
	..\lib\tolua_tolua_event.obj &
	..\lib\tolua_tolua_is.obj &
	..\lib\tolua_tolua_map.obj &
	..\lib\tolua_tolua_push.obj &
	..\lib\tolua_tolua_to.obj
TOLUAEXE_CFLAGS = -i=..\include -i=..\src\lib -i=..\src\bin &
	-i=$(LUADIR)\include $(CPPFLAGS) $(CFLAGS)
TOLUAEXE_OBJECTS =  &
	..\lib\toluaexe_tolua.obj &
	..\lib\toluaexe_toluabind.obj


all : ..\lib
..\lib :
	-if not exist ..\lib mkdir ..\lib

### Targets: ###

all : .SYMBOLIC ..\lib\tolua.lib ..\lib\toluaexe.exe

clean : .SYMBOLIC 
	-if exist ..\lib\*.obj del ..\lib\*.obj
	-if exist ..\lib\*.res del ..\lib\*.res
	-if exist ..\lib\*.lbc del ..\lib\*.lbc
	-if exist ..\lib\*.ilk del ..\lib\*.ilk
	-if exist ..\lib\*.pch del ..\lib\*.pch
	-if exist ..\lib\tolua.lib del ..\lib\tolua.lib
	-if exist ..\lib\toluaexe.exe del ..\lib\toluaexe.exe

..\lib\tolua.lib :  $(TOLUA_OBJECTS)
	@%create ..\lib\tolua.lbc
	@for %i in ($(TOLUA_OBJECTS)) do @%append ..\lib\tolua.lbc +%i
	wlib -q -p4096 -n -b $^@ @..\lib\tolua.lbc

..\lib\toluaexe.exe :  $(TOLUAEXE_OBJECTS) ..\lib\tolua.lib
	@%create ..\lib\toluaexe.lbc
	@%append ..\lib\toluaexe.lbc option quiet
	@%append ..\lib\toluaexe.lbc name $^@
	@%append ..\lib\toluaexe.lbc option caseexact
	@%append ..\lib\toluaexe.lbc $(LDFLAGS) libpath $(LUADIR)\lib
	@for %i in ($(TOLUAEXE_OBJECTS)) do @%append ..\lib\toluaexe.lbc file %i
	@for %i in ( ..\lib\tolua.lib lua.lib lualib.lib) do @%append ..\lib\toluaexe.lbc library %i
	@%append ..\lib\toluaexe.lbc
	wlink @..\lib\toluaexe.lbc
	move ..\lib\*.exe ..

..\lib\tolua_tolua_event.obj :  .AUTODEPEND .\..\src\lib\tolua_event.c
	$(CC) -zq -fo=$^@ $(TOLUA_CFLAGS) $<

..\lib\tolua_tolua_is.obj :  .AUTODEPEND .\..\src\lib\tolua_is.c
	$(CC) -zq -fo=$^@ $(TOLUA_CFLAGS) $<

..\lib\tolua_tolua_map.obj :  .AUTODEPEND .\..\src\lib\tolua_map.c
	$(CC) -zq -fo=$^@ $(TOLUA_CFLAGS) $<

..\lib\tolua_tolua_push.obj :  .AUTODEPEND .\..\src\lib\tolua_push.c
	$(CC) -zq -fo=$^@ $(TOLUA_CFLAGS) $<

..\lib\tolua_tolua_to.obj :  .AUTODEPEND .\..\src\lib\tolua_to.c
	$(CC) -zq -fo=$^@ $(TOLUA_CFLAGS) $<

..\lib\toluaexe_tolua.obj :  .AUTODEPEND .\..\src\bin\tolua.c
	$(CC) -zq -fo=$^@ $(TOLUAEXE_CFLAGS) $<

..\lib\toluaexe_toluabind.obj :  .AUTODEPEND .\..\src\bin\toluabind.c
	$(CC) -zq -fo=$^@ $(TOLUAEXE_CFLAGS) $<

