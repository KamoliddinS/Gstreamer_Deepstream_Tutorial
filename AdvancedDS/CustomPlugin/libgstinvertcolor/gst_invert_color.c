#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>

#define GST_TYPE_INVERT_COLOR gst_invert_color_get_type()
G_DECLARE_FINAL_TYPE(GstInvertColor, gst_invert_color, GST, INVERT_COLOR, GstBaseTransform)

struct _GstInvertColor {
    GstBaseTransform parent;
};

G_DEFINE_TYPE(GstInvertColor, gst_invert_color, GST_TYPE_BASE_TRANSFORM)

static GstFlowReturn gst_invert_color_transform_ip(GstBaseTransform *base, GstBuffer *buf) {
    GstMapInfo info;

    if (gst_buffer_map(buf, &info, GST_MAP_READWRITE)) {
        for (gsize i = 0; i < info.size; i++) {
            info.data[i] = 255 - info.data[i];  // Invert color
        }
        gst_buffer_unmap(buf, &info);
    }

    return GST_FLOW_OK;
}

static void gst_invert_color_class_init(GstInvertColorClass *klass) {
    GstElementClass *element_class = GST_ELEMENT_CLASS(klass);
    GstBaseTransformClass *base_transform_class = GST_BASE_TRANSFORM_CLASS(klass);

    gst_element_class_set_static_metadata(element_class,
        "Color Inverter",
        "Filter/Effect/Video",
        "Inverts video colors",
        "Your Name <your.email@example.com>");

    base_transform_class->transform_ip = GST_DEBUG_FUNCPTR(gst_invert_color_transform_ip);
}

static void gst_invert_color_init(GstInvertColor *self) {
    // Initialization, if needed
}

static gboolean plugin_init(GstPlugin *plugin) {
    return gst_element_register(plugin, "invertcolor", GST_RANK_NONE, GST_TYPE_INVERT_COLOR);
}

GST_PLUGIN_DEFINE(
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    invertcolor,
    "Inverts video colors",
    plugin_init,
    "1.0",
    "LGPL",
    "YourPlugin",
    "http://yourpluginwebsite.com"
)
