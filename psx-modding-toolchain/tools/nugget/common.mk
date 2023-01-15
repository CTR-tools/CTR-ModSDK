PREFIX ?= mipsel-none-elf
FORMAT ?= elf32-littlemips

ROOTDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CC  = $(PREFIX)-gcc
CXX = $(PREFIX)-g++

OVR_START_SYM = -Xlinker --defsym=OVR_START_ADDR=$(OVR_START_ADDR)
LDFLAGS += -Wl,--gc-sections

ARCHFLAGS = -march=mips1 -mabi=32 -EL -fno-pic -mno-shared -mno-abicalls -mfp32
ARCHFLAGS += -fno-stack-protector -nostdlib -ffreestanding
ifeq ($(USE_FUNCTION_SECTIONS),true)
CPPFLAGS += -ffunction-sections
endif
ifeq ($(DISABLE_FUNCTION_REORDER),true)
CPPFLAGS += -fno-toplevel-reorder
endif
CPPFLAGS += -mno-gpopt -fomit-frame-pointer
CPPFLAGS += -fno-builtin -fno-strict-aliasing -Wno-attributes -Wextra
CPPFLAGS += $(ARCHFLAGS)
CPPFLAGS += -I$(ROOTDIR)

LDFLAGS += -Wl,-Map=$(BINDIR)$(TARGET).map -nostdlib -T$(OVERLAYSCRIPT) $(LDSYMS) -static
LDFLAGS += $(ARCHFLAGS) -Wl,--oformat=$(FORMAT)
LDFLAGS += $(OVR_START_SYM)

CPPFLAGS += $(EXTRA_CC_FLAGS)
LDFLAGS += $(EXTRA_CC_FLAGS)

CXXFLAGS += -fno-exceptions -fno-rtti

OBJS += $(addsuffix .o, $(basename $(SRCS)))

all: dep $(foreach ovl, $(OVERLAYSECTION), $(BINDIR)Overlay$(ovl))

$(BINDIR)Overlay%: $(BINDIR)$(TARGET).elf
	$(PREFIX)-objcopy -j $(@:$(BINDIR)Overlay%=%) -O binary $< $(BINDIR)$(TARGET)$(@:$(BINDIR)Overlay%=%)
	$(PYTHON) $(TOOLSDIR)trimbin/trimbin.py $(BINDIR)$(TARGET)$(@:$(BINDIR)Overlay%=%) $(BUILDDIR)

$(BINDIR)$(TARGET).elf: $(OBJS)
ifneq ($(strip $(BINDIR)),)
	mkdir -p $(BINDIR)
endif
	$(CC) -o $(BINDIR)$(TARGET).elf $(OBJS) $(LDFLAGS)

%.o: %.s
	$(CC) $(ARCHFLAGS) -I$(ROOTDIR) -c -o $@ $<

%.dep: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -M -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

%.dep: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -M -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

%.dep: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -M -MT $(addsuffix .o, $(basename $@)) -MF $@ $<

# A bit broken, but that'll do in most cases.
%.dep: %.s
	$(GCCDIR)touch $@

DEPS := $(patsubst %.cpp, %.dep,$(filter %.cpp,$(SRCS)))
DEPS += $(patsubst %.cc, %.dep,$(filter %.cc,$(SRCS)))
DEPS +=	$(patsubst %.c, %.dep,$(filter %.c,$(SRCS)))
DEPS += $(patsubst %.s, %.dep,$(filter %.s,$(SRCS)))

-include $(DEPS)
dep: $(DEPS)