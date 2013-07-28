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
    double c1x;
    double c1y;
    double c2x;
    double c2y;
    double poincare_c1r;
    double poincare_c2r;
    double c1d; //r0 + r1
    double c2d; //r0 + r2
    double poincare_c1a;
    double poincare_c2a;

} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"


// Set the name of this plugin
APO_PLUGIN("poincare");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(poincare_c1r, 1.0),
    VAR_REAL_CYCLE(poincare_c1a, -M_PI, M_PI, -1.0),
    VAR_REAL(poincare_c2r, 1.0),
    VAR_REAL_CYCLE(poincare_c2a, -M_PI, M_PI, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(c1d) = sqrt( 1.0 + sqr(VAR(poincare_c1r)) );
    VAR(c2d) = sqrt( 1.0 + sqr(VAR(poincare_c2r)) );
    
    VAR(c1x) = VAR(c1d) * cos ( VAR(poincare_c1a));
    VAR(c1y) = VAR(c1d) * sin ( VAR(poincare_c1a));
    VAR(c2x) = VAR(c2d) * cos ( VAR(poincare_c2a));
    VAR(c2y) = VAR(c2d) * sin ( VAR(poincare_c2a));
    
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double x, y;
    
    x = VAR(c1x) + ( sqr(VAR(poincare_c1r)) * ( FTx - VAR(c1x))) / ( sqr(FTx - VAR(c1x)) + sqr(FTy - VAR(c1y)) );
    y = VAR(c1y) + ( sqr(VAR(poincare_c1r)) * ( FTy - VAR(c1y))) / ( sqr(FTx - VAR(c1x)) + sqr(FTy - VAR(c1y)) );
    
    FPx += VAR(c2x) + ( sqr(VAR(poincare_c2r)) * ( x - VAR(c2x))) / ( sqr(x - VAR(c2x)) + sqr(y - VAR(c2y)) );
    FPy += VAR(c2y) + ( sqr(VAR(poincare_c2r)) * ( y - VAR(c2y))) / ( sqr(x - VAR(c2x)) + sqr(y - VAR(c2y)) );

    return TRUE;
}
    
