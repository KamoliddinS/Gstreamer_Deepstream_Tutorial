// Include the main GStreamer header file.
#include <gst/gst.h>

// Entry point for the C program.
int main(int argc, char *argv[]) {
    // Declare pointers for the pipeline and other GStreamer components.
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    // Initialize the GStreamer library, setting up internal path lists, registering built-in elements, and loading standard plugins.
    gst_init(&argc, &argv);

    // Create a new pipeline from a pipeline description. This is a quick way to set up a pipeline, but in real applications, you might want to construct pipelines manually.
    pipeline = gst_parse_launch("playbin uri=file:///path/to/video.mp4", NULL);

    // Set the state of the pipeline to "playing". This starts the playback of the video.
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Get the bus of the pipeline. The bus is responsible for carrying messages from the pipeline to the application.
    bus = gst_element_get_bus(pipeline);

    // Wait for an error message or end-of-stream (EOS) on the bus. This will block until one of these messages is posted.
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // If a message was received, unreference it to decrease its reference count and free its resources.
    if (msg != NULL)
        gst_message_unref(msg);

    // Unreference the bus to decrease its reference count and free its resources.
    gst_object_unref(bus);

    // Set the state of the pipeline to "null", which stops playback and releases resources.
    gst_element_set_state(pipeline, GST_STATE_NULL);

    // Unreference the pipeline to decrease its reference count and free its resources.
    gst_object_unref(pipeline);

    // Exit the program.
    return 0;
}
