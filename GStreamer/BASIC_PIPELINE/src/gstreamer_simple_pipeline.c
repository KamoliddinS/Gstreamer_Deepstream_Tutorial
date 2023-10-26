// Include the main GStreamer header file.
#include <gst/gst.h>

// Entry point for the C program.
int main(int argc, char *argv[]) {
    // Declare pointers for the pipeline and other GStreamer components.
    GstElement *pipeline, *source, *sink;
    GstBus *bus;
    GstMessage *msg;

    // Initialize the GStreamer library, setting up internal path lists, registering built-in elements, and loading standard plugins.
    gst_init(&argc, &argv);

    // Create a new element of type "videotestsrc", which produces a test video pattern.
    source = gst_element_factory_make("videotestsrc", "source");

    // Create a new element of type "autovideosink", which automatically selects the best video sink (display method) available.
    sink = gst_element_factory_make("autovideosink", "sink");

    // Create a new pipeline to hold the elements.
    pipeline = gst_pipeline_new("test-pipeline");

    // Check if element creation was successful.
    if (!pipeline || !source || !sink) {
        g_printerr("Element creation failed.\n");
        return -1;
    }

    // Add the source and sink elements to the pipeline.
    gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);

    // Link the source element to the sink element, establishing data flow.
    if (!gst_element_link(source, sink)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // Set the "pattern" property of the source element to 0, which corresponds to the "smpte" pattern.
    g_object_set(source, "pattern", 0, NULL);

    // Set the pipeline's state to "playing", starting the data flow.
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Get the bus from the pipeline to listen for messages, such as errors or end-of-stream.
    bus = gst_element_get_bus(pipeline);

    // Block until an error message or end-of-stream (EOS) is received.
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // If a message was received, handle it.
    if (msg != NULL) {
        GError *err;
        gchar *debug_info;

        switch (GST_MESSAGE_TYPE(msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(msg, &err, &debug_info);
                g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
                g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
                g_clear_error(&err);
                g_free(debug_info);
                break;
            case GST_MESSAGE_EOS:
                g_print("End-Of-Stream reached.\n");
                break;
            default:
                g_printerr("Unexpected message received.\n");
                break;
        }
        gst_message_unref(msg);
    }

    // Free resources: set the pipeline's state to "null", unreference the pipeline and bus.
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    gst_object_unref(bus);

    // Exit the program.
    return 0;
}
