text_interfaceltlibs = libtext_interface.la
text_interfaceldflags = -export-dynamic -avoid-version
text_interfacesources = text.cpp

lib_LTLIBRARIES = $(text_interfaceltlibs)

AM_CXXFLAGS = @DFLAGS@ -D_REENTRANT \
		-I$(top_builddir) -I$(top_srcdir)/libalsaplayer \
		-I$(top_srcdir)/alsaplayer \
		-DADDON_DIR=\"$(ADDON_DIR)\"

libdir = $(ADDON_DIR)/interface

libtext_interface_la_LDFLAGS = $(text_interfaceldflags)
libtext_interface_la_LIBADD =
libtext_interface_la_SOURCES= $(text_interfacesources)
