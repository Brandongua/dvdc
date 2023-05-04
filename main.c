#include <SDL2/SDL.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "src/array.h"
#include "src/dvd.h"
#include "src/api.h"
#include "src/fc.h"
#include "src/globals.h"
#include "src/config.h"
#include "src/intarray.h"

//int multiplication(lua_State* L);
//
//
//TODO: add explosion effect when dvds collide

void create_dvd_module_object(lua_State* L){
    lua_newtable(L);
    lua_pushcfunction(L, dvd_exit);
    lua_setfield(L, -2, "exit");
    lua_pushcfunction(L, dvd_pop);
    lua_setfield(L, -2, "pop");
    lua_pushcfunction(L, dvd_add_dvd );
    lua_setfield(L, -2, "add");
    lua_pushcfunction(L, dvd_get_dvds );
    lua_setfield(L, -2, "get_all");
    lua_pushcfunction(L, dvd_get_dvd_count );
    lua_setfield(L, -2, "count");
    lua_pushcfunction(L, dvd_get_by_id);
    lua_setfield(L, -2, "get_by_id");
    lua_pushcfunction(L, dvd_change_logo_by_id);
    lua_setfield(L, -2, "change_logo_by_id");
    lua_pushcfunction(L, dvd_change_x_by_id);
    lua_setfield(L, -2, "change_x_by_id");
    lua_pushcfunction(L, dvd_change_y_by_id);
    lua_setfield(L, -2, "change_y_by_id");
    lua_pushcfunction(L, dvd_bounce_by_id);
    lua_setfield(L, -2, "bounce_by_id");
    lua_pushcfunction(L, dvd_set_pos_by_id);
    lua_setfield(L, -2, "set_pos_by_id");
    lua_pushcfunction(L, dvd_set_moving_by_id);
    lua_setfield(L, -2, "set_moving_by_id");
    lua_pushcfunction(L, dvd_change_xvel_by_id );
    lua_setfield(L, -2, "change_xvel_by_id");
    lua_pushcfunction(L, dvd_change_yvel_by_id );
    lua_setfield(L, -2, "change_yvel_by_id");
    lua_pushcfunction(L, dvd_set_info_to_render_by_id);
    lua_setfield(L, -2, "set_info_to_render_by_id");
    lua_pushcfunction(L, dvd_set_info_to_render_all);
    lua_setfield(L, -2, "set_info_to_render_all");
    lua_pushcfunction(L, dvd_set_default_info_to_render);
    lua_setfield(L, -2, "set_default_info_to_render");
    lua_pushcfunction(L, dvd_get_all_dvds);
    lua_setfield(L, -2, "get_all_dvds");
    lua_pushcfunction(L, dvd_register_on_click);
    lua_setfield(L, -2, "register_on_click");
    lua_pushinteger(L, DVD_RENDER_VELOCITY);
    lua_setfield(L, -2, "RENDER_VELOCITY");
    lua_pushinteger(L, DVD_RENDER_BOUNCE_COUNT);
    lua_setfield(L, -2, "RENDER_BOUNCE_COUNT");
    lua_pushinteger(L, DVD_RENDER_POSITION);
    lua_setfield(L, -2, "RENDER_POSITION");
    lua_pushinteger(L, DVD_RENDER_ID);
    lua_setfield(L, -2, "RENDER_ID");
    lua_setglobal(L, "dvd");
}

void create_sdl_module_object(lua_State* L){
    lua_newtable(L);
    lua_pushcfunction(L, sdl_get_window_size);
    lua_setfield(L, -2, "size");
    lua_pushcfunction(L, sdl_resize);
    lua_setfield(L, -2, "resize");
    lua_pushnumber(L, 500);
    lua_setfield(L, -2, "width");
    lua_pushnumber(L, 500);
    lua_setfield(L, -2, "height");
    lua_pushnumber(L, 60);
    lua_setfield(L, -2, "fps");
    lua_pushcfunction(L, sdl_set_fps);
    lua_setfield(L, -2, "set_fps");
    lua_pushcfunction(L, sdl_background_color);
    lua_setfield(L, -2, "background");
    lua_pushcfunction(L, sdl_render_text);
    lua_setfield(L, -2, "render_text");
    lua_pushinteger(L, SDL_SCANCODE_A + 1);
    lua_setfield(L, -2, "A");
    lua_pushinteger(L, SDL_SCANCODE_B + 1);
    lua_setfield(L, -2, "B");
    lua_pushinteger(L, SDL_SCANCODE_C + 1);
    lua_setfield(L, -2, "C");
    lua_pushinteger(L, SDL_SCANCODE_D + 1);
    lua_setfield(L, -2, "D");
    lua_pushinteger(L, SDL_SCANCODE_E + 1);
    lua_setfield(L, -2, "E");
    lua_pushinteger(L, SDL_SCANCODE_F + 1);
    lua_setfield(L, -2, "F");
    lua_pushinteger(L, SDL_SCANCODE_G + 1);
    lua_setfield(L, -2, "G");
    lua_pushinteger(L, SDL_SCANCODE_H + 1);
    lua_setfield(L, -2, "H");
    lua_pushinteger(L, SDL_SCANCODE_I + 1);
    lua_setfield(L, -2, "I");
    lua_pushinteger(L, SDL_SCANCODE_J + 1);
    lua_setfield(L, -2, "J");
    lua_pushinteger(L, SDL_SCANCODE_K + 1);
    lua_setfield(L, -2, "K");
    lua_pushinteger(L, SDL_SCANCODE_L + 1);
    lua_setfield(L, -2, "L");
    lua_pushinteger(L, SDL_SCANCODE_M + 1);
    lua_setfield(L, -2, "M");
    lua_pushinteger(L, SDL_SCANCODE_N + 1);
    lua_setfield(L, -2, "N");
    lua_pushinteger(L, SDL_SCANCODE_O + 1);
    lua_setfield(L, -2, "O");
    lua_pushinteger(L, SDL_SCANCODE_P + 1);
    lua_setfield(L, -2, "P");
    lua_pushinteger(L, SDL_SCANCODE_Q + 1);
    lua_setfield(L, -2, "Q");
    lua_pushinteger(L, SDL_SCANCODE_R + 1);
    lua_setfield(L, -2, "R");
    lua_pushinteger(L, SDL_SCANCODE_S + 1);
    lua_setfield(L, -2, "S");
    lua_pushinteger(L, SDL_SCANCODE_T + 1);
    lua_setfield(L, -2, "T");
    lua_pushinteger(L, SDL_SCANCODE_U + 1);
    lua_setfield(L, -2, "U");
    lua_pushinteger(L, SDL_SCANCODE_V + 1);
    lua_setfield(L, -2, "V");
    lua_pushinteger(L, SDL_SCANCODE_W + 1);
    lua_setfield(L, -2, "W");
    lua_pushinteger(L, SDL_SCANCODE_X + 1);
    lua_setfield(L, -2, "X");
    lua_pushinteger(L, SDL_SCANCODE_Y + 1);
    lua_setfield(L, -2, "Y");
    lua_pushinteger(L, SDL_SCANCODE_Z + 1);
    lua_setfield(L, -2, "Z");

    lua_pushinteger(L, SDL_SCANCODE_1 + 1);
    lua_setfield(L, -2, "1");
    lua_pushinteger(L, SDL_SCANCODE_2 + 1);
    lua_setfield(L, -2, "2");
    lua_pushinteger(L, SDL_SCANCODE_3 + 1);
    lua_setfield(L, -2, "3");
    lua_pushinteger(L, SDL_SCANCODE_4 + 1);
    lua_setfield(L, -2, "4");
    lua_pushinteger(L, SDL_SCANCODE_5 + 1);
    lua_setfield(L, -2, "5");
    lua_pushinteger(L, SDL_SCANCODE_6 + 1);
    lua_setfield(L, -2, "6");
    lua_pushinteger(L, SDL_SCANCODE_7 + 1);
    lua_setfield(L, -2, "7");
    lua_pushinteger(L, SDL_SCANCODE_8 + 1);
    lua_setfield(L, -2, "8");
    lua_pushinteger(L, SDL_SCANCODE_9 + 1);
    lua_setfield(L, -2, "9");
    lua_pushinteger(L, SDL_SCANCODE_0 + 1);
    lua_setfield(L, -2, "0");

    lua_pushinteger(L, SDL_SCANCODE_RETURN + 1);
    lua_setfield(L, -2, "RETURN");
    lua_pushinteger(L, SDL_SCANCODE_ESCAPE + 1);
    lua_setfield(L, -2, "ESCAPE");
    lua_pushinteger(L, SDL_SCANCODE_BACKSPACE + 1);
    lua_setfield(L, -2, "BACKSPACE");
    lua_pushinteger(L, SDL_SCANCODE_TAB + 1);
    lua_setfield(L, -2, "TAB");
    lua_pushinteger(L, SDL_SCANCODE_SPACE + 1);
    lua_setfield(L, -2, "SPACE");

    lua_pushinteger(L, SDL_SCANCODE_MINUS + 1);
    lua_setfield(L, -2, "MINUS");
    lua_pushinteger(L, SDL_SCANCODE_EQUALS + 1);
    lua_setfield(L, -2, "EQUALS");
    lua_pushinteger(L, SDL_SCANCODE_LEFTBRACKET + 1);
    lua_setfield(L, -2, "LEFTBRACKET");
    lua_pushinteger(L, SDL_SCANCODE_RIGHTBRACKET + 1);
    lua_setfield(L, -2, "RIGHTBRACKET");
    lua_pushinteger(L, SDL_SCANCODE_BACKSLASH + 1);
    lua_setfield(L, -2, "BACKSLASH");

    lua_pushinteger(L, SDL_SCANCODE_NONUSHASH + 1);
    lua_setfield(L, -2, "NONUSHASH");

    lua_pushinteger(L, SDL_SCANCODE_SEMICOLON + 1);
    lua_setfield(L, -2, "SEMICOLON");
    lua_pushinteger(L, SDL_SCANCODE_APOSTROPHE + 1);
    lua_setfield(L, -2, "APOSTROPHE");
    lua_pushinteger(L, SDL_SCANCODE_GRAVE + 1);
    lua_setfield(L, -2, "GRAVE");

    lua_pushinteger(L, SDL_SCANCODE_COMMA + 1);
    lua_setfield(L, -2, "COMMA");
    lua_pushinteger(L, SDL_SCANCODE_PERIOD + 1);
    lua_setfield(L, -2, "PERIOD");
    lua_pushinteger(L, SDL_SCANCODE_SLASH + 1);
    lua_setfield(L, -2, "SLASH");

    lua_pushinteger(L, SDL_SCANCODE_CAPSLOCK + 1);
    lua_setfield(L, -2, "CAPSLOCK");

 
    lua_pushinteger(L, SDL_SCANCODE_F1 + 1);
    lua_setfield(L, -2, "F1");
    lua_pushinteger(L, SDL_SCANCODE_F2 + 1);
    lua_setfield(L, -2, "F2");
    lua_pushinteger(L, SDL_SCANCODE_F3 + 1);
    lua_setfield(L, -2, "F3");
    lua_pushinteger(L, SDL_SCANCODE_F4 + 1);
    lua_setfield(L, -2, "F4");
    lua_pushinteger(L, SDL_SCANCODE_F5 + 1);
    lua_setfield(L, -2, "F5");
    lua_pushinteger(L, SDL_SCANCODE_F6 + 1);
    lua_setfield(L, -2, "F6");
    lua_pushinteger(L, SDL_SCANCODE_F7 + 1);
    lua_setfield(L, -2, "F7");
    lua_pushinteger(L, SDL_SCANCODE_F8 + 1);
    lua_setfield(L, -2, "F8");
    lua_pushinteger(L, SDL_SCANCODE_F9 + 1);
    lua_setfield(L, -2, "F9");
    lua_pushinteger(L, SDL_SCANCODE_F10 + 1);
    lua_setfield(L, -2, "F10");
    lua_pushinteger(L, SDL_SCANCODE_F11 + 1);
    lua_setfield(L, -2, "F11");
    lua_pushinteger(L, SDL_SCANCODE_F12 + 1);
    lua_setfield(L, -2, "F12");

    lua_pushinteger(L, SDL_SCANCODE_PRINTSCREEN + 1);
    lua_setfield(L, -2, "PRINTSCREEN");
    lua_pushinteger(L, SDL_SCANCODE_SCROLLLOCK + 1);
    lua_setfield(L, -2, "SCROLLLOCK");
    lua_pushinteger(L, SDL_SCANCODE_PAUSE + 1);
    lua_setfield(L, -2, "PAUSE");
    lua_pushinteger(L, SDL_SCANCODE_INSERT + 1);
    lua_setfield(L, -2, "INSERT");
 
    lua_pushinteger(L, SDL_SCANCODE_HOME + 1);
    lua_setfield(L, -2, "HOME");
    lua_pushinteger(L, SDL_SCANCODE_PAGEUP + 1);
    lua_setfield(L, -2, "PAGEUP");
    lua_pushinteger(L, SDL_SCANCODE_DELETE + 1);
    lua_setfield(L, -2, "DELETE");
    lua_pushinteger(L, SDL_SCANCODE_END + 1);
    lua_setfield(L, -2, "END");
    lua_pushinteger(L, SDL_SCANCODE_PAGEDOWN + 1);
    lua_setfield(L, -2, "PAGEDOWN");
    lua_pushinteger(L, SDL_SCANCODE_RIGHT + 1);
    lua_setfield(L, -2, "RIGHT");
    lua_pushinteger(L, SDL_SCANCODE_LEFT + 1);
    lua_setfield(L, -2, "LEFT");
    lua_pushinteger(L, SDL_SCANCODE_DOWN + 1);
    lua_setfield(L, -2, "DOWN");
    lua_pushinteger(L, SDL_SCANCODE_UP + 1);
    lua_setfield(L, -2, "UP");

    lua_pushinteger(L, SDL_SCANCODE_NUMLOCKCLEAR + 1);
    lua_setfield(L, -2, "NUMLOCKCLEAR");

    lua_pushinteger(L, SDL_SCANCODE_KP_DIVIDE + 1);
    lua_setfield(L, -2, "KP_DIVIDE");
    lua_pushinteger(L, SDL_SCANCODE_KP_MULTIPLY + 1);
    lua_setfield(L, -2, "KP_MULTIPLY");
    lua_pushinteger(L, SDL_SCANCODE_KP_MINUS + 1);
    lua_setfield(L, -2, "KP_MINUS");
    lua_pushinteger(L, SDL_SCANCODE_KP_PLUS + 1);
    lua_setfield(L, -2, "KP_PLUS");
    lua_pushinteger(L, SDL_SCANCODE_KP_ENTER + 1);
    lua_setfield(L, -2, "KP_ENTER");
    lua_pushinteger(L, SDL_SCANCODE_KP_1 + 1);
    lua_setfield(L, -2, "KP_1");
    lua_pushinteger(L, SDL_SCANCODE_KP_2 + 1);
    lua_setfield(L, -2, "KP_2");
    lua_pushinteger(L, SDL_SCANCODE_KP_3 + 1);
    lua_setfield(L, -2, "KP_3");
    lua_pushinteger(L, SDL_SCANCODE_KP_4 + 1);
    lua_setfield(L, -2, "KP_4");
    lua_pushinteger(L, SDL_SCANCODE_KP_5 + 1);
    lua_setfield(L, -2, "KP_5");
    lua_pushinteger(L, SDL_SCANCODE_KP_6 + 1);
    lua_setfield(L, -2, "KP_6");
    lua_pushinteger(L, SDL_SCANCODE_KP_7 + 1);
    lua_setfield(L, -2, "KP_7");
    lua_pushinteger(L, SDL_SCANCODE_KP_8 + 1);
    lua_setfield(L, -2, "KP_8");
    lua_pushinteger(L, SDL_SCANCODE_KP_9 + 1);
    lua_setfield(L, -2, "KP_9");
    lua_pushinteger(L, SDL_SCANCODE_KP_0 + 1);
    lua_setfield(L, -2, "KP_0");
    lua_pushinteger(L, SDL_SCANCODE_KP_PERIOD + 1);
    lua_setfield(L, -2, "KP_PERIOD");

    lua_pushinteger(L, SDL_SCANCODE_NONUSBACKSLASH + 1);
    lua_setfield(L, -2, "NONUSBACKSLASH");

    lua_pushinteger(L, SDL_SCANCODE_APPLICATION + 1);
    lua_setfield(L, -2, "APPLICATION");
    lua_pushinteger(L, SDL_SCANCODE_POWER + 1);
    lua_setfield(L, -2, "POWER");


    lua_pushinteger(L, SDL_SCANCODE_KP_EQUALS + 1);
    lua_setfield(L, -2, "KP_EQUALS");
    lua_pushinteger(L, SDL_SCANCODE_F13 + 1);
    lua_setfield(L, -2, "F13");
    lua_pushinteger(L, SDL_SCANCODE_F14 + 1);
    lua_setfield(L, -2, "F14");
    lua_pushinteger(L, SDL_SCANCODE_F15 + 1);
    lua_setfield(L, -2, "F15");
    lua_pushinteger(L, SDL_SCANCODE_F16 + 1);
    lua_setfield(L, -2, "F16");
    lua_pushinteger(L, SDL_SCANCODE_F17 + 1);
    lua_setfield(L, -2, "F17");
    lua_pushinteger(L, SDL_SCANCODE_F18 + 1);
    lua_setfield(L, -2, "F18");
    lua_pushinteger(L, SDL_SCANCODE_F19 + 1);
    lua_setfield(L, -2, "F19");
    lua_pushinteger(L, SDL_SCANCODE_F20 + 1);
    lua_setfield(L, -2, "F20");
    lua_pushinteger(L, SDL_SCANCODE_F21 + 1);
    lua_setfield(L, -2, "F21");
    lua_pushinteger(L, SDL_SCANCODE_F22 + 1);
    lua_setfield(L, -2, "F22");
    lua_pushinteger(L, SDL_SCANCODE_F23 + 1);
    lua_setfield(L, -2, "F23");
    lua_pushinteger(L, SDL_SCANCODE_F24 + 1);
    lua_setfield(L, -2, "F24");
    lua_pushinteger(L, SDL_SCANCODE_EXECUTE + 1);
    lua_setfield(L, -2, "EXECUTE");
    lua_pushinteger(L, SDL_SCANCODE_HELP + 1);
    lua_setfield(L, -2, "HELP");
    lua_pushinteger(L, SDL_SCANCODE_MENU + 1);
    lua_setfield(L, -2, "MENU");
    lua_pushinteger(L, SDL_SCANCODE_SELECT + 1);
    lua_setfield(L, -2, "SELECT");
    lua_pushinteger(L, SDL_SCANCODE_STOP + 1);
    lua_setfield(L, -2, "STOP");
    lua_pushinteger(L, SDL_SCANCODE_AGAIN + 1);
    lua_setfield(L, -2, "AGAIN");
    lua_pushinteger(L, SDL_SCANCODE_UNDO + 1);
    lua_setfield(L, -2, "UNDO");
    lua_pushinteger(L, SDL_SCANCODE_CUT + 1);
    lua_setfield(L, -2, "CUT");
    lua_pushinteger(L, SDL_SCANCODE_COPY + 1);
    lua_setfield(L, -2, "COPY");
    lua_pushinteger(L, SDL_SCANCODE_PASTE + 1);
    lua_setfield(L, -2, "PASTE");
    lua_pushinteger(L, SDL_SCANCODE_FIND + 1);
    lua_setfield(L, -2, "FIND");
    lua_pushinteger(L, SDL_SCANCODE_MUTE + 1);
    lua_setfield(L, -2, "MUTE");
    lua_pushinteger(L, SDL_SCANCODE_VOLUMEUP + 1);
    lua_setfield(L, -2, "VOLUMEUP");
    lua_pushinteger(L, SDL_SCANCODE_VOLUMEDOWN + 1);
    lua_setfield(L, -2, "VOLUMEDOWN");
    lua_pushinteger(L, SDL_SCANCODE_KP_COMMA + 1);
    lua_setfield(L, -2, "KP_COMMA");
    lua_pushinteger(L, SDL_SCANCODE_KP_EQUALSAS400 + 1);
    lua_setfield(L, -2, "KP_EQUALSAS400");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL1 + 1);
    lua_setfield(L, -2, "INTERNATIONAL1");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL2 + 1);
    lua_setfield(L, -2, "INTERNATIONAL2");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL3 + 1);
    lua_setfield(L, -2, "INTERNATIONAL3");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL4 + 1);
    lua_setfield(L, -2, "INTERNATIONAL4");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL5 + 1);
    lua_setfield(L, -2, "INTERNATIONAL5");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL6 + 1);
    lua_setfield(L, -2, "INTERNATIONAL6");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL7 + 1);
    lua_setfield(L, -2, "INTERNATIONAL7");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL8 + 1);
    lua_setfield(L, -2, "INTERNATIONAL8");
    lua_pushinteger(L, SDL_SCANCODE_INTERNATIONAL9 + 1);
    lua_setfield(L, -2, "INTERNATIONAL9");
    lua_pushinteger(L, SDL_SCANCODE_LANG1 + 1);
    lua_setfield(L, -2, "LANG1");
    lua_pushinteger(L, SDL_SCANCODE_LANG3 + 1);
    lua_setfield(L, -2, "LANG3");
    lua_pushinteger(L, SDL_SCANCODE_LANG4 + 1);
    lua_setfield(L, -2, "LANG4");
    lua_pushinteger(L, SDL_SCANCODE_LANG5 + 1);
    lua_setfield(L, -2, "LANG5");
    lua_pushinteger(L, SDL_SCANCODE_LANG6 + 1);
    lua_setfield(L, -2, "LANG6");
    lua_pushinteger(L, SDL_SCANCODE_LANG7 + 1);
    lua_setfield(L, -2, "LANG7");
    lua_pushinteger(L, SDL_SCANCODE_LANG8 + 1);
    lua_setfield(L, -2, "LANG8");
    lua_pushinteger(L, SDL_SCANCODE_LANG9 + 1);
    lua_setfield(L, -2, "LANG9");
    lua_pushinteger(L, SDL_SCANCODE_ALTERASE + 1);
    lua_setfield(L, -2, "ALTERASE");
    lua_pushinteger(L, SDL_SCANCODE_SYSREQ + 1);
    lua_setfield(L, -2, "SYSREQ");
    lua_pushinteger(L, SDL_SCANCODE_CANCEL + 1);
    lua_setfield(L, -2, "CANCEL");
    lua_pushinteger(L, SDL_SCANCODE_CLEAR + 1);
    lua_setfield(L, -2, "CLEAR");
    lua_pushinteger(L, SDL_SCANCODE_PRIOR + 1);
    lua_setfield(L, -2, "PRIOR");
    lua_pushinteger(L, SDL_SCANCODE_RETURN2 + 1);
    lua_setfield(L, -2, "RETURN2");
    lua_pushinteger(L, SDL_SCANCODE_SEPARATOR + 1);
    lua_setfield(L, -2, "SEPARATOR");
    lua_pushinteger(L, SDL_SCANCODE_OUT + 1);
    lua_setfield(L, -2, "OUT");
    lua_pushinteger(L, SDL_SCANCODE_OPER + 1);
    lua_setfield(L, -2, "OPER");
    lua_pushinteger(L, SDL_SCANCODE_CLEARAGAIN + 1);
    lua_setfield(L, -2, "CLEARAGAIN");
    lua_pushinteger(L, SDL_SCANCODE_CRSEL + 1);
    lua_setfield(L, -2, "CRSEL");
    lua_pushinteger(L, SDL_SCANCODE_EXSEL + 1);
    lua_setfield(L, -2, "EXSEL");

    lua_pushinteger(L, SDL_SCANCODE_KP_00 + 1);
    lua_setfield(L, -2, "KP_00");
    lua_pushinteger(L, SDL_SCANCODE_KP_000 + 1);
    lua_setfield(L, -2, "KP_000");
    lua_pushinteger(L, SDL_SCANCODE_THOUSANDSSEPARATOR + 1);
    lua_setfield(L, -2, "THOUSANDSSEPARATOR");
    lua_pushinteger(L, SDL_SCANCODE_DECIMALSEPARATOR + 1);
    lua_setfield(L, -2, "DECIMALSEPARATOR");
    lua_pushinteger(L, SDL_SCANCODE_CURRENCYUNIT + 1);
    lua_setfield(L, -2, "CURRENCYUNIT");
    lua_pushinteger(L, SDL_SCANCODE_CURRENCYSUBUNIT + 1);
    lua_setfield(L, -2, "CURRENCYSUBUNIT");
    lua_pushinteger(L, SDL_SCANCODE_KP_LEFTPAREN + 1);
    lua_setfield(L, -2, "KP_LEFTPAREN");
    lua_pushinteger(L, SDL_SCANCODE_KP_RIGHTPAREN + 1);
    lua_setfield(L, -2, "KP_RIGHTPAREN");
    lua_pushinteger(L, SDL_SCANCODE_KP_LEFTBRACE + 1);
    lua_setfield(L, -2, "KP_LEFTBRACE");
    lua_pushinteger(L, SDL_SCANCODE_KP_RIGHTBRACE + 1);
    lua_setfield(L, -2, "KP_RIGHTBRACE");
    lua_pushinteger(L, SDL_SCANCODE_KP_TAB + 1);
    lua_setfield(L, -2, "KP_TAB");
    lua_pushinteger(L, SDL_SCANCODE_KP_BACKSPACE + 1);
    lua_setfield(L, -2, "KP_BACKSPACE");
    lua_pushinteger(L, SDL_SCANCODE_KP_A + 1);
    lua_setfield(L, -2, "KP_A");
    lua_pushinteger(L, SDL_SCANCODE_KP_B + 1);
    lua_setfield(L, -2, "KP_B");
    lua_pushinteger(L, SDL_SCANCODE_KP_C + 1);
    lua_setfield(L, -2, "KP_C");
    lua_pushinteger(L, SDL_SCANCODE_KP_D + 1);
    lua_setfield(L, -2, "KP_D");
    lua_pushinteger(L, SDL_SCANCODE_KP_E + 1);
    lua_setfield(L, -2, "KP_E");
    lua_pushinteger(L, SDL_SCANCODE_KP_F + 1);
    lua_setfield(L, -2, "KP_F");
    lua_pushinteger(L, SDL_SCANCODE_KP_XOR + 1);
    lua_setfield(L, -2, "KP_XOR");
    lua_pushinteger(L, SDL_SCANCODE_KP_POWER + 1);
    lua_setfield(L, -2, "KP_POWER");
    lua_pushinteger(L, SDL_SCANCODE_KP_PERCENT + 1);
    lua_setfield(L, -2, "KP_PERCENT");
    lua_pushinteger(L, SDL_SCANCODE_KP_LESS + 1);
    lua_setfield(L, -2, "KP_LESS");
    lua_pushinteger(L, SDL_SCANCODE_KP_GREATER + 1);
    lua_setfield(L, -2, "KP_GREATER");
    lua_pushinteger(L, SDL_SCANCODE_KP_AMPERSAND + 1);
    lua_setfield(L, -2, "KP_AMPERSAND");
    lua_pushinteger(L, SDL_SCANCODE_KP_DBLAMPERSAND + 1);
    lua_setfield(L, -2, "KP_DBLAMPERSAND");
    lua_pushinteger(L, SDL_SCANCODE_KP_VERTICALBAR + 1);
    lua_setfield(L, -2, "KP_VERTICALBAR");
    lua_pushinteger(L, SDL_SCANCODE_KP_DBLVERTICALBAR + 1);
    lua_setfield(L, -2, "KP_DBLVERTICALBAR");
    lua_pushinteger(L, SDL_SCANCODE_KP_COLON + 1);
    lua_setfield(L, -2, "KP_COLON");
    lua_pushinteger(L, SDL_SCANCODE_KP_HASH + 1);
    lua_setfield(L, -2, "KP_HASH");
    lua_pushinteger(L, SDL_SCANCODE_KP_SPACE + 1);
    lua_setfield(L, -2, "KP_SPACE");
    lua_pushinteger(L, SDL_SCANCODE_KP_AT + 1);
    lua_setfield(L, -2, "KP_AT");
    lua_pushinteger(L, SDL_SCANCODE_KP_EXCLAM + 1);
    lua_setfield(L, -2, "KP_EXCLAM");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMSTORE + 1);
    lua_setfield(L, -2, "KP_MEMSTORE");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMRECALL + 1);
    lua_setfield(L, -2, "KP_MEMRECALL");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMCLEAR + 1);
    lua_setfield(L, -2, "KP_MEMCLEAR");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMADD + 1);
    lua_setfield(L, -2, "KP_MEMADD");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMSUBTRACT + 1);
    lua_setfield(L, -2, "KP_MEMSUBTRACT");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMMULTIPLY + 1);
    lua_setfield(L, -2, "KP_MEMMULTIPLY");
    lua_pushinteger(L, SDL_SCANCODE_KP_MEMDIVIDE + 1);
    lua_setfield(L, -2, "KP_MEMDIVIDE");
    lua_pushinteger(L, SDL_SCANCODE_KP_PLUSMINUS + 1);
    lua_setfield(L, -2, "KP_PLUSMINUS");
    lua_pushinteger(L, SDL_SCANCODE_KP_CLEAR + 1);
    lua_setfield(L, -2, "KP_CLEAR");
    lua_pushinteger(L, SDL_SCANCODE_KP_CLEARENTRY + 1);
    lua_setfield(L, -2, "KP_CLEARENTRY");
    lua_pushinteger(L, SDL_SCANCODE_KP_BINARY + 1);
    lua_setfield(L, -2, "KP_BINARY");
    lua_pushinteger(L, SDL_SCANCODE_KP_OCTAL + 1);
    lua_setfield(L, -2, "KP_OCTAL");
    lua_pushinteger(L, SDL_SCANCODE_KP_DECIMAL + 1);
    lua_setfield(L, -2, "KP_DECIMAL");
    lua_pushinteger(L, SDL_SCANCODE_KP_HEXADECIMAL + 1);
    lua_setfield(L, -2, "KP_HEXADECIMAL");

    lua_pushinteger(L, SDL_SCANCODE_LCTRL + 1);
    lua_setfield(L, -2, "LCTRL");
    lua_pushinteger(L, SDL_SCANCODE_LSHIFT + 1);
    lua_setfield(L, -2, "LSHIFT");
    lua_pushinteger(L, SDL_SCANCODE_LALT + 1);
    lua_setfield(L, -2, "LALT");
    lua_pushinteger(L, SDL_SCANCODE_LGUI + 1);
    lua_setfield(L, -2, "LGUI");
    lua_pushinteger(L, SDL_SCANCODE_RCTRL + 1);
    lua_setfield(L, -2, "RCTRL");
    lua_pushinteger(L, SDL_SCANCODE_RSHIFT + 1);
    lua_setfield(L, -2, "RSHIFT");
    lua_pushinteger(L, SDL_SCANCODE_RALT + 1);
    lua_setfield(L, -2, "RALT");
    lua_pushinteger(L, SDL_SCANCODE_RGUI + 1);
    lua_setfield(L, -2, "RGUI");
    lua_pushinteger(L, SDL_SCANCODE_MODE + 1);
    lua_setfield(L, -2, "MODE");

    lua_pushinteger(L, SDL_SCANCODE_AUDIONEXT + 1);
    lua_setfield(L, -2, "AUDIONEXT");
    lua_pushinteger(L, SDL_SCANCODE_AUDIOPREV + 1);
    lua_setfield(L, -2, "AUDIOPREV");
    lua_pushinteger(L, SDL_SCANCODE_AUDIOSTOP + 1);
    lua_setfield(L, -2, "AUDIOSTOP");
    lua_pushinteger(L, SDL_SCANCODE_AUDIOPLAY + 1);
    lua_setfield(L, -2, "AUDIOPLAY");
    lua_pushinteger(L, SDL_SCANCODE_AUDIOMUTE + 1);
    lua_setfield(L, -2, "AUDIOMUTE");
    lua_pushinteger(L, SDL_SCANCODE_MEDIASELECT + 1);
    lua_setfield(L, -2, "MEDIASELECT");
    lua_pushinteger(L, SDL_SCANCODE_WWW + 1);
    lua_setfield(L, -2, "WWW");
    lua_pushinteger(L, SDL_SCANCODE_MAIL + 1);
    lua_setfield(L, -2, "MAIL");
    lua_pushinteger(L, SDL_SCANCODE_CALCULATOR + 1);
    lua_setfield(L, -2, "CALCULATOR");
    lua_pushinteger(L, SDL_SCANCODE_COMPUTER + 1);
    lua_setfield(L, -2, "COMPUTER");
    lua_pushinteger(L, SDL_SCANCODE_AC_SEARCH + 1);
    lua_setfield(L, -2, "AC_SEARCH");
    lua_pushinteger(L, SDL_SCANCODE_AC_HOME + 1);
    lua_setfield(L, -2, "AC_HOME");
    lua_pushinteger(L, SDL_SCANCODE_AC_BACK + 1);
    lua_setfield(L, -2, "AC_BACK");
    lua_pushinteger(L, SDL_SCANCODE_AC_FORWARD + 1);
    lua_setfield(L, -2, "AC_FORWARD");
    lua_pushinteger(L, SDL_SCANCODE_AC_STOP + 1);
    lua_setfield(L, -2, "AC_STOP");
    lua_pushinteger(L, SDL_SCANCODE_AC_REFRESH + 1);
    lua_setfield(L, -2, "AC_REFRESH");
    lua_pushinteger(L, SDL_SCANCODE_AC_BOOKMARKS + 1);
    lua_setfield(L, -2, "AC_BOOKMARKS");

    lua_pushinteger(L, SDL_SCANCODE_BRIGHTNESSDOWN + 1);
    lua_setfield(L, -2, "BRIGHTNESSDOWN");
    lua_pushinteger(L, SDL_SCANCODE_BRIGHTNESSUP + 1);
    lua_setfield(L, -2, "BRIGHTNESSUP");
    lua_pushinteger(L, SDL_SCANCODE_DISPLAYSWITCH + 1);
    lua_setfield(L, -2, "DISPLAYSWITCH");
    lua_pushinteger(L, SDL_SCANCODE_KBDILLUMTOGGLE + 1);
    lua_setfield(L, -2, "KBDILLUMTOGGLE");
    lua_pushinteger(L, SDL_SCANCODE_KBDILLUMDOWN + 1);
    lua_setfield(L, -2, "KBDILLUMDOWN");
    lua_pushinteger(L, SDL_SCANCODE_KBDILLUMUP + 1);
    lua_setfield(L, -2, "KBDILLUMUP");
    lua_pushinteger(L, SDL_SCANCODE_EJECT + 1);
    lua_setfield(L, -2, "EJECT");
    lua_pushinteger(L, SDL_SCANCODE_SLEEP + 1);
    lua_setfield(L, -2, "SLEEP");

    lua_pushinteger(L, SDL_SCANCODE_APP1 + 1);
    lua_setfield(L, -2, "APP1");
    lua_pushinteger(L, SDL_SCANCODE_APP2 + 1);
    lua_setfield(L, -2, "APP2");

    lua_pushinteger(L, SDL_SCANCODE_AUDIOREWIND + 1);
    lua_setfield(L, -2, "AUDIOREWIND");
    lua_pushinteger(L, SDL_SCANCODE_AUDIOFASTFORWARD + 1);
    lua_setfield(L, -2, "AUDIOFASTFORWARD");

    lua_pushinteger(L, SDL_SCANCODE_SOFTLEFT + 1);
    lua_setfield(L, -2, "SOFTLEFT");

    lua_pushinteger(L, SDL_SCANCODE_SOFTRIGHT + 1);
    lua_setfield(L, -2, "SOFTRIGHT");

    lua_pushinteger(L, SDL_SCANCODE_CALL + 1);
    lua_setfield(L, -2, "CALL");
    lua_pushinteger(L, SDL_SCANCODE_ENDCALL + 1);
    lua_setfield(L, -2, "ENDCALL");
 
    lua_pushinteger(L, SDL_NUM_SCANCODES + 1);
    lua_setfield(L, -2, "NUM_SCANCODES");

    lua_setglobal(L, "sdl");
}

void create_this_module_object(lua_State* L){
    lua_newtable(L);
    lua_pushcfunction(L, this_register_on_click);
    lua_setfield(L, -2, "register_on_click");
    lua_pushcfunction(L, this_register_on_right_click);
    lua_setfield(L, -2, "register_on_right_click");
    lua_pushcfunction(L, this_register_on_middle_click);
    lua_setfield(L, -2, "register_on_middle_click");
    lua_pushcfunction(L, this_register_on_bounce);
    lua_setfield(L, -2, "register_on_bounce");
    lua_pushcfunction(L, this_register_on_render);
    lua_setfield(L, -2, "register_on_render");
    lua_pushcfunction(L, this_register_on_hover);
    lua_setfield(L, -2, "register_on_hover");
    lua_pushcfunction(L, this_register_on_key);
    lua_setfield(L, -2, "register_on_key");
    lua_setglobal(L, "this");
}

int main(int argc, char ** argv) {
    srand(time(NULL));


    initDvdArray(&dvds, 0);
    initIntArray(&on_click_callbacks, 0);
    initIntArray(&on_right_click_callbacks, 0);
    initIntArray(&on_bounce_callbacks, 0);
    initIntArray(&on_middle_click_callbacks, 0);
    initIntArray(&on_key_callbacks, 0);
    initIntArray(&on_render_callbacks, 0);
    initIntArray(&on_dvd_hover_callbacks, 0);
    initIntArray(&on_dvd_click_callbacks, 0);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    create_dvd_module_object(L);
    create_sdl_module_object(L);
    create_this_module_object(L);

    // Work with lua API

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }


    win = SDL_CreateWindow("DVDScreen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    TTF_Init();
    FC_Font* mainInfoFont = FC_CreateFont();
    FC_LoadFont(mainInfoFont, rend, "/usr/share/fonts/ubuntu/Ubuntu-M.ttf", 15, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    FC_Font* dvdInfoFont = FC_CreateFont();
    FC_LoadFont(dvdInfoFont, rend, "/usr/share/fonts/TTF/Arial.TTF", 10, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

    if(!mainInfoFont){
        printf("%s\n", "Font not found");
        return 1;
    }

    char systemPath[30];
    globalConfigPath(systemPath);
    DIR* d;
    struct dirent* dir;
    d = opendir(systemPath);
    if(d){
        while((dir = readdir(d)) != NULL){
            if(luaL_dofile(L,strcat(systemPath,dir->d_name)) == LUA_OK){
                lua_pop(L, lua_gettop(L));
            }
            else{
                fprintf(stderr, "%s\n", lua_tostring(L, -1));
            }
            globalConfigPath(systemPath);
        }
        closedir(d);
    }

    char configPath[200];
    memset(configPath, 0, 200);

    getConfigPath(configPath);

    if( luaL_dofile(L,strcat(configPath, "config.lua")) == LUA_OK){
        lua_pop(L, lua_gettop(L));
    }
    else{
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        return 1;
    }

    lua_getglobal(L, "sdl");
    lua_getfield(L, -1, "fps");
    fps = lua_tointeger(L, -1);
    if(fps == 0) fps = 60;

    while(running == 1){
        SDL_Event event;

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:{
                    lua_getglobal(L, "on_exit");
                    lua_pcall(L, 0, 0, 0);
                    running = 0;
                    break;
                }

                case  SDL_KEYDOWN: {
                    int length;
                    const Uint8* state = SDL_GetKeyboardState(NULL);
                    SDL_GetKeyboardState(&length);

                    for(int i = 0; i < on_key_callbacks.used; i++){
                        lua_rawgeti(L, LUA_REGISTRYINDEX, on_key_callbacks.array[i]);
                        lua_createtable(L, length, 0);
                        for(int i = 0; i < length; i++){
                            lua_pushnumber(L, i + 1);
                            lua_pushinteger(L, state[i]);
                            lua_settable(L, -3);
                        }
                        lua_pcall(L, 1, 0, 0);
                    }
                    break;
                    
                    //printf("%d\n", state[SDL_SCANCODE_3]);
                }

                case SDL_MOUSEBUTTONDOWN:{
                    int x, y;
                    Uint32 buttons = SDL_GetMouseState(&x, &y);
                    int override_normal_clicking = 0;
                    if(on_dvd_click_callbacks.used > 0){
                        for(int i = 0; i < dvds.used; i++){
                            Dvd* d = &dvds.array[i];
                            if(mouseX >= d->x && mouseX <= d->x + d->width && mouseY >= d->y && mouseY <= d->y + d->height){
                                for(int i = 0; i < on_dvd_click_callbacks.used; i++){
                                    lua_rawgeti(L, LUA_REGISTRYINDEX, on_dvd_click_callbacks.array[i]);
                                    //bitshifting so that:
                                        //left click = 0
                                        //middle click = 1
                                        //right click = 2
                                    lua_pushinteger(L, buttons >> 1);
                                    lua_pushinteger(L, d->id);
                                    dvd_create_lua_table(d, L);
                                    lua_pcall(L, 3, 1, 0);

                                    //overriding takes priority over not overriding ie:
                                        //if one function requests override, and another doesnt,
                                        //it will be garanteed to override.
                                    if(override_normal_clicking == 0)
                                        override_normal_clicking = lua_tointeger(L, -1);
                                }
                            }
                        }
                    }
                    if(override_normal_clicking == 1)
                        break;

                    switch(buttons){
                        case SDL_BUTTON_LMASK:{
                            for(int i = 0; i < on_click_callbacks.used; i++){
                                lua_rawgeti(L, LUA_REGISTRYINDEX, on_click_callbacks.array[i]);
                                lua_pushinteger(L, x);
                                lua_pushinteger(L, y);
                                lua_pcall(L, 2, 1, 0);
                            }
                            break;
                        }
                        case SDL_BUTTON_RMASK: {
                            for(int i = 0; i < on_right_click_callbacks.used; i++){
                                lua_rawgeti(L, LUA_REGISTRYINDEX, on_right_click_callbacks.array[i]);
                                lua_pushinteger(L, x);
                                lua_pushinteger(L, y);
                                lua_pcall(L, 2, 1, 0);
                            }
                            break;
                        }
                        case SDL_BUTTON_MIDDLE: {
                            for(int i = 0; i < on_right_click_callbacks.used; i++){
                                lua_rawgeti(L, LUA_REGISTRYINDEX, on_middle_click_callbacks.array[i]);
                                lua_pushinteger(L, x);
                                lua_pushinteger(L, y);
                                lua_pcall(L, 2, 1, 0);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }

        SDL_RenderClear(rend);


        for(int i = 0; i < dvds.used; i++){
            if(dvds.array[i].initialized == 0) dvd_init(&dvds.array[i], rend);

            Dvd* d = &dvds.array[i];
            dvd_render(d, rend);
            dvd_render_text(d, rend, dvdInfoFont);

            if(mouseX >= d->x && mouseX <= d->x + d->width && mouseY >= d->y && mouseY <= d->y + d->height){
                for(int i = 0; i < on_dvd_hover_callbacks.used; i++){
                    lua_rawgeti(L, LUA_REGISTRYINDEX, on_dvd_hover_callbacks.array[i]);
                    lua_pushinteger(L, d->id);
                    dvd_create_lua_table(d, L);
                    lua_pcall(L, 2, 0, 0);
                }
            }

            dvd_move(d);

            int bounce = dvd_is_touching_wall(d, win);
            if(bounce != 0){
                d->bounces++;
                const char* axis = bounce == 1 ? "x" : "y";
                for(int i = 0; i < on_bounce_callbacks.used; i++){
                    lua_rawgeti(L, LUA_REGISTRYINDEX, on_bounce_callbacks.array[i]);
                    lua_pushstring(L, axis);
                    lua_pushinteger(L, d->id);
                    dvd_create_lua_table(d, L);
                    lua_pcall(L, 3, 0, 0);
                }
            }

            if(dvd_is_in_wall(d, win)){
                d->x = 1;
                d->y = 1;
            }
        }

        for(int i = 0; i < on_render_callbacks.used; i++){
            lua_rawgeti(L, LUA_REGISTRYINDEX, on_render_callbacks.array[i]);
            lua_pcall(L, 0, 0, 0);
        }

        FC_Draw(mainInfoFont, rend, 0, 0, "%d", dvds.used);
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / fps);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);

    SDL_Quit();

    lua_close(L);


    return 0;
}

