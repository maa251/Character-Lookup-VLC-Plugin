LD = ld
CC = cc
OS = Linux
DESTDIR =
INSTALL = install
CFLAGS = -g0 -O3 -Wall -Wextra
LDFLAGS =
VLC_PLUGIN_CFLAGS := $(shell pkg-config --cflags vlc-plugin)
VLC_PLUGIN_LIBS := $(shell pkg-config --libs vlc-plugin)

plugindir := $(shell pkg-config vlc-plugin --variable=pluginsdir)

override CC += -std=gnu11
override CPPFLAGS += -DPIC -I. -Isrc
override CFLAGS += -fPIC

override CPPFLAGS += -DMODULE_STRING=\"character_lookup\"
override CFLAGS += $(VLC_PLUGIN_CFLAGS)
override LDFLAGS += $(VLC_PLUGIN_LIBS)

ifeq ($(OS),Linux)
  EXT := so
else ifeq ($(OS),Windows)
  EXT := dll
else ifeq ($(OS),macOS)
  EXT := dylib
else
  $(error Unknown OS specified, please set OS to either Linux, Windows or macOS)
endif

TARGETS = libtest_plugin.$(EXT)

all: libtest_plugin.$(EXT)

install: all
	mkdir -p -- $(DESTDIR)$(plugindir)/video_filter
	$(INSTALL) --mode 0755 libtest_plugin.$(EXT) $(DESTDIR)$(plugindir)/video_filter

install-strip:
	$(MAKE) install INSTALL="$(INSTALL) -s"

uninstall:
	rm -f $(DESTDIR)$(plugindir)/video_filter/libtest_plugin.$(EXT)

clean:
	rm -f -- libtest_plugin.$(EXT) pause_click.o

mostlyclean: clean

SOURCES = character_lookup.c

$(SOURCES:%.c=%.o): %: character_lookup.c

libtest_plugin.$(EXT): $(SOURCES:%.c=%.o)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

.PHONY: all install install-strip uninstall clean mostlyclean
