/*
    Apophysis Plugin

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
    int hypertile_p, hypertile_q, hypertile_n;

    double re, im;

} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hypertile");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(hypertile_p, 3, 0x7fffffff, 3),
    VAR_INTEGER_RANGE(hypertile_q, 3, 0x7fffffff, 7),
    VAR_INTEGER(hypertile_n, 0),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    double pa = 2*M_PI / VAR(hypertile_p),
           qa = 2*M_PI / VAR(hypertile_q);

    double r = (1 - cos(pa)) / (cos(pa) + cos(qa)) + 1;

    if (r > 0)
        r = 1 / sqrt(r);
    else
        r = 1;

    double a = VAR(hypertile_n) * pa;

    VAR(re) = r * cos(a);
    VAR(im) = r * sin(a);

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double a = FTx + VAR(re),
           b = FTy - VAR(im);

    double c = VAR(re)*FTx - VAR(im)*FTy + 1,
           d = VAR(re)*FTy + VAR(im)*FTx;

    double vr = VVAR / (sqr(c) + sqr(d));

    FPx += vr * (a*c + b*d);
    FPy += vr * (b*c - a*d);

    return TRUE;
}
