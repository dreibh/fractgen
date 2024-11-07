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

#include "mandelbrotn.h"
#include "doubleconfigentry.h"

// #include <math.h>

const QString MandelbrotN::Identifier(QStringLiteral("MandelbrotN"));
const QString MandelbrotN::Description(QStringLiteral("MandelbrotN z[i+1]=z[i]^N-c"));
const bool MandelbrotN::Registered =
   FractalAlgorithmInterface::registerClass(
      MandelbrotN::Identifier,
      MandelbrotN::Description,
      &MandelbrotN::makeNewInstance
   );


// ###### Constructor #######################################################
MandelbrotN::MandelbrotN()
{
   N = 4.0;
   ConfigEntries.append(new DoubleConfigEntry(&N, "N"));
}


// ###### Destructor ########################################################
MandelbrotN::~MandelbrotN()
{
}


// ###### Get identifier ####################################################
const QString& MandelbrotN::getIdentifier() const
{
   return MandelbrotN::Identifier;
}


// ###### Get description ###################################################
const QString& MandelbrotN::getDescription() const
{
   return MandelbrotN::Description;
}

// ###### Create new instance ###############################################
FractalAlgorithmInterface* MandelbrotN::makeNewInstance()
{
   return new MandelbrotN();
}


// ###### Calculate graphics point (x,y) ####################################
unsigned int MandelbrotN::calculatePoint(const unsigned int x,
                                         const unsigned int y)
{
   const std::complex<double> c = std::complex<double>(C1.real() + ((double)x * StepX),
                                                       C1.imag() + ((double)y * StepY));
   std::complex<double> z(0.0, 0.0);
   unsigned int         i;

   for(i = 0;i < MaxIterations;i++) {
      z = pow(z, (int)rint(N)) - c;
      if(z.real() * z.real() + z.imag() * z.imag() >= 2.0) {
         return i;
      }
   }
   return i;
}
