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


class FractalAlgorithmInterface {
   // ====== Constructor/Destructor =========================================
   public:
   FractalAlgorithmInterface();
   virtual ~FractalAlgorithmInterface();

   // ====== Algorithm information ==========================================
   virtual const QString& getIdentifier()  const = 0;
   virtual const QString& getDescription() const = 0;

   // ====== Algorithm parameters ===========================================
   virtual std::complex<double> defaultC1() const = 0;
   virtual std::complex<double> defaultC2() const = 0;
   virtual int defaultMaxIterations()       const;

   inline const std::complex<double> getC1() { return C1; }
   inline const std::complex<double> getC2() { return C2; }
   virtual void configure(const unsigned int          width,
                          const unsigned int          height,
                          const std::complex<double>& c1,
                          const std::complex<double>& c2,
                          const unsigned int          maxIterations);
   inline unsigned int*        getMaxIterations() { return &MaxIterations; }
   inline QList<ConfigEntry*>* getConfigEntries() { return &ConfigEntries; }
   virtual void changeSize(int X, int Y);

   // ====== The actual calculation =========================================
   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y) = 0;

   // ====== Algorithm registry =============================================
   inline static const QMap<QString, ClassRegistry::Registration*>& getAlgorithms() {
      return Registry->getClassMap();
   }
   inline static FractalAlgorithmInterface* makeAlgorithmInstance(const QString& identifier) {
      return (FractalAlgorithmInterface*)Registry->makeNewInstance(identifier);
   }

   // ====== Protected methods and attributes ===============================
   protected:
   // ------ Algorithm registry ---------------------------------------------
   static bool registerClass(const QString& identifier,
                             const QString& description,
                             FractalAlgorithmInterface* (*makeInstanceFunction)());

   // ------ Algorithm parameters -------------------------------------------
   unsigned int          Width;
   unsigned int          Height;
   unsigned int          MaxIterations;
   std::complex<double>  C1;
   std::complex<double>  C2;
   double                StepX;
   double                StepY;
   QList<ConfigEntry*>   ConfigEntries;

   // ====== Private attributes =============================================
   private:
   static ClassRegistry* Registry;
};

#endif
