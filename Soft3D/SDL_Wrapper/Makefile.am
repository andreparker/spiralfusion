## Makefile.am for the SDLmm library

# The SDL library target
lib_LTLIBRARIES = libSDLmm.la

HDRS=sdlmm_global.h sdlmm.h sdlmm_spoint.h sdlmm_srect.h sdlmm_color.h sdlmm_surface.h sdlmm_videoinfo.h \
     sdlmm_display.h sdlmm_basesurface.h sdlmm_pixelformat.h sdlmm_event.h sdlmm_eventhandler.h \
     sdlmm_audio.h sdlmm_timer.h sdlmm_joystick.h sdlmm_cd.h sdlmm_config.h

libSDLmm_la_SOURCES = sdlmm_global.cpp sdlmm_basesurface.cpp sdlmm_surface.cpp sdlmm_display.cpp sdlmm_pixelformat.cpp \
	sdlmm_srect.cpp sdlmm_event.cpp sdlmm_audio.cpp sdlmm_timer.cpp \
	sdlmm_joystick.cpp sdlmm_cd.cpp sdlmm_videoinfo.cpp
libSDLmm_la_LDFLAGS = 		\
        -release $(LT_RELEASE)	\
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

# The directory where the include files will be installed
libSDLmmincludedir = $(includedir)/SDLmm/

# Which header files to install
libSDLmminclude_HEADERS = $(HDRS) sdlmm_autoconfig.h

