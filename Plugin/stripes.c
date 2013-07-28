/*
    Apophysis Plugin

    Copyright (C) 2007-2009 Joel Faber
    Copyright (C) 2007-2009 Michael Faber

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
    double stripes_space;
    double stripes_warp;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("stripes");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_RANGE(stripes_space, 0.0, 1.0, 0.5),
    VAR_REAL(stripes_warp, 0.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // Always return TRUE.
    return TRUE;
}

inline double rint(double x)
{
    int temp; temp = (x >= 0. ? (int)(x + 0.5) : (int)(x - 0.5));
    return (double)temp;
}


// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double roundx;
    double offsetx;
 
    roundx = (double)rint(FTx);
    offsetx = FTx - roundx;

 	FPx += VVAR * ( offsetx * (1.0 - VAR(stripes_space)) + roundx);
 	FPy += VVAR * (FTy + offsetx * offsetx * VAR(stripes_warp));

    return TRUE;
}

