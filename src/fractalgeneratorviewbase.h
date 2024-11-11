/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2025 by Thomas Dreibholz
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

#ifndef FRACTALGENERATORVIEWBASE_H
#define FRACTALGENERATORVIEWBASE_H

#include "fractalbuffer.h"
#include "fractalalgorithminterface.h"
#include "fractalcalculationthread.h"
#include "colorschemeinterface.h"

#include <QtWidgets/QWidget>


class FractalGeneratorDoc;
class FractalGeneratorApp;


class FractalGeneratorViewBase : public QWidget
{
   Q_OBJECT
   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorViewBase(QWidget*           parent,
                            const unsigned int width,
                            const unsigned int height,
                            const unsigned int progStep = 8);
   ~FractalGeneratorViewBase();

   // ====== Access methods =================================================
   inline FractalAlgorithmInterface* getAlgorithm() const { return Algorithm;   }
   inline ColorSchemeInterface* getColorScheme() const    { return ColorScheme; }
   inline unsigned int getWidth() const                   { return Width;       }
   inline unsigned int getHeight() const                  { return Height;      }

   virtual void configChanged();
   virtual void changeSize(const unsigned int width, const unsigned int height);
   virtual void changeAlgorithm(const QString& identifier);
   void changeColorScheme(const QString& identifier);
   void changeC1C2(const std::complex<double>& newC1,
                   const std::complex<double>& newC2);

   inline void performCalculation(QImage* image) {
      puts("T1");
      startCalculation(image);
      puts("T2");
      stopCalculation();
      puts("T3");
   }

   // ====== Signals ========================================================
   Q_SIGNALS:
   void updateAlgorithm();
   void updateColorScheme();

   // ====== Protected methods and attributes ===============================
   protected:
   virtual void startCalculation(QImage* image);
   virtual void stopCalculation();

   FractalBuffer*                   Buffer;
   FractalAlgorithmInterface*       Algorithm;
   ColorSchemeInterface*            ColorScheme;
   QList<FractalCalculationThread*> ThreadList;

   unsigned int                     ProgStep;
   unsigned int                     Width;
   unsigned int                     Height;
   std::complex<double>             C1;
   std::complex<double>             C2;
};

#endif
