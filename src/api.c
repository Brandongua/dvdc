#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <string.h>
#include <stdlib.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <SDL2/SDL.h>

#include "api.h"
#include "dvd.h"
#include "array.h"
#include "globals.h"
#include "intarray.h"

int dvd_exit(lua_State* L){
    running = 0;
    return 1;
}

int dvd_pop(lua_State* L){
    if(dvds.len > 0){
        popDvdArrayItem(&dvds);
    }
    return 1;
}

int dvd_add_dvd(lua_State* L){
    int x = lua_tointeger(L, 1);
    int y = lua_tointeger(L, 2);
    const char* file_path = lua_tostring(L, 3);
    if(x == -1) x = rand() % 50;
    if(y == -1) y = rand() % 50;
    Dvd d = request_dvd_init(x, y, 0, 0, file_path ? file_path : "DVD_White.png"); //I would like to put NULL, NULL instead of 0, 0, but that gives warnings
    if(insertDvdArray(&dvds, d) == 1){
	return 2;
    }
    dvd_create_lua_table(&d, L);
    return 1;
}

int dvd_get_dvds(lua_State* L){
    lua_newtable(L);
    for(int i = 0; i < dvds.used; i++){
	Dvd d = dvds.array[i];
	lua_pushinteger(L, i);
	dvd_create_lua_table(&d, L);
	lua_settable(L, -3);
    }
    return 1;
}

int dvd_get_dvd_count(lua_State* L){
    lua_pushinteger(L, dvds.used);
    return 1;
}

int dvd_get_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    dvd_create_lua_table(d, L);
    return 1;
}

int dvd_change_logo_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized){
        dvd_init(d, rend);
    }
    const char* file_path = lua_tostring(L, 2);
    if(file_path == NULL){
        dvd_change_logo(d, rend, dvd_file_paths[rand() % sizeof(dvd_file_paths[0])]);
    }
    else{
        dvd_change_logo(d, rend, file_path);
    }
    return 1;
}

int dvd_change_x_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL){
        return 2;
    }
    if(!d->initialized)
        dvd_init(d, rend);
    int x = lua_tointeger(L, 2);
    d->x = x;
    return 1;
}

int dvd_change_y_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL){
        return 2;
    }
    if(!d->initialized)
        dvd_init(d, rend);
    int y = lua_tointeger(L, 2);
    d->y = y;
    return 1;
}

int dvd_bounce_by_id(lua_State *L){
    int id =  lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    const char* axis = lua_tostring(L, 2);
    if(axis == NULL)
        return 2;
    if(strcmp(axis, "x") == 0){
        dvd_bounce_x(d);
    }
    else if(strcmp(axis, "y") == 0){
        dvd_bounce_y(d);
    }
    else if(strcmp(axis, "xy") == 0){
        dvd_bounce_y(d);
        dvd_bounce_x(d);
    }
    return 1;
}

int dvd_set_pos_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL){
        return 2;
    }
    if(!d->initialized)
        dvd_init(d, rend);
    double y = lua_tonumber(L, 2);
    d->y = y;
    double x = lua_tonumber(L, 2);
    d->x = x;
    return 1;
}

int dvd_set_moving_by_id(lua_State *L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    int can_move = lua_toboolean(L, 2);
    d->canMove = can_move;
    return 1;
}

int dvd_change_xvel_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    int amount = lua_tointeger(L, 2);
    d->xVel += amount;
    return 1;
}

int dvd_change_yvel_by_id(lua_State* L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    int amount = lua_tointeger(L, 2);
    d->yVel += amount;
    return 1;
}

int dvd_set_info_to_render_by_id(lua_State *L){
    int id = lua_tointeger(L, 1);
    Dvd* d = get_dvd_by_id(id);
    if(d == NULL)
        return 2;
    if(!d->initialized)
        dvd_init(d, rend);
    int bitField = lua_tointeger(L, 2);
    d->infoToRender = bitField;
    return 1;
}

int dvd_set_info_to_render_all(lua_State *L){
    int info = lua_tointeger(L, 1);
    for(int i = 0; i < dvds.used; i++){
        if(dvds.array[i].initialized == 0)
            continue;
        dvds.array[i].infoToRender = info;
    }
    return 1;
}

int dvd_set_default_info_to_render(lua_State *L){
    int info = lua_tointeger(L, 1);
    DVD_DEFAULT_RENDER = info;
    return 1;
}

int dvd_get_all_dvds(lua_State* L){
    lua_newtable(L);
    for(int i = 0; i < dvds.len; i++){
        if(dvds.array[i].initialized == 0){
            continue;
        }
        lua_pushnumber(L, i + 1);
        dvd_create_lua_table(&(dvds.array[i]), L);
        lua_settable(L, -3);
    }
    return 1;
}

int dvd_register_on_click(lua_State *L){
    insertIntArray(&on_dvd_click_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int sdl_get_window_size(lua_State *L){
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    lua_newtable(L);
    lua_pushstring(L, "width");
    lua_pushnumber(L, w);
    lua_settable(L, -3);
    lua_pushstring(L, "height");
    lua_pushnumber(L, h);
    lua_settable(L, -3);
    return 1;
}

int sdl_resize(lua_State* L){
    int newW = lua_tointeger(L, 1);
    int newH = lua_tointeger(L, 2);
    int curW, curH;
    SDL_GetWindowSize(win, &curW, &curH);
    if(newW == 0){
        newW = curW;
    }
    if(newH == 0){
        newH = curH;
    }
    SDL_SetWindowSize(win, newW, newH);

    //set the values sdl.width and sdl.height
    lua_getglobal(L, "sdl");
    lua_pushnumber(L, newW);
    lua_setfield(L, -2, "width");
    lua_pushnumber(L, newH);
    lua_setfield(L, -2, "height");

    WIDTH = newW;
    HEIGHT = newH;

    return 1;
}

int sdl_set_fps(lua_State* L){
    int newFps = lua_tointeger(L, 1);
    if(newFps == 0){
	return 2;
    }
    fps = newFps;
    lua_getglobal(L, "sdl");
    lua_pushnumber(L, fps);
    lua_setfield(L, -2, "fps");
    return 1;
}

int sdl_background_color(lua_State* L){
    int r = lua_tointeger(L, 1);
    int g = lua_tointeger(L, 2);
    int b = lua_tointeger(L, 3);
    int a = lua_tointeger(L, 4);
    if(r > 255 || g > 255 || b > 255 || a > 255){
	return 2;
    }
    SDL_SetRenderDrawColor(rend, r, g, b, a);
    return 1;
}

int sdl_render_text(lua_State *L){
    int x = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);
    if(!lua_istable(L, 4)){
        return 2;
    }
    lua_getfield(L, 4, "font");
    const char* font = lua_tostring(L, -1);
    if(font == NULL){
        printf("%s\n", "Font is null");
        return 2;
    }
    lua_getfield(L, 4, "size");
    int size = lua_tointeger(L, -1);
    if(size == 0)
        size = 1;
    lua_getfield(L, 4, "r");
    Uint8 r = lua_tointeger(L, -1);
    lua_getfield(L, 4, "g");
    Uint8 g = lua_tointeger(L, -1);
    lua_getfield(L, 4, "b");
    Uint8 b = lua_tointeger(L, -1);
    lua_getfield(L, 4, "a");
    Uint8 a = lua_tointeger(L, -1);
    FC_Font* fc_font = FC_CreateFont();
    FC_LoadFont(fc_font, rend, font, size, FC_MakeColor(r, g, b, a), TTF_STYLE_NORMAL);
    if(lua_istable(L, 1)){
        lua_rawgeti(L, 1, 1);
        const char* format = lua_tostring(L, -1);
        lua_rawgeti(L, 1, 2);
        const char* text = lua_tostring(L, -1);
        FC_Draw(fc_font, rend, x, y, format, text);
    }
    else{
        const char* text = lua_tostring(L, 1);
        if(text == NULL){
            printf( "%s\n", "Text is null");
            return 2;
        }
        FC_Draw(fc_font, rend, x, y, "%s", text);
    }

    return 1;
}

int this_register_on_click(lua_State* L){

    insertIntArray(&on_click_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_right_click(lua_State* L){

    insertIntArray(&on_right_click_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_bounce(lua_State *L){
    insertIntArray(&on_bounce_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_middle_click(lua_State* L){
    insertIntArray(&on_middle_click_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_render(lua_State *L){
    insertIntArray(&on_render_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_hover(lua_State *L){
    insertIntArray(&on_dvd_hover_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}

int this_register_on_key(lua_State *L){
    insertIntArray(&on_key_callbacks, luaL_ref(L, LUA_REGISTRYINDEX));
    return 1;
}
