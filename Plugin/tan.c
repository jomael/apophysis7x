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


#define _USE_MATH_DEFINES
#define APO_NOVARIABLES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("tan");


// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{

    // Always return TRUE.
    return TRUE;
}

// Calculates the function z' = tan(z) = sin(z)/cos(z)

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double sinx, cosx, sinhy, coshy;

    fsincos(2 * FTx, &sinx, &cosx);
    sinhcosh(2 * FTy, &sinhy, &coshy);

    double denom = VVAR / (cosx + coshy + EPS);

	FPx += sinx * denom;
    FPy += sinhy * denom;

    return TRUE;
}

