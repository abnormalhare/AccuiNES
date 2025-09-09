#pragma once

#include <SDL_error.h>
#include <SDL_events.h>
#include <SDL_keyboard.h>
#include <SDL_keycode.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#ifdef WINDOWS
#include <SDL_main.h>
#endif
#include <SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern TTF_Font *font;