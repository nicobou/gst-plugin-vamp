/*
 * GStreamer
 * Copyright (C) 2006 Stefan Kost <ensonic@users.sf.net>
 * Copyright (C) 2012 Nicolas Bouillot <http://www.nicolasbouillot.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * SECTION:element-vamp
 *
 * FIXME:Describe vamp here.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch -v -m fakesrc ! vamp ! fakesink silent=TRUE
 * ]|
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include <gst/controller/gstcontroller.h>

#include "gstvamp.h"

GST_DEBUG_CATEGORY_STATIC (gst_vamp_debug);
#define GST_CAT_DEFAULT gst_vamp_debug

/* Filter signals and args */
enum
{
  /* FILL ME */
  LAST_SIGNAL
};

enum
{
  PROP_0,
  PROP_SILENT,
};

/* the capabilities of the inputs and outputs.
 *
 * FIXME:describe the real formats here.
 */
static GstStaticPadTemplate sink_template =
GST_STATIC_PAD_TEMPLATE (
  "sink",
  GST_PAD_SINK,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("ANY")
);

static GstStaticPadTemplate src_template =
GST_STATIC_PAD_TEMPLATE (
  "src",
  GST_PAD_SRC,
  GST_PAD_ALWAYS,
  GST_STATIC_CAPS ("ANY")
);

/* debug category for filtering log messages
 *
 */
#define DEBUG_INIT(bla) \
  GST_DEBUG_CATEGORY_INIT (gst_vamp_debug, "vamp", 0, "Vamp audio analysis plugins");

GST_BOILERPLATE_FULL (Gstvamp, gst_vamp, GstBaseTransform,
    GST_TYPE_BASE_TRANSFORM, DEBUG_INIT);

static void gst_vamp_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_vamp_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static GstFlowReturn gst_vamp_transform_ip (GstBaseTransform * base,
    GstBuffer * outbuf);

/* GObject vmethod implementations */

static void
gst_vamp_base_init (gpointer klass)
{
  GstElementClass *element_class = GST_ELEMENT_CLASS (klass);

  gst_element_class_set_details_simple (element_class,
    "vamp",
    "Generic/Filter",
    "Vamp audio analysis plugins",
    "Nicolas Bouillot <http://www.nicolasbouillot.net>");

  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (element_class,
      gst_static_pad_template_get (&sink_template));
}

/* initialize the vamp's class */
static void
gst_vamp_class_init (GstvampClass * klass)
{
  GObjectClass *gobject_class;

  gobject_class = (GObjectClass *) klass;
  gobject_class->set_property = gst_vamp_set_property;
  gobject_class->get_property = gst_vamp_get_property;

  g_object_class_install_property (gobject_class, PROP_SILENT,
    g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
			  FALSE, (GParamFlags) (G_PARAM_READWRITE | GST_PARAM_CONTROLLABLE)));

  GST_BASE_TRANSFORM_CLASS (klass)->transform_ip =
      GST_DEBUG_FUNCPTR (gst_vamp_transform_ip);
}

/* initialize the new element
 * initialize instance structure
 */
static void
gst_vamp_init (Gstvamp *filter, GstvampClass * klass)
{
  filter->silent = FALSE;
}

static void
gst_vamp_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  Gstvamp *filter = GST_VAMP (object);

  switch (prop_id) {
    case PROP_SILENT:
      filter->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_vamp_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  Gstvamp *filter = GST_VAMP (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, filter->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

/* GstBaseTransform vmethod implementations */

/* this function does the actual processing
 */
static GstFlowReturn
gst_vamp_transform_ip (GstBaseTransform * base, GstBuffer * outbuf)
{
  Gstvamp *filter = GST_VAMP (base);

  if (GST_CLOCK_TIME_IS_VALID (GST_BUFFER_TIMESTAMP (outbuf)))
    gst_object_sync_values (G_OBJECT (filter), GST_BUFFER_TIMESTAMP (outbuf));

  if (filter->silent == FALSE)
    g_print ("I'm plugged, therefore I'm in. hehe\n");
  
  /* FIXME: do something interesting here.  This simply copies the source
   * to the destination. */

  return GST_FLOW_OK;
}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
vamp_init (GstPlugin * vamp)
{
  /* initialize gst controller library */
  gst_controller_init(NULL, NULL);

  return gst_element_register (vamp, "vamp", GST_RANK_NONE,
      GST_TYPE_VAMP);
}

/* gstreamer looks for this structure to register vamps
 *
 */
GST_PLUGIN_DEFINE (
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    "vamp",
    "Vamp audio analysis plugins",
    vamp_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "http://gstreamer.net/"
)
