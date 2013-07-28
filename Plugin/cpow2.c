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
    double cpow2_r, cpow2_a;
    int cpow2_divisor;
    int cpow2_spread;

    double c, half_c;
    double d, half_d;
    double ang;
    double inv_spread, full_spread;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("cpow2");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(cpow2_r, 1.0),
    VAR_REAL(cpow2_a, 0.0),
    VAR_INTEGER_NONZERO(cpow2_divisor, 1),
    VAR_INTEGER_RANGE(cpow2_spread, 1, 0x7fffffff, 1),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(ang) = 2*M_PI / ((double) VAR(cpow2_divisor));
    VAR(c) = VAR(cpow2_r) * cos(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
    VAR(d) = VAR(cpow2_r) * sin(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
    VAR(half_c) = VAR(c) / 2;
    VAR(half_d) = VAR(d) / 2;
    VAR(inv_spread) = 0.5 / VAR(cpow2_spread);
    VAR(full_spread) = 2*M_PI*VAR(cpow2_spread);

    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double sn, cs;
    double a = atan2(FTy, FTx);

    int n = rand() % VAR(cpow2_spread);
    if (a < 0) n++;
    a += 2*M_PI*n;
    if (cos(a*VAR(inv_spread)) < rand()*2.0/RAND_MAX - 1.0)
        a -= VAR(full_spread);

    double lnr2 = log(FTx*FTx + FTy*FTy); // logarithm * 2

    double r = VVAR * exp(VAR(half_c) * lnr2 - VAR(d) * a);

    fsincos(VAR(c) * a + VAR(half_d) * lnr2 + VAR(ang) * rand(),
        &sn, &cs);

    FPx += r * cs;
    FPy += r * sn;

    return TRUE;
}
