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

#ifndef FRACTALALGORITHMINTERFACE_H
#define FRACTALALGORITHMINTERFACE_H

#include "classregistry.h"
#include "configentry.h"

#include <complex>


/**
  *@author Thomas Dreibholz
  */
class FractalAlgorithmInterface {
   public:
   FractalAlgorithmInterface();
   virtual ~FractalAlgorithmInterface();

   virtual const char* getIdentifier() const;
   virtual const char* getName()       const;

   virtual std::complex<double> defaultC1() const = 0;
   virtual std::complex<double> defaultC2() const = 0;
   virtual int defaultMaxIterations() const;

   inline const std::complex<double> getC1() { return C1; }
   inline const std::complex<double> getC2() { return C2; }
   virtual void configure(unsigned int         width,
                          unsigned int         height,
                          std::complex<double> c1,
                          std::complex<double> c2,
                          unsigned int         maxIterations);
   inline unsigned int*        getMaxIterations() { return &MaxIterations; }
   inline QList<ConfigEntry*>* getConfigEntries() { return &ConfigEntries; }
   virtual void changeSize(int X, int Y);
   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y) = 0;

//    static const FractalAlgorithmInterface* getAlgorithmByIndex(const unsigned int algorithmIndex);
//    static FractalAlgorithmInterface* makeAlgorithmInstanceByIndex(const unsigned int algorithmIndex);
//    static FractalAlgorithmInterface* makeAlgorithmInstanceByIdentifier(const char* algorithmIdentifier);

   protected:
   const char*          Name;
   const char*          Identifier;
   unsigned int         Width;
   unsigned int         Height;
   unsigned int         MaxIterations;
   std::complex<double> C1;
   std::complex<double> C2;
   double               StepX;
   double               StepY;
   QList<ConfigEntry*>  ConfigEntries;

   protected:
   static ClassRegistry Registry;
};

#endif
