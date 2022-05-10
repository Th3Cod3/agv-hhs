#build
BUILD			= build
LIBS_DIR		= lib
TARGET			= main.c
LIBS			= $(wildcard $(LIBS_DIR)/*.c)
OBJS			= $(LIBS:.c=.o)
OBJS			+= $(TARGET:.c=.o)
ASMS			= $(OBJS:.o=.asm)

# DEFINE
FLAGS			= -D F_CPU=16000000UL
FLAGS			+= -D DEBUG_EN=1

# DEFINE
PORT			= COM3
DEVICE			= atmega2560
PROGRAMMER		= arduino
#BAUD			= 57600
BAUD			= 115200
COMPILE			= avr-gcc -Wall -Os -mmcu=$(DEVICE) -std=gnu99

.PHONY: clean upload

default: compile upload

%.asm: %.c
	$(COMPILE) -S -c $< -o $@

%.o: %.c
	$(COMPILE) $(FLAGS) -c $< -o $@

compile: clean-all $(OBJS)
	$(COMPILE) -o $(BUILD).elf $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(BUILD).elf $(BUILD).hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD).elf

asm: clean-all $(ASMS)

upload:
	avrdude -v -D -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -Uflash:w:$(BUILD).hex:i

clean:
	-rm *.o
	-rm *.elf
	-rm *.hex
	-rm *.s
	-rm *.asm

clean-all: clean
	-rm $(LIBS_DIR)/*.o
	-rm $(LIBS_DIR)/*.s
	-rm $(LIBS_DIR)/*.asm