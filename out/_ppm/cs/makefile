####################################
#            Constants             #
####################################

-include _project

OUTPUT_DIR = out

# Config
MAINCLASS = EntryClass
MANIFEST = manifest.xml
SOURCE_DIR = src
COMP = csc
# [appcontainerexe, exe, library, module, winexe, winmdobj]
TARGETTYPE = exe




# Macros
CFLAGS = /target:$(TARGETTYPE) /main:$(MAINCLASS) /win32manifest:$(MANIFEST)
OUTPUT_FULL = $(OUTPUT_DIR)/$(OUTPUT_NAME).exe



####################################
#             Commands             #
####################################

# Default command
default: build

# Files
-include _objs

# Build command
build: init
	@$(COMP) $(CFLAGS) /out:$(OUTPUT_FULL) $(OBJSX)
	@echo "Build finished with success."
	@echo "You can find the resulting file at : "$(OUTPUT_FULL)

# Release mode
release: build
	
# Clean/Clear command
clean:
	@rm -f $(OUTPUT_FULL)
	@echo "Cleaned, ready for a new build."
clear: clean
	
# Help
help:
	@echo "Commands : make [CMD]"
	@echo "With [CMD] option :"
	@echo "   * build [DEFAULT]"
	@echo "   * clean/clear"
	
run:
	@.\$(OUTPUT_FULL)

	
####################################
#           Compilations           #
####################################

init:
	@echo "Compiling..."
	@rm -f $(OUTPUT_FULL)
	@mkdir -p $(OUTPUT_DIR)
	
