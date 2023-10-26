#ifndef __GST_INVERT_COLOR_H__
#define __GST_INVERT_COLOR_H__

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>

G_BEGIN_DECLS

#define GST_TYPE_INVERT_COLOR (gst_invert_color_get_type())
G_DECLARE_FINAL_TYPE(GstInvertColor, gst_invert_color, GST, INVERT_COLOR, GstBaseTransform)

struct _GstInvertColor {
    GstBaseTransform parent;
};

G_DEFINE_TYPE(GstInvertColor, gst_invert_color, GST_TYPE_BASE_TRANSFORM)

G_END_DECLS

#endif // __GST_INVERT_COLOR_H__
