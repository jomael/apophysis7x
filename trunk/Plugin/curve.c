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
    double curve_xamp;
    double curve_xlength;
    double curve_yamp;
    double curve_ylength;

    // precalc values:
    double pc_xamp;
    double pc_yamp;
    double pc_xlen;
    double pc_ylen;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("curve");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(curve_xamp, 0.0),
    VAR_REAL(curve_yamp, 0.0),
    VAR_REAL(curve_xlength, 1.0),
    VAR_REAL(curve_ylength, 1.0)
);

inline double fmax(double a, double b) {
	return a > b ? a : b;
}

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(pc_xamp) = VVAR * VAR(curve_xamp);
    VAR(pc_yamp) = VVAR * VAR(curve_yamp);
    VAR(pc_xlen) = 1.0 / fmax(VAR(curve_xlength) * VAR(curve_xlength), 1E-20);
    VAR(pc_ylen) = 1.0 / fmax(VAR(curve_ylength) * VAR(curve_ylength), 1E-20);

    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    FPx += VVAR * FTx + VAR(pc_xamp) * exp(-FTy * FTy * VAR(pc_xlen));
    FPy += VVAR * FTy + VAR(pc_yamp) * exp(-FTx * FTx * VAR(pc_ylen));

    return TRUE;
}

