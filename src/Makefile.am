# Note: plugindir is set in configure
AM_CXXFLAGS = \
    $(GST_CFLAGS) \
    $(VAMPHOST_CFLAGS)

plugin_LTLIBRARIES = \
    libgstvamp.la

# sources used to compile this plug-in
libgstvamp_la_SOURCES = \
    gstvamp.cpp \
    gstvamp.h \
    system.h \
    vamp-host.cpp \
    vamp-host.h

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstvamp_la_LIBADD = \
    $(GST_LIBS) \
    $(VAMPHOST_LIBS)


libgstvamp_la_LDFLAGS = \
    $(GST_PLUGIN_LDFLAGS)

libgstvamp_la_LIBTOOLFLAGS = \
    --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = \
    gstvamp.h \
    system.h
