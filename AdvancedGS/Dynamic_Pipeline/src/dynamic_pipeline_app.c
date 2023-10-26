#include <gst/gst.h>

// Callback function when a new pad is created by decodebin
static void on_pad_added(GstElement *element, GstPad *pad, gpointer data) {
    GstPad *sinkpad;
    GstElement *converter = (GstElement *)data;

    sinkpad = gst_element_get_static_pad(converter, "sink");
    gst_pad_link(pad, sinkpad);
    gst_object_unref(sinkpad);
}

int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *decodebin, *videoconvert, *videoeffect, *videosink;
    GstBus *bus;
    GstMessage *msg;

    gst_init(&argc, &argv);

    // Create elements
    pipeline = gst_pipeline_new("dynamic-pipeline");
    source = gst_element_factory_make("filesrc", "source");
    decodebin = gst_element_factory_make("decodebin", "decoder");
    videoconvert = gst_element_factory_make("videoconvert", "converter");
    videoeffect = gst_element_factory_make("edgetv", "effect");  // Using edgetv effect as an example
    videosink = gst_element_factory_make("autovideosink", "videosink");

    // Set the input file location
    g_object_set(source, "location", "path_to_your_media_file", NULL);

    // Add elements to the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, decodebin, videoconvert, videoeffect, videosink, NULL);

    // Link elements
    gst_element_link(source, decodebin);
    gst_element_link_many(videoconvert, videoeffect, videosink, NULL);

    // Connect the pad-added signal for the decodebin
    g_signal_connect(decodebin, "pad-added", G_CALLBACK(on_pad_added), videoconvert);

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
