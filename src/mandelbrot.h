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

#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <fractalalgorithminterface.h>


/**
  *@author Thomas Dreibholz
  */
class Mandelbrot : public FractalAlgorithmInterface  {
   // ====== Constructor/Destructor =========================================
   public:
   Mandelbrot();
   ~Mandelbrot();

   // ====== Algorithm information ==========================================
   virtual const QString& getIdentifier()  const override;
   virtual const QString& getDescription() const override;

   virtual std::complex<double> defaultC1() const override;
   virtual std::complex<double> defaultC2() const override;

   // ====== The actual calculation =========================================
   virtual unsigned int calculatePoint(const unsigned int x,
                                       const unsigned int y) override;

   // ====== Private methods and attributes =================================
   private:
   static FractalAlgorithmInterface* makeNewInstance();

   static const QString Identifier;
   static const QString Description;
   static const bool    Registered;
};

#endif
