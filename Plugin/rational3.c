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
	double rational3_vvar;
    double rational3_t3;
    double rational3_t2;
    double rational3_t1;
    double rational3_tc;
    double rational3_b3;
    double rational3_b2;
    double rational3_b1;
    double rational3_bc;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("rational3");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(rational3_t3, 1.0),
    VAR_REAL(rational3_t2, 0.0),
    VAR_REAL(rational3_t1, 0.0),
    VAR_REAL(rational3_tc, 1.0),
    VAR_REAL(rational3_b3, 0.0),
    VAR_REAL(rational3_b2, 1.0),
    VAR_REAL(rational3_b1, 0.0),
    VAR_REAL(rational3_bc, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(rational3_vvar) = VVAR;
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{


    double xsqr = FTx * FTx;
    double ysqr = FTy * FTy;
    double xcb = FTx * FTx * FTx;
    double ycb = FTy * FTy * FTy;

    double tr = VAR(rational3_t3) * (xcb - 3 * FTx * ysqr) + VAR(rational3_t2) * (xsqr - ysqr) + VAR(rational3_t1) * FTx + VAR(rational3_tc);
    double ti = VAR(rational3_t3) * (3 * xsqr * FTy - ycb) + VAR(rational3_t2) * 2 * FTx * FTy + VAR(rational3_t1) * FTy;

    double br = VAR(rational3_b3) * (xcb - 3 * FTx * ysqr) + VAR(rational3_b2) * (xsqr - ysqr) + VAR(rational3_b1) * FTx + VAR(rational3_bc);
    double bi = VAR(rational3_b3) * (3 * xsqr * FTy - ycb) + VAR(rational3_b2) * 2 * FTx * FTy + VAR(rational3_b1) * FTy;

    double r3den = 1/(br * br + bi * bi);

 	FPx += VAR(rational3_vvar) * (tr * br + ti * bi) * r3den;
    FPy += VAR(rational3_vvar) * (ti * br - tr * bi) * r3den;

//    FPx += VAR(rational3_vvar) * FTx * 2;
//    FPy += VAR(rational3_vvar) * FTy * 2;

    return TRUE;

}

// Rational3 allows you to customize a rational function
// involving the complex variable z. It can be represented
// as the function...

// az^3 + bz^2 + cz + d
// -------------------- division line
// ez^3 + fz^2 + gz + h

// In this case,
// t3 = a (top z^3 coefficient)
// t2 = b
// t1 = c
// tc = d (top constant)
// b3 = e (bottom z^3 coefficient)
// b2 = f
// b1 = g
// bc = h (bottom constant)

// This baby was a beast to work out, so please don't ask
// me to explain the whole thing.

// This works sort of like Curl, except Curl uses the formula...

//       z
// -------------
// bz^2 + az + 1

// Which is weird and abstract (one might say pointless,
// but that would be mean).
