CC =  gcc
CFLAGS = -Wall -g
TARGET = test_dll
OBJ = test_dll.o dll.o

all: $(TARGET) clean
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

test_dll.o:	 test_dll.c test_dll.h
	$(CC) $(CFLAGS) -c test_dll.c test_dll.h
dll.o:       dll.c dll.h
	$(CC) $(CFLAGS) -c dll.c dll.h

clean:
	rm -f test_dll.o dll.o test_dll.h.gch dll.h.gch
