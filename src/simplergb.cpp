/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2016 by Thomas Dreibholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Contact: dreibh@iem.uni-due.de
 */

#include "simplergb.h"

#include <qcolor.h>
#include <math.h>


SimpleRGB* SimpleRGB::Registration = new SimpleRGB();


#define INITAL_COLORMAP_SIZE 256


SimpleRGB::SimpleRGB(const char* identifier, const char* name)
   : ColorSchemeInterface(identifier, name)
{
   ColorMapSize = INITAL_COLORMAP_SIZE;
   ColorMap     = new unsigned int[ColorMapSize];
   Q_CHECK_PTR(ColorMap);
   for(unsigned int i = 0;i < ColorMapSize;i++) {
      ColorMap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColorMapSize));
   }
}


SimpleRGB::~SimpleRGB()
{
   delete [] ColorMap;
   ColorMap = NULL;
}


unsigned int SimpleRGB::rgbFromWaveLength(const double wave)
{
   double r = 0.0;
   double g = 0.0;
   double b = 0.0;

   if (wave >= 380.0 && wave <= 440.0) {
      r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
      b = 1.0;
   } else if (wave >= 440.0 && wave <= 490.0) {
      g = (wave - 440.0) / (490.0 - 440.0);
      b = 1.0;
   } else if (wave >= 490.0 && wave <= 510.0) {
      g = 1.0;
      b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
   } else if (wave >= 510.0 && wave <= 580.0) {
      r = (wave - 510.0) / (580.0 - 510.0);
      g = 1.0;
   } else if (wave >= 580.0 && wave <= 645.0) {
      r = 1.0;
      g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
   } else if (wave >= 645.0 && wave <= 780.0) {
      r = 1.0;
   }

   double s = 1.0;
   if (wave > 700.0) {
      s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
   }
   else if (wave <  420.0) {
      s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);
   }

   r = pow(r * s, 0.8);
   g = pow(g * s, 0.8);
   b = pow(b * s, 0.8);
   return qRgb(int(r * 255), int(g * 255), int(b * 255));
}


unsigned int SimpleRGB::getColor(const unsigned int value)
{
   return(ColorMap[value % ColorMapSize]);
}
