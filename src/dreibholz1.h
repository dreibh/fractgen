/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2018 by Thomas Dreibholz
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

#ifndef DREIBHOLZ1_H
#define DREIBHOLZ1_H


#include <fractalalgorithminterface.h>
#include <complex>


/**
  *@author Thomas Dreibholz
  */
class Dreibholz1 : public FractalAlgorithmInterface
{
   public:
   Dreibholz1(const char* identifier = "Dreibholz1",
              const char* name       = "Dreibholz1 Test");
   ~Dreibholz1();

   virtual std::complex<double> defaultC1() const;
   virtual std::complex<double> defaultC2() const;
   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y);

   private:
   static Dreibholz1* Registration;
};

#endif
