/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2010 by Thomas Dreibholz
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

#ifndef SIMPLERGB_H
#define SIMPLERGB_H

#include <colorschemeinterface.h>

/**
  *@author Thomas Dreibholz
  */
class SimpleRGB : public ColorSchemeInterface  {
   public:
   SimpleRGB(const char* identifier = "SimpleRGB",
             const char* name       = "Simple RGB");
   ~SimpleRGB();

   virtual unsigned int getColor(const unsigned int value);

   private:
   static unsigned int rgbFromWaveLength(const double wave);
   static SimpleRGB* Registration;
   unsigned int*     ColorMap;
   unsigned int      ColorMapSize;
};

#endif
