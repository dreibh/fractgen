/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2019 by Thomas Dreibholz
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

#include "fractalalgorithminterface.h"
#include "uintconfigentry.h"


QList<FractalAlgorithmInterface*>* FractalAlgorithmInterface::AlgorithmList = nullptr;
bool                               FractalAlgorithmInterface::Updated       = false;


// ###### Constructor #######################################################
FractalAlgorithmInterface::FractalAlgorithmInterface(const char* identifier, const char* name)
{
   Updated    = true;
   Identifier = identifier;
   Name       = name;

   if(AlgorithmList == nullptr) {
      AlgorithmList = new QList<FractalAlgorithmInterface*>;
   }
   AlgorithmList->append(this);

   // When using this mechanism to allow configuration of own variables
   // in derived classes you need to make sure the string could be used in
   // well-formed xml as a tag (i.e. no whitespaces)
   ConfigEntries.append(new UIntConfigEntry(&MaxIterations, "MaxIterations"));
}


// ###### Destructor ########################################################
FractalAlgorithmInterface::~FractalAlgorithmInterface()
{
   AlgorithmList->removeAll(this);
}


// ###### Get default number of iterations ##################################
int FractalAlgorithmInterface::defaultMaxIterations() const
{
   return(250);
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


// ###### Comparison function for names ######################################
static bool lessThan(const FractalAlgorithmInterface* f1,
                     const FractalAlgorithmInterface* f2)
{
   return(strcmp(f1->getName(), f2->getName()) < 0);
}


// ###### Get algorithm by number #############################################
FractalAlgorithmInterface* FractalAlgorithmInterface::getAlgorithm(const unsigned int index)
{
   if(Updated) {
      qSort(AlgorithmList->begin(), AlgorithmList->end(), lessThan);
      Updated = false;
   }
   return(AlgorithmList->value(index, nullptr));
}


// ###### Get algorithm by identifier #######################################
FractalAlgorithmInterface* FractalAlgorithmInterface::getAlgorithmByIdentifier(const char* identifier)
{
   QListIterator<FractalAlgorithmInterface*> iterator(*AlgorithmList);
   while(iterator.hasNext()) {
      FractalAlgorithmInterface* algorithm = iterator.next();
      if(strcmp(identifier, algorithm->getIdentifier()) == 0) {
         return(algorithm);
      }
   }
   return(nullptr);
}
