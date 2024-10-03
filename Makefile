CC = sdcc
MCU = stm8
SRC = main.c
RELS = bin2/stm8l15x_lcd.rel bin2/stm8l15x_clk.rel bin2/stm8l15x_rtc.rel bin2/stm8l15x_gpio.rel

CFLAGS = --opt-code-size --std-sdcc99 -mstm8 -D__SDCC__ -DSTM8L15X_LD
LIBS = -lstm8

ODIR = bin
ODIREC = bin2

.SUFFIXES: .c .rel

INCLUDES = -IC:/STM8/stm8-sdcc-cmake/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver/inc -IC:/STM8/stm8-sdcc-cmake/StdPeriph
all: bin/main.ihx

#$(ODIREC)/%.rel : $(EXTRASRCPATH)%.c
#	$(CC) -c $(CFLAGS) $(INCLUDES) -m$(MCU) $< -o$(ODIREC)/

bin/main.ihx: $(SRC) $(RELS)
	$(CC) $(CFLAGS) $(INCLUDES) -m$(MCU) -l$(MCU) $(SRC) $(wildcard $(ODIREC)/*.rel) -o$(ODIR)/

bin2/stm8l15x_lcd.rel: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -m$(MCU) C:/STM8/stm8-sdcc-cmake/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_lcd.c -o$(ODIREC)/

bin2/stm8l15x_clk.rel: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -m$(MCU) C:/STM8/stm8-sdcc-cmake/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_clk.c -o$(ODIREC)/

bin2/stm8l15x_rtc.rel: 
	$(CC) -c $(CFLAGS) $(INCLUDES) -m$(MCU) C:/STM8/stm8-sdcc-cmake/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_rtc.c -o$(ODIREC)/

bin2/stm8l15x_gpio.rel:
	$(CC) -c $(CFLAGS) $(INCLUDES) -m$(MCU) C:/STM8/stm8-sdcc-cmake/StdPeriph/STM8L15x-16x-05x/Libraries/STM8L15x_StdPeriph_Driver/src/stm8l15x_gpio.c -o$(ODIREC)/

clean:
	@echo "clean project"
	cd bin && del *.ihx *.asm *.lst *.rel *.sym *.lk *.map *.mem *.rst
	cd bin2 && del *.ihx *.asm *.lst *.rel *.sym *.lk *.map *.mem *.rst

