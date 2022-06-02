SRC=$(TARGET).c

compile: $(SRC)
	avr-gcc -mmcu=atmega8 -Os -o $(TARGET).o $(SRC)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).o $(TARGET).hex
	@echo "compiled successfully"


clean:
	@rm $(TARGET).o $(TARGET).hex
	@echo "Done cleaning"