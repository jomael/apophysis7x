/*
    Apophysis Plugin

    Copyright (C) 2009 Joel Faber

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
    double blur_linear_length;
    double blur_linear_angle;

    double s;
    double c;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("blur_linear");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(blur_linear_length, 0.0),
    VAR_REAL_CYCLE(blur_linear_angle, 0.0, M_2PI, 0.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    fsincos(VAR(blur_linear_angle), &VAR(s), &VAR(c));
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r = VAR(blur_linear_length) * random01();

    FPx += VVAR * (FTx + r * VAR(c));
    FPy += VVAR * (FTy + r * VAR(s));

    return TRUE;
}
