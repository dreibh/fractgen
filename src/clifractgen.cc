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

#include "fractalgenerator.h"
#include "fractalgeneratordoc.h"
#include "fractalgeneratorviewbase.h"

#include <QtWidgets/QApplication>


// ###### Main program ######################################################
int main(int argc, char *argv[])
{
   setenv("QT_QPA_PLATFORM", "offscreen", 1);
   QApplication application(argc, argv);

   unsigned int width  = 640;
   unsigned int height = 480;

   FractalGeneratorViewBase view(nullptr, width, height, 1);
   FractalGeneratorDoc document(nullptr, &view);
   if(document.openDocument("fractgen.fsf")) {
      QImage image(width, height, QImage::Format_RGB32);
      view.performCalculation(&image);
      image.save("result.png");
   }
   else puts("ERR");
}
