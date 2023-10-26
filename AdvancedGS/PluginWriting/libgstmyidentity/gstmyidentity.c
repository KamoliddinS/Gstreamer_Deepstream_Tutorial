#include "gstmyidentity.h"

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE(
    "sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE(
    "src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

G_DEFINE_TYPE(GstMyIdentity, gst_my_identity, GST_TYPE_ELEMENT)

static void gst_my_identity_class_init(GstMyIdentityClass *klass) {
  GstElementClass *element_class = GST_ELEMENT_CLASS(klass);

  gst_element_class_set_static_metadata(element_class,
    "My Identity Plugin",
    "Example",
    "Passes data unchanged",
    "Author Name <author@email.com>");

  gst_element_class_add_static_pad_template(element_class, &src_template);
  gst_element_class_add_static_pad_template(element_class, &sink_template);
}

static void gst_my_identity_init(GstMyIdentity *filter) {
  filter->sinkpad = gst_pad_new_from_static_template(&sink_template, "sink");
  gst_element_add_pad(GST_ELEMENT(filter), filter->sinkpad);

  filter->srcpad = gst_pad_new_from_static_template(&src_template, "src");
  gst_element_add_pad(GST_ELEMENT(filter), filter->srcpad);
}

static gboolean plugin_init(GstPlugin *plugin) {
  return gst_element_register(plugin, "myidentity", GST_RANK_NONE, GST_TYPE_MYIDENTITY);
}

GST_PLUGIN_DEFINE(
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    myidentity,
    "My identity plugin",
    plugin_init,
    "1.0",
    "LGPL",
    "GStreamer Course",
    "http://gstreamer.net/"
)
