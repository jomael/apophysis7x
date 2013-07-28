/*
    Apophysis Plugin

    Copyright (C) 2007-2009 Joel Faber
    Copyright (C) 2007-2009 Michael Faber

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
APO_PLUGIN("butterfly");

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(v) = VVAR * 4.0 / sqrt(3.0 * M_PI);
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double y2 = FTy * 2.0;
	double r = VAR(v) * sqrt(fabs(FTy * FTx)/(EPS + sqr(FTx) + sqr(y2)));

	FPx += r * FTx;
	FPy += r * y2;

    return TRUE;
}
