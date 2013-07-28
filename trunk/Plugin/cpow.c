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
    double cpow_r;
    double cpow_i;
    int cpow_power;

    double c;
    double d;
    double ang;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("cpow");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(cpow_r, 1.0),
    VAR_REAL(cpow_i, 0.0),
    VAR_INTEGER_NONZERO(cpow_power, 1)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(ang) = 2.0 * M_PI / ((double) VAR(cpow_power));
    VAR(c) = VAR(cpow_r) / ((double) VAR(cpow_power));
    VAR(d) = VAR(cpow_i) / ((double) VAR(cpow_power));
    return TRUE; // Always return TRUE.
}

/*
  z' = z^(cpow_r + i * cpow_i)

Simplified using formula:
    (a + i*b)^(c + i*d) = rho^c * e^(-d * theta) * [cos(c * theta + d * ln(rho) + i * sin(c * theta + d * ln(rho)],
    where (rho, theta) is the polar coordinate equivalent of z=(x, y).
*/

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double sn, cs;
    double a = atan2(FTy, FTx); // Angular polar dimension
    double lnr = 0.5 * log(FTx*FTx + FTy*FTy); // Natural logarithm of the radial polar dimension.

    double m = VVAR * exp(VAR(c) * lnr - VAR(d) * a);

    fsincos(VAR(c) * a + VAR(d) * lnr + VAR(ang) * (rand() % VAR(cpow_power)), &sn, &cs);

    FPx += m * cs;
    FPy += m * sn;

    return TRUE;
}
