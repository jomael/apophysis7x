/*
    Apophysis Plugin

    Copyright (C) 2007-2009 Joel Faber

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
    double split_xsize;
    double split_ysize;
    
    // precacluated values
    double xang;
    double yang;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("split");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(split_xsize, 0.5),
    VAR_REAL(split_ysize, 0.5)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(xang) = M_PI * VAR(split_xsize);
    VAR(yang) = M_PI * VAR(split_ysize);
    
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{  
    if (cos(FTx * VAR(xang)) >= 0)
        FPy += VVAR * FTy;
    else
        FPy -= VVAR * FTy;
    
    if (cos(FTy * VAR(yang)) >= 0)
        FPx += VVAR * FTx;
    else 
        FPx -= VVAR * FTx;
    
    return TRUE;
}

