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

/* SET PLUGIN NAME HERE:
   e.g. name-me
*/
APO_PLUGIN("fisheye");

/* DO PREPARE STUFF HERE:
   You must call the argument "vp"
*/
int PluginVarPrepare(Variation* vp)
{
    return TRUE; // Always return TRUE.
}

/* DO CALC STUFF HERE:
   You must call the argument "vp"
*/
int PluginVarCalc(Variation* vp)
{
    double r = 2 * VVAR / (sqrt(FTx * FTx + FTy * FTy) + 1); 
    FPx = FPx + r * FTy; 
    FPy = FPy + r * FTx;
    return TRUE;
}
