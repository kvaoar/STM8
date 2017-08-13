MCU=stm8
DEVICE=stm8s003f3
FLASHER=stlinkv2
LIBDIR=libs
CFLAGS= --std-c99  -I$(LIBDIR) -DSTM8S003 -c
CC=sdcc
LIB=stm8s_gpio.rel stm8s_spi.rel stm8s_clk.rel
TARGET=leds
OBJ=$(TARGET).rel

OUTDIR=build

.PHONY: all clean run

%.rel: %.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

%.rel:$(LIBDIR)/%.c
	$(CC) -m$(MCU) $(CFLAGS) $(LDFLAGS) $<

all: $(OBJ) $(LIB)
	$(CC) -m$(MCU) -o $(OUTDIR)/$(TARGET).ihx $(OBJ) $(LIB)
	objcopy -Iihex -Obinary $(OUTDIR)/$(TARGET).ihx $(OUTDIR)/$(TARGET).bin
	ls -l $(OUTDIR)/$(TARGET).bin 
	rm -v *.sym *.asm *.lst *.rel *.rst > /dev/null

run:	
	stm8flash -c $(FLASHER) -p $(DEVICE) -s flash -w $(OUTDIR)/$(TARGET).ihx
     
clean:
	rm -v *.sym *.asm *.lst *.rel *.ihx *.lk *.rst *.cdb *.map > /dev/null
