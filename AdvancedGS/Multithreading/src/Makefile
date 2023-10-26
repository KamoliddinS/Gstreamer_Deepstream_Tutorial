# Variables
CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags gstreamer-1.0 gstreamer-audio-1.0)
LIBS = $(shell pkg-config --libs gstreamer-1.0 gstreamer-audio-1.0)
TARGET = multi_threaded_gstreamer
SOURCE = multi_threaded_gstreamer.c

# Default target
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LIBS)

# Clean target
clean:
	rm -f $(TARGET)
