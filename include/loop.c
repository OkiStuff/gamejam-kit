#include "application.h"
#include "input.h"
#include <stdlib.h>
#include <time.h>

#include <raudio.h>

#define FONT(f) self->fonts[f]
#define SPRITE(s) &self->sprites[s]
#define NEW_INPUT_MANAGER() (input_manager){.applet=&self->applet}

void _application_update(app* self)
{
    while (keep_applet(self->applet.window_handle))
    {
        begin_drawing();
            clear_screen(GRAY);
        end_drawing(&self->applet);
    }
}

void OnAppletUpdate() { /* to prevent linking errors */ }