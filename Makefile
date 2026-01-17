# dsu
DEVKITPRO ?= /opt/devkitpro
DEVKITARM ?= $(DEVKITPRO)/devkitARM
LIBNDS    ?= $(DEVKITPRO)/libnds
CALICO    ?= $(DEVKITPRO)/calico

CC   = $(DEVKITARM)/bin/arm-none-eabi-gcc
AS   = $(DEVKITARM)/bin/arm-none-eabi-as
GRIT = $(DEVKITPRO)/tools/bin/grit

ARCH = -mcpu=arm946e-s -mtune=arm946e-s -mthumb -mthumb-interwork

CFLAGS  = -DARM9 -D__NDS__ -O2 -g $(ARCH) \
          -fomit-frame-pointer -ffast-math \
          -I$(CALICO)/include -I$(LIBNDS)/include -Iinclude -Ibuild

LDFLAGS = -specs=$(CALICO)/share/ds9.specs -g $(ARCH) \
          -L$(CALICO)/lib -L$(LIBNDS)/lib

LDLIBS  = -lnds9 -lcalico_ds9 -lm

DEFAULT_ARM7 = $(CALICO)/bin/ds7_maine.elf
OUT = build/dsu.nds
EMU ?= melonds
SRC = source/*.c source/scenes/*.c

# graphics
GFX_PNG  = $(wildcard data/*.png)
GFX_OBJ  = $(patsubst data/%.png,build/%.o,$(GFX_PNG))
GFX_HDR  = $(patsubst data/%.png,build/%.h,$(GFX_PNG))

all: $(OUT)

build/%.s build/%.h: data/%.png data/%.grit | build
	$(GRIT) $< -fts -o build/$* -ff data/$*.grit

build/%.o: build/%.s
	$(AS) -o $@ $<

build/arm9.elf: $(GFX_HDR) $(SRC) $(GFX_OBJ) | build
	$(CC) $(CFLAGS) $(SRC) $(GFX_OBJ) $(LDFLAGS) $(LDLIBS) -o $@

build/dsu.nds: build/arm9.elf
	ndstool -c $@ -9 $< -7 $(DEFAULT_ARM7)

build:
	mkdir -p build

clean:
	rm -rf build

run: $(OUT)
	$(EMU) $(OUT)

.PHONY: all clean run
