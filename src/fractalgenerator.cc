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

#include "fractalgenerator.h"
#include "fractalgeneratorview.h"
#include "fractalgeneratordoc.h"
#include "fractalalgorithminterface.h"
#include "colorschemeinterface.h"
#include "optionsdialog.h"

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
   connect(View, SIGNAL(updateFractalAlgorithm()), this, SLOT(slotUpdateFractalAlgorithm()));
   connect(View, SIGNAL(updateColorScheme()), this, SLOT(slotUpdateColorScheme()));
   connect(View, SIGNAL(updateZoomBackPossible()), this, SLOT(slotUpdateZoomBackPossible()));
   connect(View, SIGNAL(updateZoomInPossible()), this, SLOT(slotUpdateZoomInPossible()));

   Document = new FractalGeneratorDoc(this, View);
   Q_CHECK_PTR(Document);
   connect(Document, SIGNAL(updateFileName(const QString&)), this, SLOT(slotUpdateFileName(const QString&)));
   Document->newDocument();

   // ====== Create File menu ===============================================
   QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
   Q_CHECK_PTR(fileMenu);
   fileMenu->addAction(tr("&New"), this, SLOT(slotFileNew()), QKeySequence(QKeySequence::New));
   fileMenu->addAction(tr("&Open"), this, SLOT(slotFileOpen()), QKeySequence(QKeySequence::Open));
   fileMenu->addAction(tr("&Save"), this, SLOT(slotFileSave()), QKeySequence(QKeySequence::Save));
   fileMenu->addAction(tr("Save As ..."), this, SLOT(slotFileSaveAs()));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Export ..."), this, SLOT(slotFileExportImage()), QKeySequence(Qt::CTRL | Qt::Key_X));
   fileMenu->addAction(tr("&Print ..."), this, SLOT(slotFilePrint()), QKeySequence(QKeySequence::Print));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Close"), this, SLOT(slotFileClose()), QKeySequence(QKeySequence::Close));
   fileMenu->addAction(tr("&Quit"), this, SLOT(slotFileQuit()), QKeySequence(Qt::CTRL | Qt::Key_Q));

   // ====== Create View menu ===============================================
   QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
   Q_CHECK_PTR(viewMenu);
   ViewZoomIn = viewMenu->addAction(tr("Zoom &In"), View, SLOT(zoomIn()), QKeySequence(Qt::CTRL | Qt::Key_I));
   ViewZoomIn->setEnabled(false);
   ViewZoomBack = viewMenu->addAction(tr("Zoom &Back"), View, SLOT(zoomBack()), QKeySequence(QKeySequence::Undo));
   ViewZoomBack->setEnabled(false);
   viewMenu->addAction(tr("&Reset Zoom"), View, SLOT(zoomReset()), QKeySequence(Qt::CTRL | Qt::Key_R));
   viewMenu->addSeparator();
   viewMenu->addAction(tr("Image Size"), this, SLOT(slotViewSetImageSize()), QKeySequence(Qt::Key_F3));

   // ====== Create menu with the algorithms ================================
   QMenu* fractalAlgorithmMenu = menuBar()->addMenu(tr("&Algorithm"));
   Q_CHECK_PTR(fractalAlgorithmMenu);
   QAction* configureAlgorithmAction = fractalAlgorithmMenu->addAction(tr("Configure Algorithm ..."), this, SLOT(slotViewConfigureAlgorithm()), QKeySequence(Qt::Key_F2));
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
   helpMenu->addAction(tr("&About"), this, SLOT(slotHelpAbout()));

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
      if(QMessageBox::warning(this, QStringLiteral("FractGen II"),
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
   QMessageBox::information(this, QStringLiteral("FractGen"),
      QStringLiteral("FractGen\nCopyright (C) 2003-2024 by Thomas Dreibholz\nhttps://www.nntb.no/~dreibh/fractalgenerator/"),
      tr("&Okay"));
}


// ###### Set picture size ##################################################
void FractalGeneratorApp::slotViewSetImageSize()
{
   statusBar()->showMessage(tr("Changing Image Size ..."));

   const QString currentSize =
      QString().setNum(View->getSizeWidth()) +
      QStringLiteral("*") +
      QString().setNum(View->getSizeHeight());

   bool ok;
   QString text = QInputDialog::getText(
                     this,
                     tr("Image Size"),
                     tr("Please enter new size in the format x*y:"),
                     QLineEdit::Normal, currentSize, &ok);
   if((ok) || (!text.isEmpty())) {
      const unsigned int newX = text.section(QStringLiteral("*"), 0, 0).toUInt();
      const unsigned int newY = text.section(QStringLiteral("*"), 1, 1).toUInt();

      if((0 < newX) && (0 < newY)) {
         View->changeSize(newX, newY);
         View->configChanged();
      }
      else {
         QMessageBox::about(this, tr("Image Size"), tr("Invalid image size!"));
      }
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
   }

   statusBar()->showMessage(tr("Ready"));
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
void FractalGeneratorApp::slotUpdateFractalAlgorithm()
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
   setWindowTitle(fileName + QStringLiteral(" - FractGen II"));
}


// ###### Update Zoom In menu item ##########################################
void FractalGeneratorApp::slotUpdateZoomInPossible()
{
   const bool zoomInPossible = View->isZoomInPossible();
   ViewZoomIn->setEnabled(zoomInPossible);
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
