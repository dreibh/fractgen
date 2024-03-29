/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2024 by Thomas Dreibholz
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
 * Contact: thomas.dreibholz@gmail.com
 */

#ifndef MANDELBROTN_H
#define MANDELBROTN_H

#include <mandelbrot.h>


/**
  *@author Thomas Dreibholz
  */
class MandelbrotN : public Mandelbrot  {
   public:
   MandelbrotN(const char* identifier = "MandelbrotN",
               const char* name       = "MandelbrotN z[i+1]=z[i]^N-c");
   ~MandelbrotN();

   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y) override;

   private:
   static MandelbrotN* Registration;
   double              N;
};

#endif
