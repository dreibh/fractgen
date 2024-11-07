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

#include "fractalalgorithminterface.h"
#include "uintconfigentry.h"


ClassRegistry* FractalAlgorithmInterface::Registry = nullptr;


// ###### Constructor #######################################################
FractalAlgorithmInterface::FractalAlgorithmInterface()
{
   // When using this mechanism to allow configuration of own variables
   // in derived classes you need to make sure the string could be used in
   // well-formed XML as a tag (i.e. no whitespaces)!
   ConfigEntries.append(new UIntConfigEntry(&MaxIterations, "MaxIterations"));
}


// ###### Destructor ########################################################
FractalAlgorithmInterface::~FractalAlgorithmInterface()
{
}


// ###### Get default number of iterations ##################################
int FractalAlgorithmInterface::defaultMaxIterations() const
{
   return 250;
}


// ###### Configure algorithm ###############################################
void FractalAlgorithmInterface::configure(unsigned int         width,
                                          unsigned int         height,
                                          std::complex<double> c1,
                                          std::complex<double> c2,
                                          unsigned int         maxIterations)
{
   Width         = width;
   Height        = height;
   MaxIterations = maxIterations;
   C1            = c1;
   C2            = c2;
   StepX         = (c2.real() - c1.real()) / Width;
   StepY         = (c2.imag() - c1.imag()) / Height;
}


// ###### Change image size ##################################################
void FractalAlgorithmInterface::changeSize(int X, int Y)
{
   Width  = X;
   Height = Y;
   StepX  = (C2.real() - C1.real()) / Width;
   StepY  = (C2.imag() - C1.imag()) / Height;
}


// ###### Create new instance class #########################################
bool FractalAlgorithmInterface::registerClass(const QString& identifier,
                                              const QString& description,
                                              FractalAlgorithmInterface* (*makeInstanceFunction)())
{
  if(Registry == nullptr) {
      Registry = new ClassRegistry;
      Q_CHECK_PTR(Registry);
  }
  FractalAlgorithmInterface::Registry->registerClass(identifier, description,
                                                     (void* (*)())makeInstanceFunction);
}
