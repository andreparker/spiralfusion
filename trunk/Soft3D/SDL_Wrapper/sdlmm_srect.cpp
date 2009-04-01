/*
 * SDLmm - a C++ wrapper for SDL and related libraries
 * Copyright © 2001 David Hedbor <david@hedbor.org>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

// The SDLmm::SRect class

#include "sdlmm_config.h"
RCSID("$Id: sdlmm_srect.cpp,v 1.7 2001/07/06 20:30:38 neotron Exp $");

#include <SDL.h>
#include "sdlmm_srect.h"

namespace SDLmm {
  SRect::SRect() {
    x = y = w = h = 0;
  }

  SRect::SRect(const SRect& rect) {
    x = rect.x; y = rect.y;
    w = rect.w; h = rect.h;
  }

  SRect::SRect(const SDL_Rect& rect) {
    x = rect.x; y = rect.y;
    w = rect.w; h = rect.h;
  }

  SRect::SRect(Sint16 nx, Sint16 ny, Uint16 nw, Uint16 nh) {
    x = nx; y = ny; w = nw; h = nh;
  }

  SRect::SRect(Uint16 nw, Uint16 nh) {
    x = y = 0;
    w = nw; h = nh;
  }

  SRect::SRect(const SPoint &point) {
    x = point.x; y = point.y;
    w = 0;    h = 0;
  }
  SRect::SRect(const SPoint &point, Uint16 nw, Uint16 nh) {
    x = point.x; y = point.y;
    w = nw;   h = nh;
  }

  SRect::SRect(const SPoint &upper_left_point,
	       const SPoint &bottom_right_point) {
    ASSERT(upper_left_point <= bottom_right_point);
    x = upper_left_point.x; y = upper_left_point.y;
    w = bottom_right_point.x - upper_left_point.x;
    h = bottom_right_point.y - upper_left_point.y;
  }
}

