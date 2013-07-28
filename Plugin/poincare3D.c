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
    double poincare3D_r, poincare3D_a, poincare3D_b;

    double cx, cy, cz;
    double c2;
    double c2x, c2y, c2z;
    double s2x, s2y, s2z;

} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("poincare3D");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(poincare3D_r, 0.0),
    VAR_REAL(poincare3D_a, 0.0),
    VAR_REAL(poincare3D_b, 0.0),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(cx) = -VAR(poincare3D_r) * cos(VAR(poincare3D_a)*M_PI_2) * cos(VAR(poincare3D_b)*M_PI_2);
    VAR(cy) =  VAR(poincare3D_r) * sin(VAR(poincare3D_a)*M_PI_2) * cos(VAR(poincare3D_b)*M_PI_2);
    VAR(cz) = -VAR(poincare3D_r) * sin(VAR(poincare3D_b)*M_PI_2);

    VAR(c2) = sqr(VAR(cx)) + sqr(VAR(cy)) + sqr(VAR(cz));

    VAR(c2x) = 2 * VAR(cx);
    VAR(c2y) = 2 * VAR(cy);
    VAR(c2z) = 2 * VAR(cz);

    VAR(s2x) = sqr(VAR(cx)) - sqr(VAR(cy)) - sqr(VAR(cz)) + 1;
    VAR(s2y) = sqr(VAR(cy)) - sqr(VAR(cx)) - sqr(VAR(cz)) + 1;
    VAR(s2z) = sqr(VAR(cz)) - sqr(VAR(cy)) - sqr(VAR(cx)) + 1;

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r2 = sqr(FTx) + sqr(FTy) + sqr(FTz);

    double x2cx = VAR(c2x)*FTx, y2cy = VAR(c2y)*FTy, z2cz = VAR(c2z)*FTz;

    double d = VVAR / (
        VAR(c2) * r2 - x2cx - y2cy - z2cz + 1
        );

    FPx += d * (
        FTx * VAR(s2x) + VAR(cx) * (y2cy + z2cz - r2 - 1)
    );
    FPy += d * (
        FTy * VAR(s2y) + VAR(cy) * (x2cx + z2cz - r2 - 1)
    );
    FPz += d * (
        FTz * VAR(s2z) + VAR(cz) * (y2cy + x2cx - r2 - 1)
    );

    return TRUE;
}
