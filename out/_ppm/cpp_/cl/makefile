####################################
#           Information            #
####################################
#
# Add in PATH : "[...]\Microsoft Visual Studio 12.0\VC\bin\"
# to have access to nmake.exe
#
# To not display the logo, use "nmake /nologo [...]"
#
# Compiler "cl.exe" options :
# https://msdn.microsoft.com/en-us/library/fwkeyyhe.aspx
#
####################################
#            Constants             #
####################################

# x86 / x64
BITS_VERSION = x86
SOURCE_DIR = src
OUTPUT_EXT = exe
OUTPUT_DIR = out
OBJECT_DIR = bin

# https://msdn.microsoft.com/en-US/library/thxezb7y.aspx
WARNING_LEVEL = 0

INC = /D
INCLUDES = 	$(INC) WIN32 \
			$(INC) _DEBUG \
			$(INC) _CONSOLE \
			$(INC) _UNICODE \
			$(INC) UNICODE 

COMPILER_FLAGS = 	/GS- \
					/MD \
					/analyze- \
					/Zc:wchar_t \
					/errorReport:none \
					/WX- \
					/Zc:forScope \
					/Gd \
					/EHsc \
					/O2 \
					/I src/_default
LINKER_FLAGS = 


####################################
#              Macros              #
####################################
!INCLUDE _project

OUTPUT_FULLPATH = $(OUTPUT_DIR)/$(OUTPUT_NAME).$(OUTPUT_EXT)
FCOMPILER_FLAGS = $(COMPILER_FLAGS) /W$(WARNING_LEVEL) $(INCLUDES) /Fo"$(OBJECT_DIR)\"
VCVARSALL_FULLPATH = $(VC_PATH)\vcvarsall

!INCLUDE _objs

####################################
#             Commands             #
####################################

default: build

build: init
	@echo "******************  Compiling...  ************************"
	@call vc_compiler.cmd "$(OBJSX)" "$(VCVARSALL_FULLPATH)" $(BITS_VERSION) "$(FCOMPILER_FLAGS)" "$(OUTPUT_FULLPATH)" "$(LINKER_FLAGS)"
	@echo "****************  Compilation done  **********************"
	@echo "Build finished with success."
	@echo "You can find the resulting file at : "$(OUTPUT_FULLPATH)"
	@echo "**********************************************************"

clean:
	@rm -f "$(OUTPUT_FULLPATH)"
	@rm -f -r "$(OBJECT_DIR)"
	@echo "*********************  Cleaned  **************************"
	
run:
	@call "$(OUTPUT_FULLPATH)"
	
init:
	@mkdir -p "$(OUTPUT_DIR)"
	@mkdir -p "$(OBJECT_DIR)"
	
	