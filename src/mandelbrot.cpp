/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2009 by Thomas Dreibholz
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

#include "mandelbrot.h"


Mandelbrot* Mandelbrot::Registration = new Mandelbrot();


// ###### Constructor #######################################################
Mandelbrot::Mandelbrot(const char* identifier, const char* name)
   : FractalAlgorithmInterface(identifier, name)
{
}


// ###### Destructor ########################################################
Mandelbrot::~Mandelbrot()
{
}


// ###### Get default for C1 ################################################
std::complex<double> Mandelbrot::defaultC1() const
{
   return(std::complex<double>(-1.5, 1.5));
}


// ###### Get default for C2 ################################################
std::complex<double> Mandelbrot::defaultC2() const
{
   return(std::complex<double>(1.5, -1.5));
}


// ###### Calculate graphics point (x,y) ####################################
unsigned int Mandelbrot::calculatePoint(const unsigned int x,
                                        const unsigned int y)
{
   const std::complex<double> c = std::complex<double>(C1.real() + ((double)x * StepX),
                                                       C1.imag() + ((double)y * StepY));
   std::complex<double> z(0.0, 0.0);
   unsigned int         i;

   for(i = 0;i < MaxIterations;i++) {
      z = z*z - c;
      if(z.real() * z.real() + z.imag() * z.imag() >= 2.0) {
         return(i);
      }
   }

   return(i);
}
