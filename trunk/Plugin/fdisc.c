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
#define _USE_MATH_DEFINES
#define APO_NOVARIABLES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("fdisc");


// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{

    double c, s;
    double a = M_2PI /(sqrt(sqr(FTx) + sqr(FTy)) + 1.0);
    double r = (atan2(FTy, FTx) * M_1_PI + 1.0) * 0.5;

    fsincos( a, &s, &c);

    FPx += VVAR * r * c;
    FPy += VVAR * r * s;

    return TRUE;
}
