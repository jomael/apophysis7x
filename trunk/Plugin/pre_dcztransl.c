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

    Written by Georg Kiehne
    --> http://xyrus-worx.net, http://xyrus02.deviantart.com

    If you find any bugs / nags - keep them :)
*/

typedef struct {
  double pre_dcztransl_x0;
  double pre_dcztransl_x1;
  double pre_dcztransl_factor;
  double x0_, x1_, x1_m_x0;
  int pre_dcztransl_overwrite;
  int pre_ztransl_clamp;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("pre_dcztransl");
APO_VARIABLES(
  VAR_REAL_RANGE(pre_dcztransl_x0, 0.0, 1.0, 0.0),
  VAR_REAL_RANGE(pre_dcztransl_x1, 0.0, 1.0, 1.0),
  VAR_REAL(pre_dcztransl_factor, 1.0),
  VAR_INTEGER_RANGE(pre_dcztransl_overwrite, 0, 1, 1),
  VAR_INTEGER_RANGE(pre_ztransl_clamp, 0, 1, 0)
);

int PluginVarPrepare(Variation* vp)
{
  vp->var.x0_ = vp->var.pre_dcztransl_x0 < vp->var.pre_dcztransl_x1 ? vp->var.pre_dcztransl_x0 : vp->var.pre_dcztransl_x1;
  vp->var.x1_ = vp->var.pre_dcztransl_x0 > vp->var.pre_dcztransl_x1 ? vp->var.pre_dcztransl_x0 : vp->var.pre_dcztransl_x1;
  vp->var.x1_m_x0 = vp->var.x1_ - vp->var.x0_ == 0 ? EPS : vp->var.x1_ - vp->var.x0_;

  return 1;
}

inline double flip(double a, double b, double c){return (c*(b-a)+a);}
int PluginVarCalc(Variation* vp)
{
  double zf = vp->var.pre_dcztransl_factor * (*(vp->pColor) - vp->var.x0_) / vp->var.x1_m_x0;
  if (vp->var.pre_ztransl_clamp != 0)
     zf = zf < 0 ? 0 : zf > 1 ? 1 : zf;

  *(vp->pFTx) = vp->vvar*(*(vp->pFTx));
  *(vp->pFTy) = vp->vvar*(*(vp->pFTy));

  if (vp->var.pre_dcztransl_overwrite == 0)
    *(vp->pFTz) = vp->vvar*(*(vp->pFTz))*zf;
  else *(vp->pFTz) = vp->vvar*zf;

	return 1;
}
