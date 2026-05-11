/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2026 by Thomas Dreibholz
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
#include "package-version.h"

#include <QCommandLineParser>
#include <QFile>
#include <QtGlobal>
#include <QTranslator>
#include <QtWidgets/QApplication>


// ###### Main program ######################################################
int main(int argc, char *argv[])
{
   // ====== Initialise =====================================================
   QApplication application(argc, argv);
#if QT_VERSION < 0x060000
   application.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#endif
   QTranslator applicationTranslator;
   if(!applicationTranslator.load(QLatin1String("fractgen_") + QLocale::system().name())) {
      if(!applicationTranslator.load(QLatin1String("fractgen_") + QLocale::system().name(),
                                     QStringLiteral(FRACTGEN_INSTALL_PREFIX) + QStringLiteral("/share/fractgen"))) {
         // No translations for this locale -> using built-in strings.
      }
   }
   application.installTranslator(&applicationTranslator);
#ifdef WITH_KDE
   QCoreApplication::setApplicationName(QStringLiteral("kfractgen"));
#else
   QCoreApplication::setApplicationName(QStringLiteral("fractgen"));
#endif
   QCoreApplication::setApplicationVersion(QStringLiteral(FRACTGEN_VERSION));

   // ====== Parse command-line arguments ===================================
   QCommandLineParser parser;
   parser.setApplicationDescription(QStringLiteral("Fractal Generator"));
   parser.addHelpOption();
   parser.addVersionOption();
   parser.addPositionalArgument(QStringLiteral("input_file"),
                                QStringLiteral("Input file."),
                                QStringLiteral("[input_file ...]"));
   parser.process(application);

   // ====== Open files given as arguments ==================================
   bool  openedAnyFile    = false;
   const QStringList args = parser.positionalArguments();
   for(const QString& fileName : args) {
      if(QFile::exists(fileName)) {
         // Open file provided by argument ...
         FractalGeneratorApp* fractalGeneratorApp =
            new FractalGeneratorApp(nullptr, fileName);
         Q_CHECK_PTR(fractalGeneratorApp);
         fractalGeneratorApp->show();
         openedAnyFile = true;
      }
      else {
         qWarning("WARNING: File %s does not exist!", qPrintable(fileName));
      }
   }

   // ====== Start the application ==========================================
   if(!openedAnyFile) {
      // Start new image, if no file has been opened.
      FractalGeneratorApp* fractalGeneratorApp =
         new FractalGeneratorApp(nullptr);
      Q_CHECK_PTR(fractalGeneratorApp);
      fractalGeneratorApp->show();
   }

   return application.exec();
}
