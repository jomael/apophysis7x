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
    double ortho_in;
    double ortho_out;

} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"


// Set the name of this plugin
APO_PLUGIN("ortho");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_CYCLE(ortho_in, -M_PI, M_PI, 0.0),
    VAR_REAL_CYCLE(ortho_out, -M_PI, M_PI, 0.0)

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r, a;
    double xo;
    double ro;
    double c,s;
    double x,y, tc, ts;
    double theta;
    
    r = sqr(FTx) + sqr(FTy);
    
    if ( r < 1.0)// && FTx > 0.0 && FTy > 0.0)
    {
        if(FTx >= 0.0)
        {
            xo = (r + 1.0)/ (2.0 * FTx);
            ro = sqrt(sqr(FTx - xo) + sqr(FTy));
            theta = atan2(1.0 , ro);
            a = fmod( VAR(ortho_in)* theta + atan2(FTy, xo - FTx ) + theta, 2.0 * theta) - theta;
            fsincos(a, &s, &c);
            
            FPx += VVAR * (xo - c * ro);
            FPy += VVAR * s * ro;
        }
        else
        {
            xo = - (r + 1.0)/ (2.0 * FTx);
            ro = sqrt(sqr(-FTx - xo) + sqr(FTy));
            theta = atan2(1.0 , ro);
            a = fmod( VAR(ortho_in) * theta + atan2(FTy, xo + FTx ) + theta, 2.0 * theta) - theta;
            fsincos(a, &s, &c);

            FPx -= VVAR * (xo - c * ro);
            FPy += VVAR * s * ro;
        }
    }
    else
    {
        r = 1.0 / sqrt(r);
        fsincos( atan2(FTy, FTx), &ts, &tc);
        x = r * tc;
        y = r * ts;
        
        if(x >= 0.0)
        {
            xo = (sqr(x) + sqr(y) + 1.0)/ (2.0 * x);
            ro = sqrt(sqr(x - xo) + sqr(y));
            theta = atan2(1.0 , ro);
            a = fmod( VAR(ortho_out)* theta + atan2(y, xo - x ) + theta, 2.0 * theta) - theta;
            fsincos(a, &s, &c);

            x = (xo - c * ro);
            y =  s * ro;
            fsincos( atan2(y, x), &ts, &tc);
            r = 1.0 / sqrt(sqr(x) + sqr(y));
            
            FPx += VVAR * r * tc;
            FPy += VVAR * r * ts;
        }
        else
        {
            xo = - (sqr(x) + sqr(y) + 1.0)/ (2.0 * x);
            ro = sqrt(sqr(-x - xo) + sqr(y));
            theta = atan2(1.0 , ro);
            a = fmod( VAR(ortho_out) * theta + atan2(y, xo + x ) + theta, 2.0 * theta) - theta;
            fsincos(a, &s, &c);

            x = (xo - c * ro);
            y =  s * ro;
            fsincos( atan2(y, x), &ts, &tc);
            r = 1.0 / sqrt(sqr(x) + sqr(y));

            FPx -= VVAR * r * tc;
            FPy += VVAR * r * ts;
            
        }
    }



    return TRUE;
}
