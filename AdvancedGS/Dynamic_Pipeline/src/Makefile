# Variables
CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags gstreamer-1.0 gstreamer-video-1.0)
LIBS = $(shell pkg-config --libs gstreamer-1.0 gstreamer-video-1.0)
TARGET = dynamic_pipeline_app
SOURCE = dynamic_pipeline_app.c

# Default target
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LIBS)

# Clean target
clean:
	rm -f $(TARGET)
