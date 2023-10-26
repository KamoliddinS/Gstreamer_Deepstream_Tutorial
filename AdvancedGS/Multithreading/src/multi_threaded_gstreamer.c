#include <gst/gst.h>

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *decodebin, *queue, *audioconvert, *audiosink;
    GstBus *bus;
    GstMessage *msg;

    gst_init(&argc, &argv);

    // Create elements
    pipeline = gst_pipeline_new("multi-threaded-pipeline");
    source = gst_element_factory_make("filesrc", "source");
    decodebin = gst_element_factory_make("decodebin", "decoder");
    queue = gst_element_factory_make("queue", "queue");
    audioconvert = gst_element_factory_make("audioconvert", "converter");
    audiosink = gst_element_factory_make("autoaudiosink", "audiosink");

    // Set the input file location
    g_object_set(source, "location", "path_to_your_media_file", NULL);

    // Add elements to the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, decodebin, queue, audioconvert, audiosink, NULL);

    // Link elements
    gst_element_link(source, decodebin);
    gst_element_link_many(queue, audioconvert, audiosink, NULL);

    // Connect a callback for the "pad-added" signal of decodebin
    g_signal_connect(decodebin, "pad-added", G_CALLBACK(gst_pad_link), gst_element_get_static_pad(queue, "sink"));

    // Start playing
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Listen to the bus
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    // Clean up
    if (msg != NULL)
        gst_message_unref(msg);

    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
