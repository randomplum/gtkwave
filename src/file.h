/*
 * Copyright (c) Tony Bybell 2010-2013
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 */

#ifndef WAVE_FILESEL_H
#define WAVE_FILESEL_H

void fileselbox(const char *title, char **filesel_path, GCallback ok_func, GCallback notok_func, const char *pattn, int is_writemode);

#endif
