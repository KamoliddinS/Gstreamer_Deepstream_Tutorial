# Variables
CC = gcc
CFLAGS = -Wall -fPIC
LIBS = $(shell pkg-config --libs gstreamer-1.0 gstreamer-base-1.0)
INCLUDES = $(shell pkg-config --cflags gstreamer-1.0 gstreamer-base-1.0)
PLUGIN_NAME = libgstinvertcolor.so

# Targets
all: $(PLUGIN_NAME)

$(PLUGIN_NAME): gst_invert_color.o
	$(CC) -shared -o $@ $^ $(LIBS)

gst_invert_color.o: gst_invert_color.c gst_invert_color.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o $(PLUGIN_NAME)

install: $(PLUGIN_NAME)
	cp $(PLUGIN_NAME) /usr/lib/gstreamer-1.0/

uninstall:
	rm -f /usr/lib/gstreamer-1.0/$(PLUGIN_NAME)
