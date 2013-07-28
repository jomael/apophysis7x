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

typedef struct
{
    double ffive;
    double fnatlog;
} Variables;

#define _USE_MATH_DEFINES
#define APO_NOVARIABLES
#define APO_VIRTUALVAR
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("fibonacci");


// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // Updated to use the new constants. Still calculates
    // invserse of root five and the nat log of the Golden Ratio.
    // I'm not sure how many decimal places were appropriate,
    // or how many C allows, and this isn't going to take
    // up any noticeable amount of time.
    VAR(ffive) = 1/M_SQRT5;
    VAR(fnatlog) = log(M_PHI);
    // Always return TRUE.
    return TRUE;
}

//       p^z - (-p)^(-z)
// z' = -----------------
//           sqrt(5)
//
// Where p is the Golden Ratio.
// This function generates the fibonacci sequence
// for real integer values.
// 1 2 3 4 5 6  7  8  9 10 11  12  13  14  15 < Real Value
// 1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 < Fib Value
//
// Negative real integers produce the negative fibonacci sequence,
// which is the same as the normal one, except every
// other number is negative.
// 1 0 -1 -2 -3 -4 -5 -6 -7  -8 < Real Value
// 1 0  1 -1  3 -3  5 -8 13 -21 < Fib Value

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{

	double snum1, cnum1, snum2, cnum2;

    fsincos(FTy * VAR(fnatlog), &snum1, &cnum1);
    fsincos((FTx * M_PI + FTy * VAR(fnatlog)) * -1, &snum2, &cnum2);

    double eradius1 = exp(FTx * VAR(fnatlog));
    double eradius2 = exp((FTx * VAR(fnatlog) - FTy * M_PI) * -1);

	FPx += VVAR * (eradius1 * cnum1 - eradius2 * cnum2) * VAR(ffive);
    FPy += VVAR * (eradius1 * snum1 - eradius2 * snum2) * VAR(ffive);

    return TRUE;
}

