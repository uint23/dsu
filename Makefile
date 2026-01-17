# dsu
DEVKITPRO ?= /opt/devkitpro
DEVKITARM ?= $(DEVKITPRO)/devkitARM
LIBNDS    ?= $(DEVKITPRO)/libnds
CALICO    ?= $(DEVKITPRO)/calico

CC       = $(DEVKITARM)/bin/arm-none-eabi-gcc
CFLAGS   = -DARM9 -D__NDS__ -O2 -mcpu=arm946e-s -mtune=arm946e-s -mthumb -mthumb-interwork \
           -fomit-frame-pointer -ffast-math \
           -I$(CALICO)/include -I$(LIBNDS)/include -Iinclude
LDFLAGS  = -T$(CALICO)/lib/ds9.ld -g -mthumb -mthumb-interwork \
           -L$(CALICO)/lib -L$(LIBNDS)/lib -lcalico_ds9 -lnds9 -lm

# Default ARM7 binary (from calico/default-arm7 package)
DEFAULT_ARM7 = $(CALICO)/bin/ds7_maine.elf

OUT = build/dsu.nds
EMU = melonDS

all: $(OUT)

build/arm9.elf: source/*.c | build
	$(CC) $(CFLAGS) source/dsu.c $(LDFLAGS) -o $@

build/dsu.nds: build/arm9.elf
	ndstool -c $@ -9 build/arm9.elf -7 $(DEFAULT_ARM7)

build:
	mkdir -p build

clean:
	rm -rf build

run:
	melonDS build/dsu.nds

.PHONY: all clean run
