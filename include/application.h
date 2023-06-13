#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#define APPLICATION_ARRAY_SIZE 10

#include <Muzzle.h>
#include "safe_realloc.h"
#include <raudio.h>

typedef struct _application
{
    void (*initialize)(struct _application*);
    void (*update)(struct _application*);
    void (*quit)(struct _application*);

    Applet applet;
    
    font* fonts;
    sprite* sprites;
    Music* music_streams;
    int* active_music_streams;
    Sound* sound_streams;
    
    size_t fonts_count;
    size_t sprites_count;
    size_t fonts_max;
    size_t sprites_max;
    size_t music_streams_count;
    size_t music_streams_max;
    size_t sound_streams_count;
    size_t sound_streams_max;
    size_t active_music_streams_count;
    size_t active_music_streams_max;

    int (*add_font)(struct _application*, const char*);
    int (*add_sprite)(struct _application*, const char*);
    int (*add_music)(struct _application*, const char*, int);
    int (*add_sound)(struct _application*, const char*);

    const char* title;
    int width;
    int height;
} app;

void _application_initialize(app* self);
void _application_update(app* self);
void _application_quit(app* self);

int _application_add_font(app* self, const char* font_name);
int _application_add_sprite(app* self, const char* sprite_name);
int _application_add_music(app* self, const char* music_name, int start_playing);
int _application_add_sound(app* self, const char* sound_name);


app application(const char* title, int width, int height);

#endif //GAME_APPLICATION_H