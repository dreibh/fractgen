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

#include "fractalcalculationthread.h"

#include <QEvent>
#include <QCoreApplication>


// ###### Constructor #######################################################
FractalCalculationThread::FractalCalculationThread(QObject*                   parent,
                                                   FractalAlgorithmInterface* algorithm,
                                                   ColorSchemeInterface*      colorScheme,
                                                   FractalBuffer*             buffer,
                                                   QImage*                    image,
                                                   const unsigned int         progStep,
                                                   const unsigned int         interleave,
                                                   const unsigned int         offset)
 : Parent(parent),
   Algorithm(algorithm),
   ColorScheme(colorScheme),
   Buffer(buffer),
   Image(image),
   ProgStep(progStep),
   Interleave(interleave),
   Offset(offset),
   MaxIterations(*(Algorithm->getMaxIterations()))
{
   Stop = false;
}


// ###### Destructor ########################################################
FractalCalculationThread::~FractalCalculationThread()
{
   wait();
}


// ###### Thread main function ##############################################
#include <QAtomicInteger>
static QAtomicInteger nnn=0;
void FractalCalculationThread::run()
{
   const unsigned int width  = Image->width();
   const unsigned int height = Image->height();

   for(unsigned int step = ProgStep; step >= 1; step /= 2) {
      for(unsigned int iy = Offset * ProgStep; iy < height; iy += ProgStep * Interleave) {
         for(unsigned int y = iy; y < iy + ProgStep; y += step) {
            for(unsigned int x = 0; x < width; x += step) {
               if(Buffer->getPoint(x, y) == (unsigned int)~0) {
                  const unsigned int value = Algorithm->calculatePoint(x, y);
                  Buffer->setPoint(x, y, value);
                  nnn++;

                  const unsigned int rgb = ColorScheme->getColor(value);
                  for(unsigned int vy = y; vy < std::min(y + step, height); vy++) {
                     for(unsigned int vx = x; vx < std::min(x + step, width); vx++) {
                        Image->setPixel(vx, vy, rgb);
                     }
                  }
                  if(Stop) {
                     goto finished;
                  }
               }
            }
         }
      }
      QCoreApplication::postEvent(Parent, new QEvent(QEvent::User));
   }

finished:
   QCoreApplication::postEvent(Parent, new QEvent((QEvent::Type)(QEvent::User + 1)));
}


// ###### Stop thread and wait until it has really finished #################
void FractalCalculationThread::stop()
{
   Stop = true;
   wait();
   Stop = false;
}
