#include "application.h"

void _application_initialize(app* self)
{
    self->applet = InitializeApplet(self->width, self->height, self->title, MUZZLE_FALSE, MUZZLE_TRUE);

    self->fonts_count = 0;
    self->fonts_max = APPLICATION_ARRAY_SIZE;
    self->fonts = MZ_CALLOC(self->fonts_max, sizeof(font));

    self->sprites_count = 0;
    self->sprites_max = APPLICATION_ARRAY_SIZE;
    self->sprites = MZ_CALLOC(self->sprites_max, sizeof(sprite));

    if (self->fonts == NULL) log_status(STATUS_FATAL_ERROR, "Fonts failed to allocate memory");
    if (self->sprites == NULL) log_status(STATUS_FATAL_ERROR, "Sprites failed to allocate memory");
}

void _application_quit(app* self)
{
    for (int i = 0; i > self->sprites_count; i++)
    {
        unload_sprite(&self->sprites[i]);
    }

    for (int i = 0; i > self->fonts_count; i++)
    {
        unload_font(self->fonts[i]);
    }

    MZ_FREE(self->sprites);
    MZ_FREE(self->fonts);

    QuitMuzzle(self->applet);
}

int _application_add_font(app* self, const char* font_name)
{
    // Checks if have enough space
    if (self->fonts_count >= self->fonts_max)
    {
        self->fonts_max += APPLICATION_ARRAY_SIZE;
        self->fonts = safe_realloc(self->fonts, sizeof(font) * self->fonts_max);

        if (self->fonts == NULL) log_status(STATUS_FATAL_ERROR, "Fonts failed to allocate memory [realloc]");
    }

    char font_path[512];
    sprintf(font_path, "../assets/fonts/%s.ttf", font_name);

    self->fonts[self->fonts_count] = load_font(font_path, font_name);
    self->fonts_count++;

    return self->fonts_count - 1;
}

int _application_add_sprite(app* self, const char* sprite_name)
{
    // Checks if have enough space
    if (self->sprites_count >= self->sprites_max)
    {
        self->sprites_max += APPLICATION_ARRAY_SIZE;
        self->sprites = safe_realloc(self->sprites, sizeof(sprite) * self->sprites_max);

        if (self->sprites == NULL) log_status(STATUS_FATAL_ERROR, "Sprites failed to allocate memory [realloc]");
    }

    char sprite_path[512];
    sprintf(sprite_path, "../assets/sprites/%s.png", sprite_name);

    self->sprites[self->sprites_count] = load_sprite(sprite_path);
    self->sprites_count++;

    return self->sprites_count - 1;
}

int _application_add_music(app* self, const char* music_name, int start_playing)
{
    // Checks if have enough space
    if (self->music_streams_count >= self->music_streams_max)
    {
        self->music_streams_max += APPLICATION_ARRAY_SIZE;
        self->music_streams = safe_realloc(self->music_streams, sizeof(Music) * self->music_streams_max);
        
        if (self->music_streams == NULL) log_status(STATUS_FATAL_ERROR, "Music streams failed to allocate memory [realloc]");
    }
    
    char music_path[512];
    sprintf(music_path, "../assets/music/%s.mp3", music_name);
    
    self->music_streams[self->music_streams_count] = LoadMusicStream(music_path);
    self->music_streams_count++;

    if (start_playing == MUZZLE_TRUE)
    {
        PlayMusicStream(self->music_streams[self->music_streams_count - 1]);
    }
    
    return self->music_streams_count - 1;
}

int _application_add_sound(app* self, const char* sound_name)
{
    // Checks if have enough space
    if (self->sound_streams_count >= self->sound_streams_max)
    {
        self->sound_streams_max += APPLICATION_ARRAY_SIZE;
        self->sound_streams = safe_realloc(self->sound_streams, sizeof(Sound) * self->sound_streams_max);

        if (self->sound_streams == NULL) log_status(STATUS_FATAL_ERROR, "Sound streams failed to allocate memory [realloc]");
    }

    char sound_path[512];
    sprintf(sound_path, "../assets/sounds/%s.wav", sound_name);

    self->sound_streams[self->sound_streams_count] = LoadSound(sound_path);
    self->sound_streams_count++;

    return self->sound_streams_count - 1;
}

struct _application application(const char* title, int width, int height)
{
    return (struct _application)
            {
                    .applet = {0},
                    .initialize = _application_initialize,
                    .quit = _application_quit,
                    .update = _application_update,
                    .title = title,
                    .width = width,
                    .height = height,
                    .fonts_max = 0,
                    .fonts_count = 0,
                    .fonts = NULL,
                    .sprites_max = 0,
                    .sprites_count = 0,
                    .sprites = NULL,
                    .add_sprite = _application_add_sprite,
                    .add_font = _application_add_font
            };
}