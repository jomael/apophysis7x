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
    // expo_real represents the real part of the base (a)
    double expo_real;
    // expo_imaginary represents the imaginary part of the base (b)
    double expo_imaginary;
    double expo_k;
    double expo_t;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("expo");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(expo_real, -1.0),
    VAR_REAL(expo_imaginary, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    double ereal = VAR(expo_real);
    double eimag = VAR(expo_imaginary);
	VAR(expo_k) = 0.5 * log(ereal * ereal + eimag * eimag + 1e-300);
	VAR(expo_t) = atan2(eimag,ereal);
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double expor = exp(FTx * VAR(expo_k) - FTy * VAR(expo_t));
	double snv, csv;

    fsincos(FTx * VAR(expo_t) + FTy * VAR(expo_k), &snv, &csv);

	FPx += VVAR * expor * csv;
    FPy += VVAR * expor * snv;

    return TRUE;
}

// Given the equation (a + ib)^z, or c^z, where c = a + ib...
// We can rewrite it as e^(ln(c^z))...
// Using the laws of Logs, we get e^(z * ln(c))...

// The ln of a complex number is ln(r) + itheta, where
// r is the radius and theta is the angle. Thus, we need
// the radius and angle of our base number c.

// k is what I've used to represent the radius of the number
// c, or a + ib. t is used to represent the angle.
// Thus, expok is the radius of c and expot is the angle.

// Now we have e^(z * (ln(k) + it)), or e^((x + iy) * (ln(k) + it))
// Simplifying this down, we get...

// e^(xln(k) - yt) * e^i(xt + yln(k))

// Because a Complex Number can be presented as
// r * e^itheta, where r is the radius and theta is the angle,
// We can say that r' = e^(xln(k) - yt)
// And that theta' = xt + yln(k)

// For optimization (as recommended by Joel) we calculate k,
// the radius of our complex number, as the ln of k,
// because we never need k to be on its own (it is always
// logged before it is used).

// That's the equation!
