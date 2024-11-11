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

#include "fractalgeneratorviewbase.h"

#include <QtWidgets/QApplication>


// ###### Constructor #######################################################
FractalGeneratorViewBase::FractalGeneratorViewBase(QWidget*           parent,
                                                   const unsigned int width,
                                                   const unsigned int height,
                                                   const unsigned int progStep)
   : QWidget(parent)
{
   // ====== Initialise buffer ==============================================
   Buffer = new FractalBuffer();
   Q_CHECK_PTR(Buffer);

   // ====== Set up algorithm and color scheme ==============================
   Algorithm = FractalAlgorithmInterface::makeAlgorithmInstance(QStringLiteral("Mandelbrot"));
   Q_CHECK_PTR(Algorithm);
   ColorScheme = ColorSchemeInterface::makeColorSchemeInstance(QStringLiteral("SimpleHSV"));
   Q_CHECK_PTR(ColorScheme);
   C1        = Algorithm->defaultC1();
   C2        = Algorithm->defaultC2();
   ProgStep  = progStep;
   Width     = width;
   Height    = height;
   Algorithm->configure(Width, Height,
                        C1, C2,
                        Algorithm->defaultMaxIterations());
   ColorScheme->configure(Algorithm->getMaxIterations());
}


// ###### Destructor ########################################################
FractalGeneratorViewBase::~FractalGeneratorViewBase()
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   delete Buffer;
   Buffer = nullptr;
}


// ###### Configuration update ##############################################
void FractalGeneratorViewBase::configChanged()
{
   // Nothing to do here!
}


// ###### Change image size #################################################
void FractalGeneratorViewBase::changeSize(const unsigned int width,
                                          const unsigned int height)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change size ====================================================
   Width  = width;
   Height = height;
   Buffer->reset(Width, Height);
   Algorithm->changeSize(Width, Height);
}


// ###### Change C1 and C2 ##################################################
void FractalGeneratorViewBase::changeC1C2(const std::complex<double>& newC1,
                                          const std::complex<double>& newC2)
{
   stopCalculation();
   C1 = newC1;
   C2 = newC2;
}


// ###### Change fractal algorithm ##########################################
void FractalGeneratorViewBase::changeAlgorithm(const QString& identifier)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change algorithm ===============================================
   delete Algorithm;
   Algorithm = FractalAlgorithmInterface::makeAlgorithmInstance(identifier);
   Q_CHECK_PTR(Algorithm);
   C1 = Algorithm->defaultC1();
   C2 = Algorithm->defaultC2();
   Algorithm->configure(Width, Height,
                        C1, C2,
                        Algorithm->defaultMaxIterations());
   ColorScheme->configure(Algorithm->getMaxIterations());
   emit updateAlgorithm();
}


// ###### Change color scheme ###############################################
void FractalGeneratorViewBase::changeColorScheme(const QString& identifier)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change color scheme ============================================
   delete ColorScheme;
   ColorScheme = ColorSchemeInterface::makeColorSchemeInstance(identifier);
   Q_CHECK_PTR(ColorScheme);
   ColorScheme->configure(Algorithm->getMaxIterations());
   emit updateColorScheme();
}


// ###### Start calculation #################################################
void FractalGeneratorViewBase::startCalculation(QImage* image)
{
   if(ThreadList.size() == 0) {
      const unsigned int threads = QThread::idealThreadCount();
      for(unsigned int i = 0; i < threads; i++) {
         FractalCalculationThread* thread =
            new FractalCalculationThread(this,
                                         Algorithm, ColorScheme, Buffer,
                                         image,
                                         ProgStep,
                                         threads, i);
         Q_CHECK_PTR(thread);
         thread->start();
         ThreadList.append(thread);
      }
   }
}


// ###### Stop calculation ##################################################
void FractalGeneratorViewBase::stopCalculation()
{
   if(ThreadList.size() > 0) {
      foreach(FractalCalculationThread* thread, ThreadList) {
         thread->stop();
      }
      while(ThreadList.size() > 0) {
         qApp->processEvents();
      }
   }
}
