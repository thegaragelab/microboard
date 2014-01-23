#----------------------------------------------------------------------------
# Microboard Project Makefile (LPC1114)
#----------------------------------------------------------------------------
# 23-Jan-2014 ShaneG
#
#  This will build a general firmware project for the LPC1114 Microboard. You
#  should not need to change this - simply drop your source files (any
#  combination of C, C++ or assembly) in the project directory and they will
#  be compiled and linked into the final image.
#----------------------------------------------------------------------------
include Makefile.inc

#=============================================================================#
# toolchain configuration
#=============================================================================#

TOOLCHAIN = arm-none-eabi-

CXX     = $(TOOLCHAIN)g++
CC      = $(TOOLCHAIN)gcc
AS      = $(TOOLCHAIN)gcc -x assembler-with-cpp
LD      = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy
OBJDUMP = $(TOOLCHAIN)objdump
SIZE    = $(TOOLCHAIN)size

#------------------------------------------------------------------------------
# Source files
#------------------------------------------------------------------------------

# File name extensions
EXT_C   = c
EXT_CPP = cpp
EXT_ASM = S

# Determine all the sources
SOURCES_C   =  $(wildcard $(patsubst %, %/*.$(EXT_C), .))
SOURCES_CPP =  $(wildcard $(patsubst %, %/*.$(EXT_CPP), .))
SOURCES_ASM =  $(wildcard $(patsubst %, %/*.$(EXT_ASM), .))

# Determine object file names from source file names
OBJECTS_C   = $(notdir $(SOURCES_C:.$(EXT_C)=.o))
OBJECTS_CPP = $(notdir $(SOURCES_CPP:.$(EXT_CPP)=.o))
OBJECTS_ASM = $(notdir $(SOURCES_ASM:.$(EXT_ASM)=.o))

# Complete list of object files required
OBJECTS = $(OBJECTS_ASM) $(OBJECTS_C) $(OBJECTS_CPP)

# Dependencies
DEPS = $(OBJECTS:.o=.d)

# Targets
TARGET_ELF = $(PROJECT_NAME).elf
TARGET_HEX = $(PROJECT_NAME).hex

TARGETS = $(TARGET_ELF) $(TARGET_HEX)

#=============================================================================#
# Compilation options
#=============================================================================#

# core type
CORE = cortex-m0

# Linker script to use
LD_SCRIPT = ${LIBS}/lpc1114/lpc1114.ld

# C++ language standard ("c++98", "gnu++98" - default, "c++0x", "gnu++0x")
CXX_STD = gnu++98

# C language standard ("c89" / "iso9899:1990", "iso9899:199409",
# "c99" / "iso9899:1999", "gnu89" - default, "gnu99")
C_STD = gnu89

# optimization flags ("-O0" - no optimization, "-O1" - optimize, "-O2" -
# optimize even more, "-Os" - optimize for size or "-O3" - optimize yet more)
OPTIMIZATION = -O0

# define warning options here
CXX_WARNINGS = -Wall -Wextra
C_WARNINGS = -Wall -Wstrict-prototypes -Wextra

# core flags
CORE_FLAGS = -mcpu=$(CORE) -mthumb -DMICROBOARD_LPC1114

# flags for C++ compiler
CXX_FLAGS = -std=$(CXX_STD) -g -ggdb3 -fno-rtti -fno-exceptions -fverbose-asm -Wa,-ahlms=$(notdir $(<:.$(EXT_CPP)=.lst))

# flags for C compiler
C_FLAGS = -std=$(C_STD) -g -ggdb3 -fverbose-asm -Wa,-ahlms=$(notdir $(<:.$(EXT_C)=.lst))

# flags for assembler
AS_FLAGS = -g -ggdb3 -Wa,-amhls=$(notdir $(<:.$(EXT_ASM)=.lst))

# flags for linker
LD_FLAGS = -T$(LD_SCRIPT) -g -Wl,-Map=$(PROJECT_NAME).map,--cref,--no-warn-mismatch

# format final flags for tools, request dependancies for C++, C and asm
CXX_FLAGS_F = $(CORE_FLAGS) $(OPTIMIZATION) $(CXX_WARNINGS) $(CXX_FLAGS) $(CXX_DEFS) -MD -MP -MF $(@F:.o=.d) -I. -I$(INCLUDE)
C_FLAGS_F = $(CORE_FLAGS) $(OPTIMIZATION) $(C_WARNINGS) $(C_FLAGS) $(C_DEFS) -MD -MP -MF $(@F:.o=.d) -I. -I$(INCLUDE)
AS_FLAGS_F = $(CORE_FLAGS) $(AS_FLAGS) $(AS_DEFS) -MD -MP -MF $(@F:.o=.d)  -I. -I$(INCLUDE)
LD_FLAGS_F = $(CORE_FLAGS) $(LD_FLAGS) -L$(LIBS)/lpc1114 -nostartfiles

# Files that get generated
GENERATED = $(wildcard $(patsubst %, *.%, d o lst elf hex map))

#=============================================================================#
# make all
#=============================================================================#

all : $(TARGETS)
	@echo "Generated object size ..."
	@$(SIZE) -B $(TARGET_ELF)

# make object files dependent on Makefile
$(OBJECTS) : Makefile

# make .elf file dependent on linker script
$(TARGET_ELF) : $(LD_SCRIPT)

#-----------------------------------------------------------------------------#
# linking - objects -> elf
#-----------------------------------------------------------------------------#

$(TARGET_ELF) : $(OBJECTS)
	@echo 'Linking: $(TARGET_ELF)'
	@$(CXX) $(LD_FLAGS_F) $(OBJECTS) -lmicroboard -o $@

#-----------------------------------------------------------------------------#
# memory images - elf -> hex, elf -> bin
#-----------------------------------------------------------------------------#

$(TARGET_HEX) : $(TARGET_ELF)
	@echo 'Hex image: $(TARGET_HEX)'
	@$(OBJCOPY) -O ihex $< $@

#-----------------------------------------------------------------------------#
# compiling - C++ source -> objects
#-----------------------------------------------------------------------------#

%.o : %.$(EXT_CPP)
	@echo 'Compiling: $<'
	@$(CXX) -c $(CXX_FLAGS_F) $< -o $@

#-----------------------------------------------------------------------------#
# compiling - C source -> objects
#-----------------------------------------------------------------------------#

%.o : %.$(EXT_C)
	@echo 'Compiling: $<'
	@$(CC) -c $(C_FLAGS_F) $< -o $@

#-----------------------------------------------------------------------------#
# assembling - ASM source -> objects
#-----------------------------------------------------------------------------#

%.o : %.$(EXT_ASM)
	@echo 'Assembling: $<'
	@$(AS) -c $(AS_FLAGS_F) $< -o $@

#=============================================================================#
# make clean
#=============================================================================#

clean:
	@rm -f $(GENERATED)

#=============================================================================#
# global exports
#=============================================================================#

.PHONY: all clean dependents

.SECONDARY:

# include dependancy files
-include $(DEPS)
