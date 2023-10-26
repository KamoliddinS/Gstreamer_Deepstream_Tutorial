#ifndef __GST_MYIDENTITY_H__
#define __GST_MYIDENTITY_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_MYIDENTITY (gst_my_identity_get_type())
G_DECLARE_FINAL_TYPE(GstMyIdentity, gst_my_identity, GST, MYIDENTITY, GstElement)

struct _GstMyIdentity {
  GstElement element;
  GstPad *sinkpad, *srcpad;
};

G_END_DECLS

#endif /* __GST_MYIDENTITY_H__ */
