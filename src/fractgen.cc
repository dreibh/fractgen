/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2021 by Thomas Dreibholz
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

#include "fractalgenerator.h"

#include <QtWidgets/QApplication>
#include <QFile>
#include <QTranslator>


// ###### Main program ######################################################
int main(int argc, char *argv[])
{
   QApplication application(argc, argv);
   application.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
   QTranslator applicationTranslator;
   if(!applicationTranslator.load(QLatin1String("fractgen_") + QLocale::system().name())) {
      applicationTranslator.load(QLatin1String("fractgen_") + QLocale::system().name(),
                                 QStringLiteral("%%PREFIX%%/share/fractgen"));
   }
   application.installTranslator(&applicationTranslator);

   FractalGeneratorApp* fractalGeneratorApp = nullptr;
   for(int i = 1;i < argc;i++) {
      const QString fileName = QString::fromLocal8Bit(argv[i]);
      if( (fractalGeneratorApp == nullptr) &&
          (fileName.right(4) == QStringLiteral(".fsf")) &&
          (QFile::exists(fileName)) ) {
         // Open file provided by argument ...
         fractalGeneratorApp = new FractalGeneratorApp(nullptr, fileName);
         fractalGeneratorApp->show();
      }
   }

   if(fractalGeneratorApp == nullptr) {
      // Start new image, if no file has been opened.
      fractalGeneratorApp = new FractalGeneratorApp(nullptr);
      fractalGeneratorApp->show();
   }

   return application.exec();
}
