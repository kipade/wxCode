# =========================================================================
#     This makefile was generated by
#     Bakefile 0.2.4 (http://www.bakefile.org)
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

# Use Unicode build of wxWidgets? [0,1]
#   0 - ANSI
#   1 - Unicode
WX_UNICODE = 0

# Use debug build of wxWidgets (define __WXDEBUG__)? [0,1]
#   0 - Release
#   1 - Debug
WX_DEBUG = 1

# Version of the wx library to build against. 
WX_VERSION = 28

# Use monolithic build of wxWidgets? [0,1]
#   0 - Multilib
#   1 - Monolithic
WX_MONOLITHIC = 0

# The directory where wxWidgets library is installed 
WX_DIR = $(%WXWIN)

# Build this wxCode component as DLL or as static library? [0,1]
#   0 - Static
#   1 - DLL
SHARED = 0

# If 1 then wxCURL component will be used for proxy/authentication stuff [1,0]
USE_CURL = 1

# The path to the wxHTTPBuilder (CURL) component 
CURL_DIR = ..\..\wxcurl



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

WX3RDPARTYLIBPOSTFIX =
!ifeq WX_DEBUG 1
WX3RDPARTYLIBPOSTFIX = d
!endif
_BUILDDIR_SHARED_SUFFIX =
!ifeq SHARED 0
_BUILDDIR_SHARED_SUFFIX = 
!endif
!ifeq SHARED 1
_BUILDDIR_SHARED_SUFFIX = _dll
!endif
__webupdate_lib___depname =
!ifeq WX_SHARED 0
__webupdate_lib___depname = &
	..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib
!endif
__webupdate_dll___depname =
!ifeq WX_SHARED 1
__webupdate_dll___depname = &
	..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.dll
!endif
____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES =
!ifeq SHARED 0
____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES = lib
!endif
!ifeq SHARED 1
____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES = dll
!endif
____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES =
!ifeq WX_SHARED 0
____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES = lib
!endif
!ifeq WX_SHARED 1
____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES = dll
!endif
__MYOPTIMIZEFLAG =
!ifeq WX_DEBUG 0
__MYOPTIMIZEFLAG = -os
!endif
!ifeq WX_DEBUG 1
__MYOPTIMIZEFLAG = -od
!endif
__CURLDEP_LIB_p =
!ifeq USE_CURL 1
__CURLDEP_LIB_p = wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_wxcurl.lib
!endif
__WXLIB_HTML_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_HTML_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_html.lib
!endif
__WXLIB_XRC_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_XRC_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_xrc.lib
!endif
__WXLIB_XML_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_XML_NAME_p = wxbase$(WX_VERSION)$(WXLIBPOSTFIX)_xml.lib
!endif
__WXLIB_NET_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_NET_NAME_p = wxbase$(WX_VERSION)$(WXLIBPOSTFIX)_net.lib
!endif
__CURLDEP_DEF_p =
!ifeq USE_CURL 0
__CURLDEP_DEF_p = -dwxUSE_CURL=0
!endif
!ifeq USE_CURL 1
__CURLDEP_DEF_p = -dwxUSE_CURL=1
!endif
__WXLIB_ADV_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_ADV_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_adv.lib
!endif
____WX_SHARED =
!ifeq WX_SHARED 0
____WX_SHARED = 
!endif
!ifeq WX_SHARED 1
____WX_SHARED = -dWXUSINGDLL
!endif
__WXUNICODE_DEFINE_p =
!ifeq WX_UNICODE 1
__WXUNICODE_DEFINE_p = -d_UNICODE
!endif
__WXDEBUG_DEFINE_p =
!ifeq WX_DEBUG 1
__WXDEBUG_DEFINE_p = -d__WXDEBUG__
!endif
WXLIBPOSTFIX =
!ifeq WX_DEBUG 0
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = u
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 0
WXLIBPOSTFIX = d
!endif
!endif
!ifeq WX_DEBUG 1
!ifeq WX_UNICODE 1
WXLIBPOSTFIX = ud
!endif
!endif
VAR_4 =
!ifeq WX_DEBUG 0
VAR_4 = -ot -ox
!endif
!ifeq WX_DEBUG 1
VAR_4 = -od
!endif
VAR =
!ifeq WX_DEBUG 0
VAR = -d0
!endif
!ifeq WX_DEBUG 1
VAR = -d2
!endif
VAR_5 =
!ifeq WX_DEBUG 0
VAR_5 = 
!endif
!ifeq WX_DEBUG 1
VAR_5 = debug all
!endif
__WXLIB_CORE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_CORE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX)_core.lib
!endif
__WXLIB_BASE_NAME_p =
!ifeq WX_MONOLITHIC 0
__WXLIB_BASE_NAME_p = wxbase$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
!ifeq WX_MONOLITHIC 1
__WXLIB_BASE_NAME_p = wxmsw$(WX_VERSION)$(WXLIBPOSTFIX).lib
!endif
WXLIBPATH =
!ifeq WX_SHARED 0
WXLIBPATH = \lib\wat_lib
!endif
!ifeq WX_SHARED 1
WXLIBPATH = \lib\wat_dll
!endif

### Variables: ###

WEBUPDATE_LIB_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR) -wx &
	-i=..\include -i=$(CURL_DIR)\include $(__CURLDEP_DEF_p) $(__MYOPTIMIZEFLAG) &
	$(CPPFLAGS) $(CXXFLAGS)
WEBUPDATE_LIB_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_checkedlistctrl.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_download.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_installer.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_md5.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_stdactions.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_versionrange.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_webupdate.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_webupdatectrl.obj
WEBUPDATE_DLL_CXXFLAGS = -bd $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR) -wx &
	-i=..\include -dWXMAKINGDLL_WEBUPDATE -i=$(CURL_DIR)\include &
	$(__CURLDEP_DEF_p) $(__MYOPTIMIZEFLAG) $(CPPFLAGS) $(CXXFLAGS)
WEBUPDATE_DLL_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_checkedlistctrl.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_download.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_installer.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_md5.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_stdactions.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_versionrange.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_webupdate.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_webupdatectrl.obj
WEBUPDATER_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR) -wx &
	-i=..\include -i=$(CURL_DIR)\include $(__CURLDEP_DEF_p) $(__MYOPTIMIZEFLAG) &
	$(CPPFLAGS) $(CXXFLAGS)
WEBUPDATER_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_webapp.obj &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_webupdatedlg.obj
SIMPLE_1_0_0_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR_4) &
	$(VAR) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
SIMPLE_1_0_0_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0_minimal.obj
SIMPLE_2_0_3_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR_4) &
	$(VAR) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
SIMPLE_2_0_3_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3_minimal.obj
ADVANCED_0_0_1_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR_4) &
	$(VAR) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
ADVANCED_0_0_1_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1_minimal.obj
ADVANCED_1_5_0_CXXFLAGS = $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) &
	$(__WXDEBUG_DEFINE_p) -d__WXMSW__ &
	-i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include $(VAR_4) &
	$(VAR) -wx -i=..\include $(CPPFLAGS) $(CXXFLAGS)
ADVANCED_1_5_0_OBJECTS =  &
	watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0_minimal.obj


all : watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)
watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) :
	-if not exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX) mkdir watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)

### Targets: ###

all : .SYMBOLIC test_for_selected_wxbuild $(__webupdate_lib___depname) $(__webupdate_dll___depname) ..\app\webupdater.exe rep4_simple100 rep4_simple203 rep4_adv001 rep4_adv150 po_simple100 po_simple203 po_adv001 po_adv150 ..\samples\simple\v1.0.0\simple.exe ..\samples\simple\v2.0.3\simple.exe ..\samples\advanced\v0.0.1\advanced.exe ..\samples\advanced\v1.5.0\advanced.exe

clean : .SYMBOLIC 
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.obj
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.res
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.lbc
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.ilk
	-if exist watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch del watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\*.pch
	-if exist ..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib del ..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib
	-if exist ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.dll del ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.dll
	-if exist ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib del ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib
	-if exist ..\app\webupdater.exe del ..\app\webupdater.exe
	-if exist webupdater.exe del webupdater.exe
	-if exist webupdatedlg.xrc del webupdatedlg.xrc
	-if exist webupdater.exe del webupdater.exe
	-if exist webupdatedlg.xrc del webupdatedlg.xrc
	-if exist webupdater.exe del webupdater.exe
	-if exist webupdatedlg.xrc del webupdatedlg.xrc
	-if exist webupdater.exe del webupdater.exe
	-if exist webupdatedlg.xrc del webupdatedlg.xrc
	-if exist ..\samples\simple\v1.0.0\simple.exe del ..\samples\simple\v1.0.0\simple.exe
	-if exist ..\samples\simple\v2.0.3\simple.exe del ..\samples\simple\v2.0.3\simple.exe
	-if exist ..\samples\advanced\v0.0.1\advanced.exe del ..\samples\advanced\v0.0.1\advanced.exe
	-if exist ..\samples\advanced\v1.5.0\advanced.exe del ..\samples\advanced\v1.5.0\advanced.exe

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
..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib :  make_dir_webupdate_lib  $(WEBUPDATE_LIB_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib.lbc
	@for %i in ($(WEBUPDATE_LIB_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib.lbc +%i
	wlib -q -p4096 -n -b $^@ @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib.lbc
!endif

make_dir_webupdate_lib :  
	if not exist ..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES) mkdir ..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)

!ifeq WX_SHARED 1
..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.dll :  make_dir_webupdate_dll  $(WEBUPDATE_DLL_OBJECTS)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) libpath $(CURL_DIR)\lib $(LDFLAGS)
	@for %i in ($(WEBUPDATE_DLL_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc file %i
	@for %i in ( $(__CURLDEP_LIB_p) $(__WXLIB_ADV_NAME_p) $(__WXLIB_HTML_NAME_p) $(__WXLIB_ADV_NAME_p) $(__WXLIB_XRC_NAME_p) $(__WXLIB_XML_NAME_p) $(__WXLIB_NET_NAME_p) $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc system nt_dll
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll.lbc
	wlib -q -n -b ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib +$^@
!endif

make_dir_webupdate_dll :  
	if not exist ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES) mkdir ..\lib\wat_$(____webupdate_dll__DIRNAME_SHARED_SUFFIX_FILENAMES)

i18n :  
	wxrc ../src/webupdatedlg.xrc -g -c -o ../src/webupdatedlg.xrc.extracted
	rm -f locale/webupdater.pot
	touch locale/webupdater.pot
	find ../include -name "*.h" | xargs xgettext --c++ -k_ -kwxPLURAL:1,2 -kwxTRANSLATE -s -j -o locale/webupdater.pot
	find ../src -name "*.cpp" | xargs xgettext --c++ -k_ -kwxPLURAL:1,2 -kwxTRANSLATE -s -j -o locale/webupdater.pot
	find ../src -name "*.xrc.extracted" | xargs xgettext --c++ -k_ -kwxPLURAL:1,2 -kwxTRANSLATE -s -j -o locale/webupdater.pot
	msgmerge locale/it.po locale/webupdater.pot > locale/it.po.new && mv locale/it.po.new locale/it.po
	msgfmt --statistics -o locale/it.mo locale/it.po
	msgmerge locale/de.po locale/webupdater.pot > locale/de.po.new && mv locale/de.po.new locale/de.po
	msgfmt --statistics -o locale/de.mo locale/de.po

..\app\webupdater.exe :  $(WEBUPDATER_OBJECTS) watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_app.res $(__webupdate_lib___depname)
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) libpath $(CURL_DIR)\lib system nt_win ref '_WinMain@16' $(LDFLAGS)
	@for %i in ($(WEBUPDATER_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc file %i
	@for %i in ( ..\lib\wat_$(____webupdate_lib__DIRNAME_SHARED_SUFFIX_FILENAMES)\wxcode_msw$(WX_VERSION)$(WXLIBPOSTFIX)_webupdate.lib $(__CURLDEP_LIB_p) $(__WXLIB_ADV_NAME_p) $(__WXLIB_HTML_NAME_p) $(__WXLIB_ADV_NAME_p) $(__WXLIB_XRC_NAME_p) $(__WXLIB_XML_NAME_p) $(__WXLIB_NET_NAME_p) $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc option resource=watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_app.res
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater.lbc

rep4_simple100 : .SYMBOLIC 
	if not exist ..\samples\simple\v1.0.0 mkdir ..\samples\simple\v1.0.0
	for %f in (webupdater.exe webupdatedlg.xrc) do copy ..\app\%f ..\samples\simple\v1.0.0

rep4_simple203 : .SYMBOLIC 
	if not exist ..\samples\simple\v2.0.3 mkdir ..\samples\simple\v2.0.3
	for %f in (webupdater.exe webupdatedlg.xrc) do copy ..\app\%f ..\samples\simple\v2.0.3

rep4_adv001 : .SYMBOLIC 
	if not exist ..\samples\advanced\v0.0.1 mkdir ..\samples\advanced\v0.0.1
	for %f in (webupdater.exe webupdatedlg.xrc) do copy ..\app\%f ..\samples\advanced\v0.0.1

rep4_adv150 : .SYMBOLIC 
	if not exist ..\samples\advanced\v1.5.0 mkdir ..\samples\advanced\v1.5.0
	for %f in (webupdater.exe webupdatedlg.xrc) do copy ..\app\%f ..\samples\advanced\v1.5.0

po_simple100 : .SYMBOLIC 
	if not exist ..\samples\simple\v1.0.0\lang mkdir ..\samples\simple\v1.0.0\lang
	for %f in (it.mo de.mo) do if not exist ..\samples\simple\v1.0.0\lang\%f copy ..\locale\%f ..\samples\simple\v1.0.0\lang

po_simple203 : .SYMBOLIC 
	if not exist ..\samples\simple\v2.0.3\lang mkdir ..\samples\simple\v2.0.3\lang
	for %f in (it.mo de.mo) do if not exist ..\samples\simple\v2.0.3\lang\%f copy ..\locale\%f ..\samples\simple\v2.0.3\lang

po_adv001 : .SYMBOLIC 
	if not exist ..\samples\advanced\v0.0.1\lang mkdir ..\samples\advanced\v0.0.1\lang
	for %f in (it.mo de.mo) do if not exist ..\samples\advanced\v0.0.1\lang\%f copy ..\locale\%f ..\samples\advanced\v0.0.1\lang

po_adv150 : .SYMBOLIC 
	if not exist ..\samples\advanced\v1.5.0\lang mkdir ..\samples\advanced\v1.5.0\lang
	for %f in (it.mo de.mo) do if not exist ..\samples\advanced\v1.5.0\lang\%f copy ..\locale\%f ..\samples\advanced\v1.5.0\lang

..\samples\simple\v1.0.0\simple.exe :  $(SIMPLE_1_0_0_OBJECTS) ..\app\webupdater.exe make_sample_dir_simple_1_0_0
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16'  $(LDFLAGS)
	@for %i in ($(SIMPLE_1_0_0_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc file %i
	@for %i in ( $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0.lbc

make_sample_dir_simple_1_0_0 :  
	if not exist ..\samples\simple\v1.0.0 mkdir ..\samples\simple\v1.0.0

..\samples\simple\v2.0.3\simple.exe :  $(SIMPLE_2_0_3_OBJECTS) ..\app\webupdater.exe make_sample_dir_simple_2_0_3
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16'  $(LDFLAGS)
	@for %i in ($(SIMPLE_2_0_3_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc file %i
	@for %i in ( $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3.lbc

make_sample_dir_simple_2_0_3 :  
	if not exist ..\samples\simple\v2.0.3 mkdir ..\samples\simple\v2.0.3

..\samples\advanced\v0.0.1\advanced.exe :  $(ADVANCED_0_0_1_OBJECTS) ..\app\webupdater.exe make_sample_dir_advanced_0_0_1
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16'  $(LDFLAGS)
	@for %i in ($(ADVANCED_0_0_1_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc file %i
	@for %i in ( $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1.lbc

make_sample_dir_advanced_0_0_1 :  
	if not exist ..\samples\advanced\v0.0.1 mkdir ..\samples\advanced\v0.0.1

..\samples\advanced\v1.5.0\advanced.exe :  $(ADVANCED_1_5_0_OBJECTS) ..\app\webupdater.exe make_sample_dir_advanced_1_5_0
	@%create watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc option quiet
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc name $^@
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc option caseexact
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc  libpath $(WX_DIR)$(WXLIBPATH) $(VAR_5) libpath ..$(WXLIBPATH) system nt_win ref '_WinMain@16'  $(LDFLAGS)
	@for %i in ($(ADVANCED_1_5_0_OBJECTS)) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc file %i
	@for %i in ( $(__WXLIB_CORE_NAME_p) $(__WXLIB_BASE_NAME_p) wxtiff$(WX3RDPARTYLIBPOSTFIX).lib wxjpeg$(WX3RDPARTYLIBPOSTFIX).lib wxpng$(WX3RDPARTYLIBPOSTFIX).lib wxzlib$(WX3RDPARTYLIBPOSTFIX).lib wxregex$(WXLIBPOSTFIX).lib wxexpat$(WX3RDPARTYLIBPOSTFIX).lib kernel32.lib user32.lib gdi32.lib comdlg32.lib winspool.lib winmm.lib shell32.lib comctl32.lib ole32.lib oleaut32.lib uuid.lib rpcrt4.lib advapi32.lib wsock32.lib odbc32.lib) do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc library %i
	@%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc
	@for %i in () do @%append watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc option stack=%i
	wlink @watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0.lbc

make_sample_dir_advanced_1_5_0 :  
	if not exist ..\samples\advanced\v1.5.0 mkdir ..\samples\advanced\v1.5.0

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_checkedlistctrl.obj :  .AUTODEPEND ..\src\checkedlistctrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_download.obj :  .AUTODEPEND ..\src\download.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_installer.obj :  .AUTODEPEND ..\src\installer.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_md5.obj :  .AUTODEPEND ..\src\md5.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_stdactions.obj :  .AUTODEPEND ..\src\stdactions.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_versionrange.obj :  .AUTODEPEND ..\src\versionrange.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_webupdate.obj :  .AUTODEPEND ..\src\webupdate.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_lib_webupdatectrl.obj :  .AUTODEPEND ..\src\webupdatectrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_LIB_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_checkedlistctrl.obj :  .AUTODEPEND ..\src\checkedlistctrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_download.obj :  .AUTODEPEND ..\src\download.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_installer.obj :  .AUTODEPEND ..\src\installer.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_md5.obj :  .AUTODEPEND ..\src\md5.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_stdactions.obj :  .AUTODEPEND ..\src\stdactions.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_versionrange.obj :  .AUTODEPEND ..\src\versionrange.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_webupdate.obj :  .AUTODEPEND ..\src\webupdate.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdate_dll_webupdatectrl.obj :  .AUTODEPEND ..\src\webupdatectrl.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATE_DLL_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_webapp.obj :  .AUTODEPEND ..\app\webapp.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATER_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_webupdatedlg.obj :  .AUTODEPEND ..\app\webupdatedlg.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(WEBUPDATER_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\webupdater_app.res :  .AUTODEPEND ..\app\app.rc
	wrc -q -ad -bt=nt -r -fo=$^@  $(____WX_SHARED) $(__WXUNICODE_DEFINE_p) $(__WXDEBUG_DEFINE_p) -d__WXMSW__ -i=$(WX_DIR)$(WXLIBPATH)\msw$(WXLIBPOSTFIX) -i=$(WX_DIR)\include -i=..\include -i=$(CURL_DIR)\include $(__CURLDEP_DEF_p)  -i=..\app $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_1_0_0_minimal.obj :  .AUTODEPEND ..\samples\simple\v1.0.0\minimal.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(SIMPLE_1_0_0_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\simple_2_0_3_minimal.obj :  .AUTODEPEND ..\samples\simple\v2.0.3\minimal.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(SIMPLE_2_0_3_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_0_0_1_minimal.obj :  .AUTODEPEND ..\samples\advanced\v0.0.1\minimal.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(ADVANCED_0_0_1_CXXFLAGS) $<

watmsw$(WXLIBPOSTFIX)$(_BUILDDIR_SHARED_SUFFIX)\advanced_1_5_0_minimal.obj :  .AUTODEPEND ..\samples\advanced\v1.5.0\minimal.cpp
	$(CXX) -bt=nt -zq -fo=$^@ $(ADVANCED_1_5_0_CXXFLAGS) $<
