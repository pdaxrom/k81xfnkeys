TARGET = k81xfnkeys

all: $(TARGET)

CFLAGS = -I/usr/local/include/hidapi -Wall

OBJS = k81xfnkeys.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -lhidapi

clean:
	rm -f $(TARGET) $(OBJS)
