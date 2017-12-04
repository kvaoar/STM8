MCU=stm8
DEVICE=stm8s003f3
FLASHER=stlinkv2
LIBDIR=libs
INCDIR=inc
SRCDIR=src
CFLAGS= --std-c99 -I$(LIBDIR) -I$(INCDIR) -c
CC=sdcc
LIB=stm8s_gpio.rel stm8s_spi.rel stm8s_clk.rel adc.rel display.rel stm8s_uart1.rel
TARGET=main
OBJ=$(TARGET).rel

OUTDIR=build

.PHONY: all clean run

%.rel: %.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

%.rel:$(LIBDIR)/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<
	
%.rel:$(SRCDIR)/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

all: $(OBJ) $(LIB)
	@mkdir -p $(OUTDIR)
	$(CC) -m$(MCU) -o $(OUTDIR)/$(TARGET).ihx $(OBJ) $(LIB)
	objcopy -Iihex -Obinary $(OUTDIR)/$(TARGET).ihx $(OUTDIR)/$(TARGET).bin
	size --format=Berkeley $(OUTDIR)/$(TARGET).ihx
	@rm -v *.sym *.asm *.lst *.rel *.rst > /dev/null

run:	
	stm8flash -c $(FLASHER) -p $(DEVICE) -s flash -w $(OUTDIR)/$(TARGET).ihx
     
clean:
	rm -vrf $(OUTDIR) *.sym *.asm *.lst *.rel *.ihx *.lk *.rst *.cdb *.map 
