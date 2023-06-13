#ifndef GAME_INPUT_H
#define GAME_INPUT_H

#include <Muzzle.h>
#include <stddef.h>

typedef struct _input_manager
{
    uint32_t key_pressed;
    uint32_t mouse_pressed;
    Applet* applet;
} input_manager;

int managed_key_press(input_manager* manager, int key);
int managed_mouse_press(input_manager* manager, int button);


#endif //GAME_INPUT_H