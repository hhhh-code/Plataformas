#include <allegro.h>
void init();
void deinit();
using namespace std;
BITMAP *SCREEN;
BITMAP *System;
BITMAP *lienzo;
void *focus = NULL;
int WIDTH = 640;
int HEIGHT = 480;
#include <math.h>
#include <iostream>
#include <list>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "Header/Alarm.h"
#include "Header/Functions.h"
#include "Header/Object.h"
#include "Header/Block.h"

volatile long speed_counter = 0;

void increment_speed_counter()
{
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);
void create_plataform(int x, int y, int size);

int main()
{
    init();
    BITMAP *background = load_bitmap("img/background.bmp", NULL);
    lienzo = create_bitmap(SCREEN_W, SCREEN_H);
    System = create_bitmap(SCREEN_W, SCREEN_H);
    SCREEN = create_bitmap(SCREEN_W, SCREEN_H);

    create_plataform(0, 230, 10);
    create_plataform(10*32, 250, 5);
    create_plataform(19*32, 230, 10);

    while (!key[KEY_ESC])
    {
        //limitar los fps
        if (speed_counter > 0)
        {
            stretch_sprite(lienzo, background, 0, 0, SCREEN_W, SCREEN_H);
            for (list<Object *>::iterator it = instancias.begin(); it != instancias.end(); it++)
            {
                Object *other = *it;
                other->action();
            }
            speed_counter--;
            draw_sprite(screen, lienzo, 0, 0);
            clear_bitmap(lienzo);
        }
        else
        {
        }
    }

    deinit();
    return 0;
}
END_OF_MAIN()

void create_plataform(int x, int y, int size)
{
    for (int i = 0; i < size; i++)
    {
        Block *b = new Block();
        b->x = x + (i * b->w);
        b->y = y;
        b->pushMe();
    }
}

void init()
{
    int depth, res;
    allegro_init();
    depth = desktop_color_depth();
    if (depth == 0)
        depth = 32;
    set_color_depth(depth);
    res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    if (res != 0)
    {
        allegro_message("%s", allegro_error);
        exit(-1);
    }

    enable_triple_buffer();
    LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(increment_speed_counter);

    // Iniciamos el limitador de FPS
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(120));
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
    install_timer();
    install_keyboard();
    install_mouse();
    show_mouse(screen);
    /* add other initializations here */
    set_uformat(U_ASCII);
}

void deinit()
{
    clear_keybuf();
    /* add other deinitializations here */
}
