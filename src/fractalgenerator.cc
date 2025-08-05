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
#include "fractalgeneratorview.h"
#include "fractalgeneratordoc.h"
#include "fractalalgorithminterface.h"
#include "colorschemeinterface.h"
#include "optionsdialog.h"
#include "package-version.h"

#include <QActionGroup>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QDir>


struct StandardImageSize {
   QString      Description;
   unsigned int Width;
   unsigned int Height;
};

// https://en.wikipedia.org/wiki/Display_resolution_standards
static const StandardImageSize StandardImageSizes [] = {
   { QStringLiteral("640x480 (VGA, 4:3)"),                                  640,      480 },
   { QStringLiteral("1024x768 (XGA, 4:3)"),                                 1024,     768 },
   { QStringLiteral("1600x1200 (UXGA, 4:3)"),                               1600,    1200 },
   { QStringLiteral(), 0, 0 },
   { QStringLiteral("1920x1080 (FullHD, 16:9)"),                            1920,    1080 },
   { QStringLiteral("3840x2160 (4K UltraHD, 16:9)"),                        3840,    2160 },
   { QStringLiteral("7680x4320 (8K UltraHD, 16:9)"),                        7680,    4320 },
   { QStringLiteral(), 0, 0 },
   { QStringLiteral("1485x1050 (DIN A4 landscape, 5*5 px/mm^2)"),          5*297,   5*210 },
   { QStringLiteral("2100x1485 (DIN A3 landscape, 5*5 px/mm^2)"),          5*420,   5*297 },
   { QStringLiteral("2970x2100 (DIN A4 landscape, 10*10 px/mm^2)"),       10*297,  10*210 },
   { QStringLiteral("4200x2970 (DIN A3 landscape, 10*10 px/mm^2)"),       10*420,  10*297 },
   { QStringLiteral("14850x10500 (DIN A4 landscape, 50*50 px/mm^2) ⚠"),   50*297,  50*210 },
   { QStringLiteral("21000x14850 (DIN A3 landscape, 50*50 px/mm^2) ⚠"),   50*420,  50*297 },
   { QStringLiteral(), 0, 0 },
   { QStringLiteral("1050x1485 (DIN A4 portrait, 5*5 px/mm^2)"),           5*210,   5*297 },
   { QStringLiteral("1485x2100 (DIN A3 portrait, 5*5 px/mm^2)"),           5*297,   5*420 },
   { QStringLiteral("2100x2970 (DIN A4 portrait, 10*10 px/mm^2)"),        10*210,  10*297 },
   { QStringLiteral("2970x4200 (DIN A3 portrait, 10*10 px/mm^2)"),        10*297,  10*420 },
   { QStringLiteral("10500x14850 (DIN A4 portrait, 50*50 px/mm^2) ⚠"),    50*210,  50*297 },
   { QStringLiteral("14850x21000 (DIN A3 portrait, 50*50 px/mm^2) ⚠"),    50*297,  50*420 },
};


// ###### Constructor #######################################################
FractalGeneratorApp::FractalGeneratorApp(QWidget*       parent,
                                         const QString& fileName)
#ifndef WITH_KDE
   : QMainWindow(parent)
#else
   : KXmlGuiWindow(parent)
#endif
{
   // ====== Create widgets =================================================
   View = new FractalGeneratorView(this);
   Q_CHECK_PTR(View);
   setCentralWidget(View);
   connect(View, SIGNAL(updateAlgorithm()),        this, SLOT(slotUpdateAlgorithm()));
   connect(View, SIGNAL(updateColorScheme()),      this, SLOT(slotUpdateColorScheme()));
   connect(View, SIGNAL(updateZoomBackPossible()), this, SLOT(slotUpdateZoomBackPossible()));
   connect(View, SIGNAL(updateZoomInPossible()),   this, SLOT(slotUpdateZoomInPossible()));

   Document = new FractalGeneratorDoc(this, View);
   Q_CHECK_PTR(Document);
   connect(Document, SIGNAL(updateFileName(const QString&)), this, SLOT(slotUpdateFileName(const QString&)));
   Document->newDocument();

   // ====== Create File menu ===============================================
   QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
   Q_CHECK_PTR(fileMenu);
   fileMenu->addAction(tr("&New"),        QKeySequence(QKeySequence::New),    this, SLOT(slotFileNew()));
   fileMenu->addAction(tr("&Open"),       QKeySequence(QKeySequence::Open),   this, SLOT(slotFileOpen()));
   fileMenu->addAction(tr("&Save"),       QKeySequence(QKeySequence::Save),   this, SLOT(slotFileSave()));
   fileMenu->addAction(tr("Save As ..."), QKeySequence(QKeySequence::SaveAs), this, SLOT(slotFileSaveAs()));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Export ..."), QKeySequence(Qt::CTRL | Qt::Key_X), this, SLOT(slotFileExportImage()));
   fileMenu->addAction(tr("&Print ..."),  QKeySequence(QKeySequence::Print),  this, SLOT(slotFilePrint()));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Close"),      QKeySequence(QKeySequence::Close),  this, SLOT(slotFileClose()));
   fileMenu->addAction(tr("&Quit"),       QKeySequence(QKeySequence::Quit),   this, SLOT(slotFileQuit()));

   // ====== Create View menu ===============================================
   QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
   Q_CHECK_PTR(viewMenu);
   viewMenu->addAction(tr("&Copy"),       QKeySequence(QKeySequence::Copy),   View, SLOT(copyToClipboard()));
   ViewCopySelection = viewMenu->addAction(tr("Copy Selection"), View, SLOT(copySelectionToClipboard()));
   ViewCopySelection->setEnabled(false);
   viewMenu->addSeparator();
   ViewZoomIn        = viewMenu->addAction(tr("Zoom &In"),   QKeySequence(QKeySequence::ZoomIn),  View, SLOT(zoomInToSelection()));
   ViewZoomIn->setEnabled(false);
   ViewZoomBack      = viewMenu->addAction(tr("Zoom &Back"), QKeySequence(QKeySequence::ZoomOut), View, SLOT(zoomBack()));
   ViewZoomBack->setEnabled(false);
   viewMenu->addSeparator();
   viewMenu->addAction(tr("&Reset Zoom"), QKeySequence(Qt::CTRL | Qt::Key_R), View, SLOT(zoomReset()));

   // ====== Create menu with image size settings ===========================
   QMenu* formatMenu = menuBar()->addMenu(tr("&Format"));
   Q_CHECK_PTR(formatMenu);

   CustomSizeItem = formatMenu->addAction(tr("Custom Image Size"), QKeySequence(Qt::Key_F3), this, SLOT(slotViewSetImageSize()));
   CustomSizeItem->setCheckable(true);
   CustomSizeItem->setChecked(true);
   formatMenu->addAction(tr("Swap Width and Height"), QKeySequence(Qt::Key_F10), this, SLOT(slotViewSwapWidthHeight()));
   formatMenu->addSeparator();

   QActionGroup* formatGroup = new QActionGroup(this);
   Q_CHECK_PTR(formatGroup);
   for(unsigned int i = 0; i < sizeof(StandardImageSizes) / sizeof(StandardImageSizes[0]); i++ ) {
      if(StandardImageSizes[i].Description != QStringLiteral()) {
         QAction* item = formatMenu->addAction(StandardImageSizes[i].Description);
         Q_CHECK_PTR(item);
         formatGroup->addAction(item);
         item->setData(StandardImageSizes[i].Description);
         item->setCheckable(true);
         FormatItems.append(item);
      }
      else {
         formatMenu->addSeparator();
      }
   }
   connect(formatGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotViewSetImageSize(QAction*)));

   // ====== Create menu with the algorithms ================================
   QMenu* fractalAlgorithmMenu = menuBar()->addMenu(tr("&Algorithm"));
   Q_CHECK_PTR(fractalAlgorithmMenu);
   fractalAlgorithmMenu->addAction(tr("Configure Algorithm ..."), QKeySequence(Qt::Key_F2), this, SLOT(slotViewConfigureAlgorithm()));
   fractalAlgorithmMenu->addSeparator();

   QActionGroup* fractalAlgorithmGroup = new QActionGroup(this);
   Q_CHECK_PTR(fractalAlgorithmGroup);
   const QMap<QString, ClassRegistry::Registration*>& fractalAlgorithmMap =
      FractalAlgorithmInterface::getAlgorithms();
   for(auto iterator = fractalAlgorithmMap.cbegin();
       iterator != fractalAlgorithmMap.end(); iterator++) {
      QAction* item = fractalAlgorithmMenu->addAction((*iterator)->Description);
      Q_CHECK_PTR(item);
      fractalAlgorithmGroup->addAction(item);
      item->setData((*iterator)->Identifier);
      item->setCheckable(true);
      item->setChecked( (*iterator)->Identifier == View->getAlgorithm()->getIdentifier() );
      FractalAlgorithmActionList.append(item);
   }
   connect(fractalAlgorithmGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotViewSetFractalAlgorithm(QAction*)));

   // ====== Create menu with the color schemes =============================
   QMenu* colorSchemeMenu = menuBar()->addMenu(tr("&Color Scheme"));
   Q_CHECK_PTR(colorSchemeMenu);

   QActionGroup* colorSchemeGroup = new QActionGroup(this);
   Q_CHECK_PTR(colorSchemeGroup);
   const QMap<QString, ClassRegistry::Registration*>& colorSchemeMap =
      ColorSchemeInterface::getColorSchemes();
   for(auto iterator = colorSchemeMap.cbegin();
       iterator != colorSchemeMap.end(); iterator++) {
      QAction* item = colorSchemeMenu->addAction((*iterator)->Description);
      Q_CHECK_PTR(item);
      colorSchemeGroup->addAction(item);
      item->setData((*iterator)->Identifier);
      item->setCheckable(true);
      item->setChecked( (*iterator)->Identifier == View->getColorScheme()->getIdentifier() );
      ColorSchemeActionList.append(item);
   }
   connect(colorSchemeGroup, SIGNAL(triggered(QAction*)), this, SLOT(slotViewSetColorScheme(QAction*)));

   // ====== Create Help menu ===============================================
   QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
   Q_CHECK_PTR(helpMenu);
   helpMenu->addAction(tr("&About"),    this, SLOT(slotHelpAbout()));
   helpMenu->addAction(tr("About &Qt"), this, SLOT(slotHelpAboutQt()));

   // ====== Further setup ==================================================
   Printer.setColorMode(QPrinter::Color);
   Printer.setPageOrientation(QPageLayout::Landscape);
   Printer.setOutputFileName(tr("Fractal.pdf"));

   statusBar()->showMessage(tr("Welcome to FractGen!"), 3000);

   // ====== Load file, if provided =========================================
   if(!fileName.isEmpty()) {
      Document->openDocument(fileName);
   }

   // ====== Finally, show the window =======================================
   show();
}


// ###### Destructor ########################################################
FractalGeneratorApp::~FractalGeneratorApp()
{
}


// ###### Open ##############################################################
void FractalGeneratorApp::slotFileNew()
{
   FractalGeneratorApp* fractalGeneratorApp = new FractalGeneratorApp(nullptr);
   Q_CHECK_PTR(fractalGeneratorApp);
   fractalGeneratorApp->show();
}


// ###### Open ##############################################################
void FractalGeneratorApp::slotFileOpen()
{
   statusBar()->showMessage(tr("Opening file ..."));
   const QString fileName = QFileDialog::getOpenFileName(
                               this, tr("Open File ..."),
                               QDir::currentPath(),
                               tr("FractGen File (*.fsf)"));
   if(!fileName.isEmpty()) {
      Document->openDocument(fileName);
   }
   statusBar()->showMessage(tr("Ready"));
}


// ###### Save as ###########################################################
void FractalGeneratorApp::slotFileSave()
{
   statusBar()->showMessage(tr("Saving file..."));
   bool overwrite = true;
   if(QFile::exists(Document->getFileName())) {
      if(QMessageBox::warning(this, QStringLiteral("FractGen"),
                              tr("Overwrite existing file?"),
                              QMessageBox::Save|QMessageBox::Cancel, QMessageBox::Save) == QMessageBox::Cancel) {
         overwrite = false;
      }
   }
   if(overwrite) {
      Document->saveDocument(Document->getFileName());
   }
   statusBar()->showMessage(tr("Ready"));
}


// ###### Save ##############################################################
void FractalGeneratorApp::slotFileSaveAs()
{
   statusBar()->showMessage(tr("Saving file as ..."));
   const QString fileName = QFileDialog::getSaveFileName(
                               this, tr("Save File ..."),
                               QDir::currentPath(),
                               tr("FractGen File (*.fsf)"));
   if(!fileName.isEmpty()) {
      Document->saveDocument(fileName);
   }
   statusBar()->showMessage(tr("Ready"));
}


// ###### Export ############################################################
void FractalGeneratorApp::slotFileExportImage()
{
   statusBar()->showMessage(tr("Exporting Image ..."));

   QString name = QFileDialog::getSaveFileName(this, tr("Export Image"),
                                               QDir::currentPath(),
                                               QStringLiteral("*.png"));
   if(!name.isEmpty()) {
      if(name.right(4).toLower() != QStringLiteral(".png")) {
         name += QStringLiteral(".png");
      }
      View->getDisplay()->saveImage(name, "PNG");
   }

   statusBar()->showMessage(tr("Ready"));
}


// ###### Close #############################################################
void FractalGeneratorApp::slotFileClose()
{
   close();
}


// ###### Print #############################################################
void FractalGeneratorApp::slotFilePrint()
{
   statusBar()->showMessage(tr("Printing..."));

   QPrintDialog printDialog(&Printer, this);
   if(printDialog.exec() == QDialog::Accepted) {
      View->print(&Printer);
   }

   statusBar()->showMessage(tr("Ready"));
}


// ###### Quit ##############################################################
void FractalGeneratorApp::slotFileQuit()
{
   exit(0);
}


// ###### About #############################################################
void FractalGeneratorApp::slotHelpAbout()
{
   QMessageBox about(this);
   about.setWindowTitle(QStringLiteral("FractGen"));
   about.setTextFormat(Qt::RichText);
   about.setText(QStringLiteral(
      "<p><center><strong>%1 %2</strong></center></p>"
      "<p>%3</p>"
      "<p><a href=\"%4\">%4</a></p>").arg(
         QStringLiteral("FractGen"),
         QStringLiteral(FRACTGEN_VERSION),
         QStringLiteral("Copyright (C) 2003-2025 by Thomas Dreibholz"),
         QStringLiteral("https://www.nntb.no/~dreibh/fractalgenerator/")
      )
   );
   about.exec();
}


// ###### About Qt ##########################################################
void FractalGeneratorApp::slotHelpAboutQt()
{
   QMessageBox::aboutQt(this, QStringLiteral("FractGen"));
}


// ###### Configure algorithm ###############################################
void FractalGeneratorApp::slotViewConfigureAlgorithm()
{
   statusBar()->showMessage(tr("Changing Options ..."));
   OptionsDialog dialog(this, View->getAlgorithm()->getConfigEntries());
   dialog.exec();
   View->configChanged();
   statusBar()->showMessage(tr("Ready"));
}


// ###### Update algorithm ##################################################
void FractalGeneratorApp::slotUpdateAlgorithm()
{
   const FractalAlgorithmInterface* currentAlgorithm = View->getAlgorithm();
   QListIterator<QAction*> iterator(FractalAlgorithmActionList);
   while(iterator.hasNext()) {
      QAction* item = iterator.next();
      item->setChecked( item->data() == currentAlgorithm->getIdentifier() );
   }
}


// ###### Update color scheme ###############################################
void FractalGeneratorApp::slotUpdateColorScheme()
{
   const ColorSchemeInterface* currentAlgorithm = View->getColorScheme();
   QListIterator<QAction*> iterator(ColorSchemeActionList);
   while(iterator.hasNext()) {
      QAction* item = iterator.next();
      item->setChecked( item->data() == currentAlgorithm->getIdentifier() );
   }
}


// ###### Update file name ##################################################
void FractalGeneratorApp::slotUpdateFileName(const QString& fileName)
{
   setWindowTitle(fileName + QStringLiteral(" - FractGen"));
}


// ###### Copy selection to clipboard #######################################
void FractalGeneratorApp::slotCopyToClipboard()
{
   View->copyToClipboard();
}


// ###### Update Zoom In menu item ##########################################
void FractalGeneratorApp::slotUpdateZoomInPossible()
{
   const bool zoomInPossible = View->isZoomInPossible();
   ViewZoomIn->setEnabled(zoomInPossible);
   ViewCopySelection->setEnabled(zoomInPossible);
   if(zoomInPossible) {
      statusBar()->showMessage(tr("Click middle mouse button or choose \"View -> Zoom In\" to magnify selected area!"));
   }
   else {
      statusBar()->showMessage(tr("Ready"));
   }
}


// ###### Update Zoom Back menu item ########################################
void FractalGeneratorApp::slotUpdateZoomBackPossible()
{
   ViewZoomBack->setEnabled(View->isZoomBackPossible());
}


// ###### Set image size ####################################################
void FractalGeneratorApp::slotViewSetImageSize()
{
   statusBar()->showMessage(tr("Changing Image Size ..."));

   const QString currentSize =
      QString().setNum(View->getWidth()) +
      QStringLiteral("*") +
      QString().setNum(View->getHeight());

   bool ok;
   QString text = QInputDialog::getText(
                     this,
                     tr("Image Size"),
                     tr("Please enter new size in the format x*y:"),
                     QLineEdit::Normal, currentSize, &ok);
   if((ok) || (!text.isEmpty())) {
      const unsigned int newWidth = text.section(QStringLiteral("*"), 0, 0).toUInt();
      const unsigned int newHeight = text.section(QStringLiteral("*"), 1, 1).toUInt();

      if( (newWidth  >= 1) && (newWidth  <= 65536) &&
          (newHeight >= 1) && (newHeight <= 65536) ) {
         View->changeSize(newWidth, newHeight);
         View->configChanged();
      }
      else {
         QMessageBox::about(this, tr("Image Size"), tr("Invalid image size!"));
      }
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
      for(auto iterator = FormatItems.begin(); iterator != FormatItems.end(); iterator++) {
         (*iterator)->setChecked(false);
      }
   }

   statusBar()->showMessage(tr("Ready"));
}


// ###### Set image size from preconfiguration ##############################
void FractalGeneratorApp::slotViewSetImageSize(QAction* action)
{
   const QString description = action->data().toString();
   for(unsigned int i = 0; i < sizeof(StandardImageSizes) / sizeof(StandardImageSizes[0]); i++ ) {
      if(StandardImageSizes[i].Description == description) {
         if( (View->getWidth()  != StandardImageSizes[i].Width) ||
             (View->getHeight() != StandardImageSizes[i].Height) ) {
            View->changeSize(StandardImageSizes[i].Width,
                           StandardImageSizes[i].Height);
            CustomSizeItem->setChecked(false);
            View->configChanged();
            return;
         }
      }
   }
}


// ###### Swap width and height #############################################
void FractalGeneratorApp::slotViewSwapWidthHeight()
{
   const unsigned int newWidth = View->getHeight();
   const unsigned int newHeight = View->getWidth();
   if(newWidth != newHeight) {
      View->changeSize(newWidth, newHeight);
      View->configChanged();
   }
}


// ###### Set algorithm #####################################################
void FractalGeneratorApp::slotViewSetFractalAlgorithm(QAction* action)
{
   View->changeAlgorithm(action->data().toString());
   View->configChanged();
   ViewZoomBack->setEnabled(View->isZoomBackPossible());
}


// ###### Set color scheme ##################################################
void FractalGeneratorApp::slotViewSetColorScheme(QAction* action)
{
   View->changeColorScheme(action->data().toString());
   View->configChanged();
   ViewZoomBack->setEnabled(View->isZoomBackPossible());
}
