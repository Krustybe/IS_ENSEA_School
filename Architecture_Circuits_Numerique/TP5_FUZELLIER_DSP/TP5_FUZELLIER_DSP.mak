# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     TP5_FUZELLIER_DSP_Debug
#     TP5_FUZELLIER_DSP_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 4.5


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "TP5_FUZELLIER_DSP_Debug" configuration
#

ifeq ($(MAKECMDGOALS),TP5_FUZELLIER_DSP_Debug)

TP5_FUZELLIER_DSP_Debug : ./Debug/TP5_FUZELLIER_DSP.dxe 

Debug/init1835viaSPI.doj :init1835viaSPI.c $(VDSP)/212xx/include/cdef21262.h $(VDSP)/212xx/include/Cdef21266.h $(VDSP)/212xx/include/def21262.h $(VDSP)/212xx/include/def21266.h $(VDSP)/212xx/include/signal.h ad1835.h 
	@echo ".\init1835viaSPI.c"
	$(VDSP)/cc21k.exe -c .\init1835viaSPI.c -file-attr ProjectName=TP5_FUZELLIER_DSP -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.1 -proc ADSP-21262 -o .\Debug\init1835viaSPI.doj -MM

Debug/initDAI.doj :initDAI.c $(VDSP)/212xx/include/SRU.h $(VDSP)/212xx/include/sru21262.h $(VDSP)/212xx/include/sru21266.h $(VDSP)/212xx/include/def21266.h 
	@echo ".\initDAI.c"
	$(VDSP)/cc21k.exe -c .\initDAI.c -file-attr ProjectName=TP5_FUZELLIER_DSP -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.1 -proc ADSP-21262 -o .\Debug\initDAI.doj -MM

Debug/initSPORT.doj :initSPORT.c $(VDSP)/212xx/include/cdef21262.h $(VDSP)/212xx/include/Cdef21266.h $(VDSP)/212xx/include/def21262.h $(VDSP)/212xx/include/def21266.h $(VDSP)/212xx/include/signal.h 
	@echo ".\initSPORT.c"
	$(VDSP)/cc21k.exe -c .\initSPORT.c -file-attr ProjectName=TP5_FUZELLIER_DSP -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.1 -proc ADSP-21262 -o .\Debug\initSPORT.doj -MM

Debug/main.doj :main.c $(VDSP)/212xx/include/cdef21262.h $(VDSP)/212xx/include/Cdef21266.h $(VDSP)/212xx/include/def21262.h $(VDSP)/212xx/include/def21266.h $(VDSP)/212xx/include/21262.h $(VDSP)/212xx/include/platform_include.h $(VDSP)/212xx/include/signal.h $(VDSP)/212xx/include/sru.h $(VDSP)/212xx/include/sru21262.h $(VDSP)/212xx/include/sru21266.h $(VDSP)/212xx/include/stdlib.h 
	@echo ".\main.c"
	$(VDSP)/cc21k.exe -c .\main.c -file-attr ProjectName=TP5_FUZELLIER_DSP -g -structs-do-not-overlap -no-multiline -double-size-32 -warn-protos -si-revision 0.1 -proc ADSP-21262 -o .\Debug\main.doj -MM

./Debug/TP5_FUZELLIER_DSP.dxe :ADSP-21262.LDF $(VDSP)/212xx/lib/2126x_rev_0.0/262_hdr.doj ./Debug/init1835viaSPI.doj ./Debug/initDAI.doj ./Debug/initSPORT.doj ./Debug/main.doj $(VDSP)/212xx/lib/2126x_rev_0.0/libc26x.dlb $(VDSP)/212xx/lib/2126x_rev_0.0/libio.dlb $(VDSP)/212xx/lib/2126x_rev_0.0/libdsp26x.dlb $(VDSP)/212xx/lib/2126x_rev_0.0/libcpp.dlb $(VDSP)/212xx/lib/2126x_rev_0.0/libeh.dlb $(VDSP)/212xx/lib/2126x_rev_0.0/libcpprt.dlb 
	@echo "Linking..."
	$(VDSP)/cc21k.exe .\Debug\init1835viaSPI.doj .\Debug\initDAI.doj .\Debug\initSPORT.doj .\Debug\main.doj -T .\ADSP-21262.LDF -L .\Debug -flags-link -od,.\Debug -o .\Debug\TP5_FUZELLIER_DSP.dxe -proc ADSP-21262 -si-revision 0.1 -flags-link -MM

endif

ifeq ($(MAKECMDGOALS),TP5_FUZELLIER_DSP_Debug_clean)

TP5_FUZELLIER_DSP_Debug_clean:
	-$(RM) "Debug\init1835viaSPI.doj"
	-$(RM) "Debug\initDAI.doj"
	-$(RM) "Debug\initSPORT.doj"
	-$(RM) "Debug\main.doj"
	-$(RM) ".\Debug\TP5_FUZELLIER_DSP.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\*.rbld"

endif


