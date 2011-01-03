/* broadcast -- creating broadcast messages.
 * Copyright (C) 2010-2011 The Zatacka X development team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "broadcast.h"

/**
 * Constructs a broadcast message. It may consist of up to three "parts".
 * When numbers 1 to MAX_PLAYERS are used, the number is exchanged for a
 * "PlayerN" string, and colored according the current player color.
 *
 * @param msg Message string to be displayed.
 * @param pcolors An array of the current player colors.
 * @return The constructed broadcast message.
 */
SDL_Surface *makeBroadcast(char *msg, SDL_Color pcolors[MAX_PLAYERS])
{
    SDL_Surface *broadcast;
    unsigned int i;
    char *strings[BROADC_PARTS];
    SDL_Surface *parts[BROADC_PARTS];
    unsigned int width = 0;

    /* Split message string */
    strings[0] = strtok(msg, ";");
    for (i = 1; (strings[i] = strtok(NULL, ";")) != NULL; ++i) {}

    for (i = 0; strings[i] != NULL && i < BROADC_PARTS; ++i) {
        
        char pstring[PLAYER_NAME_LEN];
        
        if (strlen(strings[i]) == 1) {
            int pnum = atoi(strings[i]);
            snprintf(pstring, PLAYER_NAME_LEN, "Player%d", pnum);
            parts[i] = TTF_RenderUTF8_Shaded(font_broadc, pstring,
                                             pcolors[pnum - 1], cMenuBG);
        } else
            parts[i] = TTF_RenderUTF8_Shaded(font_broadc, strings[i],
                                             cBroadcast, cMenuBG);

        width += parts[i]->w;
    }

    broadcast = SDL_CreateRGBSurface(SDL_HWSURFACE, width, parts[0]->h,
                                     SCREEN_BPP, 0, 0, 0, 0);

    int nparts = i;
    int hoffset = 0;
    for (i = 0; i < nparts; ++i) {
        SDL_Rect offset = {hoffset, 0, 0, 0};
        SDL_BlitSurface(parts[i], NULL, broadcast, &offset);
        hoffset += parts[i]->w;
        SDL_FreeSurface(parts[i]);
    }

    return broadcast;
}
