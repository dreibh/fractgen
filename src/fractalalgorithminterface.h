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

#ifndef FRACTALALGORITHMINTERFACE_H
#define FRACTALALGORITHMINTERFACE_H

#include "configentry.h"

#include <QList>
#include <complex>


/**
  *@author Thomas Dreibholz
  */
class FractalAlgorithmInterface {
   public:
   FractalAlgorithmInterface(const char* identifier, const char* name);
   virtual ~FractalAlgorithmInterface();
   inline const char* getIdentifier() { return(Identifier); }
   inline const char* getName() const { return(Name); }

   virtual std::complex<double> defaultC1() const = 0;
   virtual std::complex<double> defaultC2() const = 0;
   virtual int defaultMaxIterations() const;

   inline const std::complex<double> getC1() { return(C1); }
   inline const std::complex<double> getC2() { return(C2); }
   virtual void configure(unsigned int         width,
                          unsigned int         height,
                          std::complex<double> c1,
                          std::complex<double> c2,
                          unsigned int         maxIterations);
   inline unsigned int* getMaxIterations() { return(&MaxIterations); }
   inline QList<ConfigEntry*>* getConfigEntries() { return(&ConfigEntries); }
   virtual void changeSize(int X, int Y);
   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y) = 0;

   static FractalAlgorithmInterface* getAlgorithm(const unsigned int index);
   static FractalAlgorithmInterface* getAlgorithmByIdentifier(const char* name);

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

   private:
   static QList<FractalAlgorithmInterface*>* AlgorithmList;
   static bool                               Updated;
};

#endif
