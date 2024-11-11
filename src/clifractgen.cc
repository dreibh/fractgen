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

#include "fractalgeneratordoc.h"
#include "fractalgeneratorviewbase.h"
#include "package-version.h"

#include <iostream>
#include <QtWidgets/QApplication>
#include <QCommandLineParser>


// ###### Main program ######################################################
int main(int argc, char *argv[])
{
   setenv("QT_QPA_PLATFORM", "offscreen", 1);
   QApplication application(argc, argv);
   QCoreApplication::setApplicationName("clifractgen");
   QCoreApplication::setApplicationVersion(FRACTGEN_VERSION);

   // ====== Parse command-line arguments ===================================
   QCommandLineParser parser;
   parser.setApplicationDescription("Test helper");
   parser.addHelpOption();
   parser.addVersionOption();
   parser.addPositionalArgument("input_file" , QCoreApplication::translate("main", "Input FSF file"));
   parser.addPositionalArgument("output_file", QCoreApplication::translate("main", "Output graphics file"));

   QCommandLineOption widthOption(QStringList() << "W" << "width",
                                  QCoreApplication::translate("main", "Width"));
   widthOption.setValueName("width");
   widthOption.setDefaultValue("1024");
   parser.addOption(widthOption);

   QCommandLineOption heightOption(QStringList() << "H" << "height",
                                   QCoreApplication::translate("main", "Height"));
   heightOption.setValueName("height");
   heightOption.setDefaultValue("768");
   parser.addOption(heightOption);

   QCommandLineOption maxIterationsOption(QStringList() << "M" << "maxIterations",
                                          QCoreApplication::translate("main", "Max Interations"));
   maxIterationsOption.setValueName("maxIterations");
   maxIterationsOption.setDefaultValue("250");
   parser.addOption(maxIterationsOption);

   // ====== Check command-line arguments ===================================
   parser.process(application);
   const QStringList  args          = parser.positionalArguments();
   const QString&     inputFile     = args[0];
   const QString&     outputFile    = args[1];
   const unsigned int width         = parser.value(widthOption).toUInt();
   const unsigned int height        = parser.value(heightOption).toUInt();
   const unsigned int maxIterations = parser.value(maxIterationsOption).toUInt();
   if( (width  < 1) || (width  > 65536) || (height < 1) || (height > 65536) ) {
      std::cerr << "ERROR: Bad width/height settings!\n";
      return 1;
   }

   // ====== Perform calculation and save result ============================
   FractalGeneratorViewBase view(nullptr, width, height, 1);
   FractalGeneratorDoc document(nullptr, &view);
   if(document.openDocument(inputFile)) {
      std::cout << inputFile.toLocal8Bit().data() << " -> "
                << outputFile.toLocal8Bit().data() << " (size "
                << width << "x" << height << ", maxIterations "
                << maxIterations << ") ... ";
      std::cout.flush();

      QImage image(width, height, QImage::Format_RGB32);
      *(view.getAlgorithm()->getMaxIterations()) = maxIterations;
      view.performCalculation(&image);
      const bool success = image.save(outputFile);

      if(success) {
         std::cout << "done\n";
         return 0;
      }
      else {
         std::cout << "failed!\n";
      }
   }
   return 1;
}
