C = gcc
CFLAGS = -g -Wall -MMD 
LDLIBS = -lSDL3_image -lSDL3

TARGET = PlatForMen
SRCS = main.c game.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(C) $(OBJS) -o $@ $(LDLIBS)

%.o: %.c
	$(C) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) || exit 0
