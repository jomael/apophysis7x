/*
    Apophysis Plugin
    Copyright (C) 2007-2008 Joel Faber

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
    int pie_slices;
    double pie_thickness;
    double pie_rotation;

    double pi2_slices;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("pie");

// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_NONZERO(pie_slices, 6),
    VAR_REAL_RANGE(pie_thickness, 0.0, 1.0, 0.5),
    VAR_REAL_CYCLE(pie_rotation, 0.0, 2.0 * M_PI, 0.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(pi2_slices) = 2 * M_PI / VAR(pie_slices);

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    int sl;
	double a, r;
	double s, c;

	sl = rand() % VAR(pie_slices); // Pick a random slice.

	// Choose a random angle in the slice.
	a = VAR(pie_rotation) + VAR(pi2_slices) * (sl + VAR(pie_thickness)  * random01());

	// Choose a random distance from the centre, scaled by VVAR.
	r = VVAR * random01();

	// Convert from polar coordinates to rectangular coordinates.
    fsincos(a, &s, &c);
    FPx += r * c;
    FPy += r * s;

    return TRUE;
}

