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
	double v;

} Variables;

#define _USE_MATH_DEFINES
#define APO_NOVARIABLES
#define APO_VIRTUALVAR
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("deltaA");

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(v) = 0.5 * VVAR / M_PI;
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double avgr, avga;
	double s, c;
	
	avgr = VVAR * (sqrt(sqr(FTy) + sqr(FTx + 1.0)) / sqrt(sqr(FTy) + sqr(FTx - 1.0)));
	avga = (atan2( FTy, FTx - 1.0) - atan2(FTy, FTx + 1.0) )/ 2.0;
	fsincos( avga, &s, &c);

	FPx += avgr * c;
	FPy += avgr * s;



    return TRUE;
}
