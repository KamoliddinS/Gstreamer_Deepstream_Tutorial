CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags gstreamer-1.0)
LIBS = $(shell pkg-config --libs gstreamer-1.0)
PLUGIN = libgstmyidentity.so
SOURCES = gstmyidentity.c

all: $(PLUGIN)

$(PLUGIN): $(SOURCES)
	$(CC) -shared -o $(PLUGIN) $(SOURCES) $(CFLAGS) $(LIBS)

clean:
	rm -f $(PLUGIN)
