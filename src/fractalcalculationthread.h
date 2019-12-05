/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2020 by Thomas Dreibholz
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

#ifndef FRACTALCALCULATIONTHREAD_H
#define FRACTALCALCULATIONTHREAD_H

#include "fractalalgorithminterface.h"
#include "colorschemeinterface.h"
#include "fractalbuffer.h"

#include <QThread>
#include <QImage>
#include <QObject>


/**
  * @author Thomas Dreibholz
  */
class FractalCalculationThread : public QThread {
   public:
   FractalCalculationThread(QObject*                   parent,
                            FractalAlgorithmInterface* algorithm,
                            ColorSchemeInterface*      colorScheme,
                            FractalBuffer*             buffer,
                            QImage*                    image,
                            unsigned int               progStep);
   ~FractalCalculationThread();
   void stop();

   private:
   void run() override;

   private:
   QObject*                   Parent;
   FractalAlgorithmInterface* Algorithm;
   ColorSchemeInterface*      ColorScheme;
   FractalBuffer*             Buffer;
   QImage*                    Image;
   unsigned int               MaxIterations;
   unsigned int               ProgStep;
   bool                       Stop;
};

#endif
