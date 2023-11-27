SYSTEM = $(shell uname -s)

TARGET = k81xfnkeys

all: $(TARGET)

ifeq (Linux,$(SYSTEM))
CFLAGS  = -Wall $(shell pkg-config hidapi-hidraw --cflags)
LIBS    = $(shell pkg-config hidapi-hidraw --libs)
else
CFLAGS  = $(shell pkg-config hidapi --cflags) -Wall
LIBS    = $(shell pkg-config hidapi --libs)
endif

OBJS = k81xfnkeys.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)
