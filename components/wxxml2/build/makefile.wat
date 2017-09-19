# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.8 (http://www.bakefile.org)
#     Do not modify, all changes will be overwritten!
# =========================================================================



# -------------------------------------------------------------------------
# These are configurable options:
# -------------------------------------------------------------------------

# C++ compiler 
CXX = wpp386

# Standard flags for C++ 
CXXFLAGS = 

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS = 

# Standard linker flags 
LDFLAGS = 

# Use DLL build of wx library? [0,1]
#   0 - Static
#   1 - DLL
WX_SHARED = 0

# Use debug build of wxWidgets (linked with debug CRT)? [0,1]
#   0 - Release
#   1 - Debug
WX_DEBUG = 1

# Version of the wx library to build against. 
WX_VERSION = 29

# The directory where wxWidgets library is installed 
WX_DIR = $(%WXWIN)



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
! if $(__VERSION__) >= 1280
!  loaddll wlink    wlinkd
! else
!  loaddll wlink    wlink
! endif
!  loaddll wlib     wlibd
!endif

# We need these variables in some bakefile-made rules:
WATCOM_CWD = $+ $(%cdrive):$(%cwd) $-

### Conditionally set variables: ###

WX3RDPARTYLIBPOSTFIX =
!ifeq WX_DEBUG 1
WX3RDPARTYLIBPOSTFIX = d
!endif
__wxxml2_lib___depname =
!ifeq WX_SHARED 0
__wxxml2_lib___depname = &
	..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib
!endif
__wxxml2_dll___depname =
!ifeq WX_SHARED 1
__wxxml2_dll___depname = &
	..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.dll
!endif
VAR =
!ifeq WX_DEBUG 0
VAR = -ot -ox
!endif
!ifeq WX_DEBUG 1
VAR = -od
!endif
VAR_0 =
!ifeq WX_DEBUG 0
VAR_0 = -d0
!endif
!ifeq WX_DEBUG 1
VAR_0 = -d2
!endif
VAR_1 =
!ifeq WX_DEBUG 0
VAR_1 = 
!endif
!ifeq WX_DEBUG 1
VAR_1 = debug all
!endif
____LIBXML2_DIR_FILENAMES =
!ifeq WX_DEBUG 0
____LIBXML2_DIR_FILENAMES = libpath ..\deps\lib\release
!endif
!ifeq WX_DEBUG 1
____LIBXML2_DIR_FILENAMES = libpath ..\deps\lib\debug
!endif
____WX_SHARED =
!ifeq WX_SHARED 0
____WX_SHARED = 
!endif
!ifeq WX_SHARED 1
____WX_SHARED = -dWXUSINGDLL
!endif
__WXDEBUG_DEFINE_p =
!ifeq WX_DEBUG 1
__WXDEBUG_DEFINE_p = -d__WXDEBUG__
!endif
WXLIBPOSTFIX =
!ifeq WX_DEBUG 0
WXLIBPOSTFIX = u
!endif
!ifeq WX_DEBUG 1
WXLIBPOSTFIX = ud
!endif
WXLIBPATH =
!ifeq WX_SHARED 0
WXLIBPATH = \lib\$(COMPILER_PREFIX)_lib
!endif
!ifeq WX_SHARED 1
WXLIBPATH = \lib\$(COMPILER_PREFIX)_dll
!endif

### Variables: ###

COMPILER_PREFIX = wat
WXXML2_LIB_CXXFLAGS = $(____WX_SHARED) -d_UNICODE $(__WXDEBUG_DEFINE_p) &
	-d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) &
	-i=$(WX_DIR)\include $(VAR) $(VAR_0) -wx -i=..\include -i=..\deps\include &
	$(CPPFLAGS) $(CXXFLAGS)
WXXML2_LIB_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)\wxxml2_lib_dtd.obj &
	watmsw$(WXLIBPOSTFIX)\wxxml2_lib_xml2.obj
WXXML2_DLL_CXXFLAGS = -bd $(____WX_SHARED) -d_UNICODE $(__WXDEBUG_DEFINE_p) &
	-d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) &
	-i=$(WX_DIR)\include $(VAR) $(VAR_0) -wx -i=..\include -dWXMAKINGDLL_WXXML2 &
	-i=..\deps\include $(CPPFLAGS) $(CXXFLAGS)
WXXML2_DLL_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)\wxxml2_dll_dtd.obj &
	watmsw$(WXLIBPOSTFIX)\wxxml2_dll_xml2.obj
MINIMAL_CXXFLAGS = $(____WX_SHARED) -d_UNICODE $(__WXDEBUG_DEFINE_p) &
	-d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) &
	-i=$(WX_DIR)\include $(VAR) $(VAR_0) -wx -i=..\include -i=..\deps\include &
	$(CPPFLAGS) $(CXXFLAGS)
MINIMAL_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)\minimal_minimal.obj


all : watmsw$(WXLIBPOSTFIX)
watmsw$(WXLIBPOSTFIX) :
	-if not exist watmsw$(WXLIBPOSTFIX) mkdir watmsw$(WXLIBPOSTFIX)

### Targets: ###

all : .SYMBOLIC test_for_selected_wxbuild $(__wxxml2_lib___depname) $(__wxxml2_dll___depname) ..\sample\minimal.exe

clean : .SYMBOLIC 
	-if exist watmsw$(WXLIBPOSTFIX)\*.obj del watmsw$(WXLIBPOSTFIX)\*.obj
	-if exist watmsw$(WXLIBPOSTFIX)\*.res del watmsw$(WXLIBPOSTFIX)\*.res
	-if exist watmsw$(WXLIBPOSTFIX)\*.lbc del watmsw$(WXLIBPOSTFIX)\*.lbc
	-if exist watmsw$(WXLIBPOSTFIX)\*.ilk del watmsw$(WXLIBPOSTFIX)\*.ilk
	-if exist watmsw$(WXLIBPOSTFIX)\*.pch del watmsw$(WXLIBPOSTFIX)\*.pch
	-if exist ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib del ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib
	-if exist ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.dll del ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.dll
	-if exist ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib del ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib
	-if exist ..\sample\minimal.exe del ..\sample\minimal.exe

test_for_selected_wxbuild :  
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo The selected wxWidgets build is not available!
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo Please use the options prefixed with WX_ to select another wxWidgets build.
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	echo ----------------------------------------------------------------------------
	@if not exist $(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX)\wx\setup.h \
	exit 1

!ifeq WX_SHARED 0
..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib :  make_dir_wxxml2_lib  $(WXXML2_LIB_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)\wxxml2_lib.lbc
	@for %i in ($(WXXML2_LIB_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)\wxxml2_lib.lbc +%i
	wlib -q -p4096 -n -b $^@ @watmsw$(WXLIBPOSTFIX)\wxxml2_lib.lbc
!endif

make_dir_wxxml2_lib :  
	if not exist ..\lib\wat_lib mkdir ..\lib\wat_lib

!ifeq WX_SHARED 1
..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.dll :  make_dir_wxxml2_dll  $(WXXML2_DLL_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc  libpath $(WX_DIR)$(WXLIBPATH)  $(VAR_1) libpath ..$(WXLIBPATH) $(____LIBXML2_DIR_FILENAMES) $(LDFLAGS)
	@for %i in ($(WXXML2_DLL_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc file %i
	@for %i in ( libxml2.lib iconv.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib) do @%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc system nt_dll
	wlink @watmsw$(WXLIBPOSTFIX)\wxxml2_dll.lbc
	wlib -q -n -b ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib +$^@
!endif

make_dir_wxxml2_dll :  
	if not exist ..\lib\wat_lib mkdir ..\lib\wat_lib

..\sample\minimal.exe :  $(MINIMAL_OBJECTS) make_sample_dir_minimal watmsw$(WXLIBPOSTFIX)\minimal_minimal.res $(__wxxml2_lib___depname)
	@%create watmsw$(WXLIBPOSTFIX)\minimal.lbc
	@%append watmsw$(WXLIBPOSTFIX)\minimal.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)\minimal.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)\minimal.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)\minimal.lbc  libpath $(WX_DIR)$(WXLIBPATH)  $(VAR_1) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16' $(____LIBXML2_DIR_FILENAMES)  $(LDFLAGS)
	@for %i in ($(MINIMAL_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)\minimal.lbc file %i
	@for %i in ( ..\lib\wat_lib\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxxml2.lib libxml2.lib iconv.lib wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib) do @%append watmsw$(WXLIBPOSTFIX)\minimal.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)\minimal.lbc option resource=watmsw$(WXLIBPOSTFIX)\minimal_minimal.res
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)\minimal.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)\minimal.lbc

make_sample_dir_minimal :  
	if not exist ..\sample mkdir ..\sample

tarball :  
	make distclean
	-cd ..\..
	-tar -cvzf wxxml2.tar.gz --exclude="*~" --exclude="*.log" --exclude="*.o*" --exclude="*.a" --exclude=".svn" --exclude="autom4te.cache" wxxml2\*

zip :  clean
	del ..\..\wxxml2.zip
	-cd ..\..
	-zip -r9 wxxml2.zip wxxml2 -x "*.pdb" -x "*.log" -x "*.o*"

watmsw$(WXLIBPOSTFIX)\wxxml2_lib_dtd.obj :  .AUTODEPEND ..\src\dtd.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WXXML2_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)\wxxml2_lib_xml2.obj :  .AUTODEPEND ..\src\xml2.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WXXML2_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)\wxxml2_dll_dtd.obj :  .AUTODEPEND ..\src\dtd.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WXXML2_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)\wxxml2_dll_xml2.obj :  .AUTODEPEND ..\src\xml2.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WXXML2_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)\minimal_minimal.obj :  .AUTODEPEND ..\sample\minimal.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(MINIMAL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)\minimal_minimal.res :  .AUTODEPEND ..\sample\minimal.rc
	wrc -q -ad -bt=nt -r -fo=$^@  $(____WX_SHARED) -d_UNICODE $(__WXDEBUG_DEFINE_p) -d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include -i=..\include -i=..\deps\include -i=..\sample $<

