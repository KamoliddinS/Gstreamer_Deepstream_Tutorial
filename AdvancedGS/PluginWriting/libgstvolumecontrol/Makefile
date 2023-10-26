CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags gstreamer-1.0 gstreamer-audio-1.0)
LIBS = $(shell pkg-config --libs gstreamer-1.0 gstreamer-audio-1.0)
PLUGIN = libgstvolumecontrol.so
SOURCES = gstvolumecontrol.c

all: $(PLUGIN)

$(PLUGIN): $(SOURCES)
	$(CC) -shared -o $(PLUGIN) $(SOURCES) $(CFLAGS) $(LIBS)

clean:
	rm -f $(PLUGIN)
