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
#include "Header/Personaje.h"
#include "Header/Burning-ghoul.h"
#include "Header/Block.h"
#include "Header/Background.h"

volatile long speed_counter = 0;

void increment_speed_counter()
{
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);
void create_plataform(int x, int y, int large);

int main()
{
    init();
    lienzo = create_bitmap(SCREEN_W, SCREEN_H);
    System = create_bitmap(SCREEN_W, SCREEN_H);
    SCREEN = create_bitmap(SCREEN_W, SCREEN_H);

    (new Personaje())->pushMe();
    //(new Burning_ghoul())->pushMe();
    (new Background())->pushMe();

    create_plataform(0, 230, 10);
    create_plataform(10*32, 250, 5);
    create_plataform(19*32, 230, 10);
    //create_plataform(0, 200, 2);

    while (!key[KEY_ESC])
    {
        if (speed_counter > 0)
        {
            for (list<Object *>::iterator it = instancias.begin(); it != instancias.end(); it++)
            {
                Object *other = *it;
                other->action();
            }
            speed_counter--;
            draw_sprite(screen, lienzo, 0, 0);
            clear_bitmap(lienzo);
        }else{
            
        }

        while (!Remove.empty())
        {
            Object *other = reinterpret_cast<Object *>(*Remove.begin());
            instancias.remove(other);
            Remove.remove(other);
            delete other;
        }
    }

    deinit();
    return 0;
}
END_OF_MAIN()

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

void create_plataform(int x, int y, int large)
{
    for (int i = 0; i < large; i++)
    {
        Block *b = new Block();
        b->x = x + (i * b->w);
        b->y = y;
        b->pushMe();
    }
};