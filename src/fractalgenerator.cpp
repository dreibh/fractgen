/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2011 by Thomas Dreibholz
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
#include "fractalgeneratorview.h"
#include "fractalgeneratordoc.h"
#include "fractalalgorithminterface.h"
#include "colorschemeinterface.h"
#include "optionsdialog.h"

#include <QDir>
#include <QPainter>
#include <QStatusBar>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QPrintDialog>


// ###### Constructor #######################################################
FractalGeneratorApp::FractalGeneratorApp(QWidget* parent, const QString& fileName)
   : QMainWindow(parent)
{
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

   QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
   Q_CHECK_PTR(fileMenu);
   fileMenu->addAction(tr("&Open"), this, SLOT(slotFileOpen()), QKeySequence(QKeySequence::Open));
   fileMenu->addAction(tr("&Save"), this, SLOT(slotFileSave()), QKeySequence(QKeySequence::Save));
   fileMenu->addAction(tr("Save As"), this, SLOT(slotFileSaveAs()));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Export Image"), this, SLOT(slotFileExportImage()), QKeySequence(Qt::CTRL + Qt::Key_X));
   fileMenu->addAction(tr("Print &Image"), this, SLOT(slotFilePrint()), QKeySequence(QKeySequence::Print));
   fileMenu->addSeparator();
   fileMenu->addAction(tr("&Close"), this, SLOT(slotFileClose()), QKeySequence(QKeySequence::Close));
   fileMenu->addAction(tr("&Quit"), this, SLOT(slotFileQuit()), QKeySequence(Qt::CTRL + Qt::Key_Q));

   QMenu* viewMenu = menuBar()->addMenu(tr("&View"));
   Q_CHECK_PTR(viewMenu);
   ViewZoomIn = viewMenu->addAction(tr("Zoom &In"), View, SLOT(zoomIn()), QKeySequence(Qt::CTRL + Qt::Key_I));
   ViewZoomIn->setEnabled(false);
   ViewZoomBack = viewMenu->addAction(tr("Zoom &Back"), View, SLOT(zoomBack()), QKeySequence(QKeySequence::Undo));
   ViewZoomBack->setEnabled(false);
   viewMenu->addAction(tr("&Reset Zoom"), View, SLOT(zoomReset()), QKeySequence(Qt::CTRL + Qt::Key_R));
   viewMenu->addSeparator();
   viewMenu->addAction(tr("Image Size"), this, SLOT(slotViewSetImageSize()), QKeySequence(Qt::Key_F3));

   QMenu* fractalAlgorithmMenu = menuBar()->addMenu(tr("&Algorithm"));
   Q_CHECK_PTR(fractalAlgorithmMenu);
   QAction* configureAlgorithmAction = fractalAlgorithmMenu->addAction(tr("Configure Algorithm"), this, SLOT(slotViewConfigureAlgorithm()), QKeySequence(Qt::Key_F2));
   configureAlgorithmAction->setData(1000000);
   fractalAlgorithmMenu->addSeparator();

   QActionGroup* fractalAlgorithmGroup = new QActionGroup(this);
   Q_CHECK_PTR(fractalAlgorithmGroup);
   FractalAlgorithmInterface* fractalAlgorithm;
   QStringList                fractalAlgorithmList;
   unsigned int               fractalAlgorithmID = 0;
   while((fractalAlgorithm = FractalAlgorithmInterface::getAlgorithm(fractalAlgorithmID))) {
      QAction* item = fractalAlgorithmMenu->addAction(fractalAlgorithm->getName());
      Q_CHECK_PTR(item);
      fractalAlgorithmGroup->addAction(item);
      item->setData(fractalAlgorithmID);
      item->setCheckable(true);
      item->setChecked((fractalAlgorithmID == 0));
      FractalAlgorithmActionList.append(item);
      fractalAlgorithmID++;
   }
   connect(fractalAlgorithmMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotViewSetFractalAlgorithm(QAction*)));

   QMenu* colorSchemeMenu = menuBar()->addMenu(tr("&Color Scheme"));
   Q_CHECK_PTR(colorSchemeMenu);
   QActionGroup* colorSchemeGroup = new QActionGroup(this);
   ColorSchemeInterface* colorScheme;
   QStringList           colorSchemeList;
   unsigned int          colorSchemeID = 0;
   while((colorScheme = ColorSchemeInterface::getColorScheme(colorSchemeID))) {
      QAction* item = colorSchemeMenu->addAction(colorScheme->getName());
      Q_CHECK_PTR(item);
      colorSchemeGroup->addAction(item);
      item->setData(colorSchemeID);
      item->setCheckable(true);
      item->setChecked((colorSchemeID == 0));
      ColorSchemeActionList.append(item);
      colorSchemeID++;
   }
   connect(colorSchemeMenu, SIGNAL(triggered(QAction*)), this, SLOT(slotViewSetColorScheme(QAction*)));

   QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
   Q_CHECK_PTR(helpMenu);
   helpMenu->addAction(tr("&About"), this, SLOT(slotHelpAbout()));

   Printer.setColorMode(QPrinter::Color);
   Printer.setOrientation(QPrinter::Landscape);
   Printer.setOutputFileName(tr("Fractal.pdf"));

   statusBar()->showMessage("Welcome to Fractal Generator!", 3000);

   if(fileName != "") {
      Document->openDocument(fileName);
   }

   show();
}


// ###### Destructor ########################################################
FractalGeneratorApp::~FractalGeneratorApp()
{
}


// ###### Open ##############################################################
void FractalGeneratorApp::slotFileOpen()
{
   statusBar()->showMessage(tr("Opening file..."));
   const QString fileName = QFileDialog::getOpenFileName(
                               this, tr("Open File ..."),
                               QDir::currentPath(),
                               tr("Fractal Settings File (*.fsf)"));
   if(!fileName.isEmpty()) {
      Document->openDocument(fileName);
   }
   statusBar()->showMessage(tr("Ready."));
}


// ###### Save ##############################################################
void FractalGeneratorApp::slotFileSaveAs()
{
   statusBar()->showMessage(tr("Saving file as ..."));
   const QString fileName = QFileDialog::getSaveFileName(
                               this, tr("Save File ..."),
                               QDir::currentPath(),
                               tr("Fractal Settings File (*.fsf)"));
   if(!fileName.isEmpty()) {
      Document->saveDocument(fileName);
   }
   statusBar()->showMessage(tr("Ready."));
}


// ###### Save as ###########################################################
void FractalGeneratorApp::slotFileSave()
{
   statusBar()->showMessage(tr("Saving file..."));
   bool overwrite = true;
   if(QFile::exists(Document->getFileName())) {
      if(QMessageBox::warning(this, tr("Fractal Generator II"),
                              tr("Overwrite existing file") + " " + Document->getFileName() + "?",
                              QMessageBox::Save|QMessageBox::Cancel, QMessageBox::Save) == QMessageBox::Cancel) {
         overwrite = false;
      }
   }
   if(overwrite) {
      Document->saveDocument(Document->getFileName());
   }
   statusBar()->showMessage(tr("Ready."));
}


// ###### Export ############################################################
void FractalGeneratorApp::slotFileExportImage()
{
   statusBar()->showMessage(tr("Exporting Image ..."));

   QString name = QFileDialog::getSaveFileName(this, tr("Export Image"),
                                               QDir::currentPath(),
                                               tr("*.png"));
   if(!name.isEmpty()) {
      if(name.right(4).toLower() != tr(".png"))
      name += tr(".png");
      View->getDisplay()->saveImage(name, "PNG");
   }

   statusBar()->showMessage(tr("Ready."));
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

   statusBar()->showMessage(tr("Ready."));
}


// ###### Quit ##############################################################
void FractalGeneratorApp::slotFileQuit()
{
   exit(0);
}


// ###### About #############################################################
void FractalGeneratorApp::slotHelpAbout()
{
   QMessageBox::information(this,
      tr("FractalGenerator II"),
      tr("FractalGenerator II\n") +
         "Copyright (C) 2003-2011 by Thomas Dreibholz",
      tr("Okay"));
}


// ###### Set picture size ##################################################
void FractalGeneratorApp::slotViewSetImageSize()
{
   statusBar()->showMessage(tr("Changing Image Size ..."));

   QString CurrentSize;
   CurrentSize += QString().setNum(View->getSizeX());
   CurrentSize += tr("*");
   CurrentSize += QString().setNum(View->getSizeY());

   bool ok;
   QString text = QInputDialog::getText(
                     this,
                     tr("Image Size"),
                     tr("Please enter new size in the format x*y:"),
                     QLineEdit::Normal, CurrentSize, &ok);
   if((ok) || (!text.isEmpty())) {
      const unsigned int newX = text.section("*", 0, 0).toUInt();
      const unsigned int newY = text.section("*", 1, 1).toUInt();

      if((0 < newX) && (0 < newY)) {
         View->changeSize(newX, newY);
         View->configChanged();
      }
      else {
         QMessageBox::information( this, tr("Image Size"),
         "Change to "
         + QString().setNum(newX)
         + "*"
         + QString().setNum(newY)
         + " failed!");
      }
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
   }

   statusBar()->showMessage(tr("Ready."));
}


// ###### Configure algorithm ###############################################
void FractalGeneratorApp::slotViewConfigureAlgorithm()
{
   statusBar()->showMessage(tr("Changing Options ..."));
   OptionsDialog dialog(this, View->getAlgorithm()->getConfigEntries());
   dialog.exec();
   View->configChanged();
   statusBar()->showMessage(tr("Ready."));
}


// ###### Update algorithm ##################################################
void FractalGeneratorApp::slotUpdateFractalAlgorithm()
{
   const FractalAlgorithmInterface* currentAlgorithm = View->getAlgorithm();
   unsigned int i = 0;
   QListIterator<QAction*> iterator(FractalAlgorithmActionList);
   while(iterator.hasNext()) {
      QAction* item = iterator.next();
      const FractalAlgorithmInterface* algorithm = FractalAlgorithmInterface::getAlgorithm(i);
      Q_CHECK_PTR(algorithm);
      item->setChecked( (algorithm == currentAlgorithm) );
      i++;
   }
}


// ###### Update color scheme ###############################################
void FractalGeneratorApp::slotUpdateColorScheme()
{
   const ColorSchemeInterface* currentColorScheme = View->getColorScheme();
   unsigned int i = 0;
   QListIterator<QAction*> iterator(ColorSchemeActionList);
   while(iterator.hasNext()) {
      QAction* item = iterator.next();
      const ColorSchemeInterface* colorScheme = ColorSchemeInterface::getColorScheme(i);
      Q_CHECK_PTR(colorScheme);
      item->setChecked( (colorScheme == currentColorScheme) );
      i++;
   }
}


// ###### Update file name ##################################################
void FractalGeneratorApp::slotUpdateFileName(const QString& fileName)
{
   setWindowTitle(fileName + " - " + tr("Fractal Generator II"));
}


// ###### Update Zoon In menu item ##########################################
void FractalGeneratorApp::slotUpdateZoomInPossible()
{
   const bool zoomInPossible = View->isZoomInPossible();
   ViewZoomIn->setEnabled(zoomInPossible);
   if(zoomInPossible) {
      statusBar()->showMessage(tr("Click middle mount button or choose \"View -> Zoom In\" to magnify selected area!"));
   }
   else {
      statusBar()->showMessage(tr("Ready."));
   }
}


// ###### Update Zoon Back menu item ########################################
void FractalGeneratorApp::slotUpdateZoomBackPossible()
{
   ViewZoomBack->setEnabled(View->isZoomBackPossible());
}


// ###### Set algorithm #####################################################
void FractalGeneratorApp::slotViewSetFractalAlgorithm(QAction* action)
{
   const int algorithmID = action->data().toInt();
   if(algorithmID < 1000000) {
      View->changeAlgorithm(algorithmID);
      View->configChanged();
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
   }
}


// ###### Set color scheme ##################################################
void FractalGeneratorApp::slotViewSetColorScheme(QAction* action)
{
   const int colorSchemeID = action->data().toInt();
   if(colorSchemeID < 1000000) {
      View->changeColorScheme(colorSchemeID);
      View->configChanged();
      ViewZoomBack->setEnabled(View->isZoomBackPossible());
   }
}
