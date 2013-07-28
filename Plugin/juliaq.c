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
    int juliaq_power, juliaq_divisor;

    double half_inv_power;
    double inv_power, inv_power_2pi;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("juliaq");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_NONZERO(juliaq_power, 3),
    VAR_INTEGER_NONZERO(juliaq_divisor, 2),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(half_inv_power) = 0.5 * VAR(juliaq_divisor) / (double)VAR(juliaq_power);

    VAR(inv_power) = VAR(juliaq_divisor) / (double)VAR(juliaq_power);
    VAR(inv_power_2pi) = M_2PI / (double)VAR(juliaq_power);

    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double sina, cosa;
    fsincos( atan2(FTy, FTx)*VAR(inv_power) + rand()*VAR(inv_power_2pi),
        &sina, &cosa);
    double r = VVAR * pow(sqr(FTx) + sqr(FTy), VAR(half_inv_power));
    FPx += r * cosa;
    FPy += r * sina;

    return TRUE;
}
