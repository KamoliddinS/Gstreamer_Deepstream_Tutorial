#ifndef __GST_VOLUME_CONTROL_H__
#define __GST_VOLUME_CONTROL_H__

#include <gst/gst.h>
#include <gst/audio/audio.h>

G_BEGIN_DECLS

#define GST_TYPE_VOLUME_CONTROL (gst_volume_control_get_type())
G_DECLARE_FINAL_TYPE(GstVolumeControl, gst_volume_control, GST, VOLUME_CONTROL, GstElement)

struct _GstVolumeControl {
  GstElement element;
  GstPad *sinkpad, *srcpad;
  gdouble volume;  // Volume factor (1.0 means unchanged)
};

G_END_DECLS

#endif /* __GST_VOLUME_CONTROL_H__ */
