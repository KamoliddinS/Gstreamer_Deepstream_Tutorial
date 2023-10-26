
## Basic GStreamer Commands in C

GStreamer's true power lies in its ability to be integrated into applications. While the command-line tools are great for quick tests, building applications requires the use of GStreamer's C API. This section will introduce you to some basic GStreamer commands in C.

### Initializing GStreamer

Before using any GStreamer functions, the library must be initialized:

```c
#include <gst/gst.h>

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    // Your GStreamer code here
    return 0;
}
```

### Creating and Running a Simple Pipeline

To play a video file:

```c
GstElement *pipeline;
GstBus *bus;
GstMessage *msg;

pipeline = gst_parse_launch("playbin uri=file:///path/to/video.mp4", NULL);
gst_element_set_state(pipeline, GST_STATE_PLAYING);

bus = gst_element_get_bus(pipeline);
msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

if (msg != NULL)
    gst_message_unref(msg);

gst_object_unref(bus);
gst_element_set_state(pipeline, GST_STATE_NULL);
gst_object_unref(pipeline);
```

### Handling Bus Messages

To handle messages from the pipeline, such as errors or end-of-stream notifications:

```c
GstBus *bus;
GstMessage *msg;

bus = gst_element_get_bus(pipeline);
msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

if (msg != NULL) {
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
            g_print("An error occurred\n");
            break;
        case GST_MESSAGE_EOS:
            g_print("End of stream\n");
            break;
        default:
            g_print("Unexpected message\n");
            break;
    }
    gst_message_unref(msg);
}

gst_object_unref(bus);
```

### Dynamic Pipelines

GStreamer allows for dynamic pipelines where elements can be added or removed during playback:

```c
GstElement *pipeline, *source, *sink;

pipeline = gst_pipeline_new("my_pipeline");
source = gst_element_factory_make("videotestsrc", "source");
sink = gst_element_factory_make("autovideosink", "sink");

gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);
gst_element_link(source, sink);

gst_element_set_state(pipeline, GST_STATE_PLAYING);
// ... After some time
gst_element_set_state(pipeline, GST_STATE_NULL);

gst_object_unref(GST_OBJECT(pipeline));
```

### Conclusion

The GStreamer C API provides a robust set of functions to create multimedia applications. By understanding these basic commands, developers can build custom pipelines, handle various multimedia formats, and integrate GStreamer into their applications for powerful multimedia processing capabilities.
