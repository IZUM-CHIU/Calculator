LINUXDIR = /home/u115/microtime/linux
#CFLAGS = -gdwarf-2 -O0
#CFLAGS = -O2
#CC=$(CROSS_COMPILE) $(CFLAGS) -I$(LINUXDIR)/include
CC = arm-unknown-linux-gnu-gcc -I$(LINUXDIR)/include


EXEC = Calculator
OBJS = Calculator.o creator_lib.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

romfs:
	$(ROMFSINST) /bin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.gdb *.o

