SYSTEM = $(shell uname -s)

TARGET = k81xfnkeys

all: $(TARGET)

ifeq (Linux,$(SYSTEM))
CFLAGS  = -Wall $(shell pkg-config hidapi-hidraw --cflags)
LIBS    = $(shell pkg-config hidapi-hidraw --libs)
else
CFLAGS  = -I/usr/local/include/hidapi -Wall
LIBS    = -lhidapi
endif

OBJS = k81xfnkeys.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)
