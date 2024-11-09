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

#ifndef FRACTALGENERATOR_H
#define FRACTALGENERATOR_H

#include <QtWidgets/QMainWindow>
#include <QtPrintSupport/QPrinter>
#ifdef WITH_KDE
#include <KXmlGuiWindow>
#endif


class FractalGeneratorDoc;
class FractalGeneratorView;


class FractalGeneratorApp
#ifndef WITH_KDE
   : public QMainWindow
#else
   : public KXmlGuiWindow
#endif
{
   Q_OBJECT

   friend class FractalGeneratorView;

   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorApp(QWidget* parent, const QString& fileName = QString());
   ~FractalGeneratorApp();

   // ====== Slots ==========================================================
   public Q_SLOTS:
   void slotFileNew();
   void slotFileOpen();
   void slotFileSave();
   void slotFileSaveAs();
   void slotFileExportImage();
   void slotFileClose();
   void slotFilePrint();
   void slotFileQuit();
   void slotHelpAbout();

   void slotCopyToClipboard();
   void slotViewSetImageSize();
   void slotViewSetImageSize(QAction* action);
   void slotViewSwapWidthHeight();
   void slotViewConfigureAlgorithm();
   void slotViewSetFractalAlgorithm(QAction* action);
   void slotViewSetColorScheme(QAction* action);

   void slotUpdateFileName(const QString& fileName);
   void slotUpdateFractalAlgorithm();
   void slotUpdateColorScheme();
   void slotUpdateZoomBackPossible();
   void slotUpdateZoomInPossible();

   // ====== Private attributes =============================================
   private:
   FractalGeneratorDoc*  Document;
   FractalGeneratorView* View;
   QAction*              ViewCopySelection;
   QAction*              ViewZoomIn;
   QAction*              ViewZoomBack;
   QList<QAction*>       FractalAlgorithmActionList;
   QList<QAction*>       ColorSchemeActionList;
   QPrinter              Printer;
   QList<QAction*>       FormatItems;
   QAction*              CustomSizeItem;
};

#endif
