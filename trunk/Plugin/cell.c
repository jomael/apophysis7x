/*
    Apophysis Plugin

    Copyright (c) 2008 Joel Faber.  All rights reserverd.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
    double cell_size;

    double inv_cell_size;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("cell");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(cell_size, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	if (VAR(cell_size) == 0) VAR(cell_size) = 1e-6;
    VAR(inv_cell_size) = 1.0 / VAR(cell_size);
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    // calculate input cell
    int x = floor(FTx*VAR(inv_cell_size));
	int y = floor(FTy*VAR(inv_cell_size));

	// Offset from cell origin
	double dx = FTx - x*VAR(cell_size);
	double dy = FTy - y*VAR(cell_size);

    // interleave cells
    if (y >= 0)
    {
        if (x >= 0)
        {
            y *= 2;
            x *= 2;
        }
        else
        {
            y *= 2;
            x = -(2*x+1);
        }
    }
    else
    {
        if (x >= 0)
        {
            y = -(2*y+1);
            x *= 2;
        }
        else
        {
            y = -(2*y+1);
            x = -(2*x+1);
        }
    }

    // calculate output point from interleaved cell
    FPx += VVAR * (dx + x*VAR(cell_size));
    FPy -= VVAR * (dy + y*VAR(cell_size));

    return TRUE;
}
