TARGET ?= BasicOnOff
CC = gcc
LD = ld
C_SRC = BasicOnOff.c
CFLAGS = -g -Wall -Wextra -lm
EXEDIR = exe

$(EXEDIR)/$(TARGET): $(C_SRC)
	mkdir -p $(EXEDIR)
	$(CC) $(DEBUG) -o $@ $^ $(CFLAGS)

debug: DEBUG = -DDEBUG

debug: $(EXEDIR)/$(TARGET)

clean:
	rm -f $(EXEDIR)/$(TARGET)
