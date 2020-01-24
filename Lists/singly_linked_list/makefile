CC =  gcc
CFLAGS = -Wall -g
TARGET = test_sll
OBJ = test_sll.o sll.o

all: $(TARGET) clean
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

test_sll.o:	 test_sll.c test_sll.h
	$(CC) $(CFLAGS) -c test_sll.c test_sll.h
sll.o:       sll.c sll.h
	$(CC) $(CFLAGS) -c sll.c sll.h

clean:
	rm -f test_sll.o sll.o test_sll.h.gch sll.h.gch
