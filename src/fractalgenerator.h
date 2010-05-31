/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2010 by Thomas Dreibholz
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

#ifndef FRACTALGENERATOR_H
#define FRACTALGENERATOR_H


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QApplication>
#include <QMainWindow>
#include <QAction>
#include <QPrinter>


class FractalGeneratorDoc;
class FractalGeneratorView;


class FractalGeneratorApp : public QMainWindow
{
   Q_OBJECT

   friend class FractalGeneratorView;

   public:
   FractalGeneratorApp(QWidget* parent, const QString& fileName = "");
   ~FractalGeneratorApp();

   protected:
   void initActions();
   void initStatusBar();
   void initDocument();
   void initView();

   public slots:
   void slotFileOpen();
   void slotFileSave();
   void slotFileExportImage();
   void slotFileSaveAs();
   void slotFileClose();
   void slotFilePrint();
   void slotFileQuit();
   void slotHelpAbout();

   void slotViewSetImageSize();
   void slotViewConfigureAlgorithm();
   void slotViewSetFractalAlgorithm(QAction* action);
   void slotViewSetColorScheme(QAction* action);

   void slotUpdateFileName(const QString& fileName);
   void slotUpdateFractalAlgorithm();
   void slotUpdateColorScheme();
   void slotUpdateZoomBackPossible();
   void slotUpdateZoomInPossible();

   private:
   FractalGeneratorView* View;
   FractalGeneratorDoc*  Document;
   QAction*              ViewZoomIn;
   QAction*              ViewZoomBack;
   QList<QAction*>       FractalAlgorithmActionList;
   QList<QAction*>       ColorSchemeActionList;
   QPrinter              Printer;
};

#endif // FRACTALGENERATOR_H
