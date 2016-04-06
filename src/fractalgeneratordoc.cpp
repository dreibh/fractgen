/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2016 by Thomas Dreibholz
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

#include "fractalgeneratordoc.h"
#include "fractalgenerator.h"
#include "fractalgenerator.h"
#include "fractalgeneratorview.h"

#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <QDataStream>


// ###### Constructor #######################################################
FractalGeneratorDoc::FractalGeneratorDoc(QWidget* parent, FractalGeneratorView* view)
   : QObject(parent)
{
   View        = view;
   Application = static_cast<FractalGeneratorApp*>(parent);
}


// ###### Destructor ########################################################
FractalGeneratorDoc::~FractalGeneratorDoc()
{
   closeDocument();
}


// ###### Close document ####################################################
void FractalGeneratorDoc::closeDocument()
{
}


// ###### New document ######################################################
void FractalGeneratorDoc::newDocument()
{
   Modified = false;
   setFileName(tr("Unnamed.fsf"));
}


// ###### Open document #####################################################
bool FractalGeneratorDoc::openDocument(const QString& fileName)
{
   // ====== Open file ======================================================
   QFile file(fileName);
   if(!file.open(QIODevice::ReadOnly)) {
      return(false);
   }

   // ====== Parse XML document =============================================
   QDomDocument doc("XMLFractalSave");
   QString      errorText;
   int          line, column;
   if(!doc.setContent(&file, false, &errorText, &line, &column)) {
      QMessageBox::warning(Application, tr("Open File Failure"),
                           errorText + " in line " + QString().setNum(line) + ", column " + QString().setNum(column));
      return(false);
   }

   // ====== Get fractal configuration ======================================
   // ------ Get algorithm --------------------------------------------------
   const QDomElement algorithmNameField = doc.elementsByTagName("AlgorithmName").item(0).toElement();
   const QString     algorithmName      = algorithmNameField.firstChild().toText().data();
   unsigned int      algorithmID        = 0;
   FractalAlgorithmInterface* fractalAlgorithm;
   while( (fractalAlgorithm = FractalAlgorithmInterface::getAlgorithm(algorithmID)) != NULL ) {
      if(QString(fractalAlgorithm->getIdentifier()) == algorithmName) {
         break;
      }
      algorithmID++;
   }
   if(fractalAlgorithm == NULL) {
      QMessageBox::warning(Application, tr("Open File Failure"),
                           tr("Invalid AlgorithmName entry:") + algorithmName);
      return(false);
   }

   // ------ Get color scheme -----------------------------------------------
   const QDomElement colorSchemeField = doc.elementsByTagName("ColorSchemeName").item(0).toElement();
   const QString     colorSchemeName  = colorSchemeField.firstChild().toText().data();
   unsigned int      colorSchemeID    = 0;
   ColorSchemeInterface* colorScheme;
   while((colorScheme = ColorSchemeInterface::getColorScheme(colorSchemeID))) {
      if(QString(colorScheme->getIdentifier()) == colorSchemeName) {
        break;
     }
     colorSchemeID++;
   }
   if(colorScheme == NULL) {
      QMessageBox::warning(Application, tr("Open File Failure"),
                           tr("Invalid ColorSchemeName entry:") + colorSchemeName);
      return(false);
   }

   // ------ Get resolution -------------------------------------------------
   /*
   QString resolution = doc.elementsByTagName("Resolution").item(0).firstChild().toText().data();

   unsigned int newX = resolution.section("*",0,0).toUInt();
   unsigned int newY = resolution.section("*",1,1).toUInt();
   View->changeSize(newX, newY);
   */

   // ------ Get C1 and C2 --------------------------------------------------
   const double c1real = doc.elementsByTagName("C1Real").item(0).firstChild().toText().data().toDouble();
   const double c1imag = doc.elementsByTagName("C1Imag").item(0).firstChild().toText().data().toDouble();
   const double c2real = doc.elementsByTagName("C2Real").item(0).firstChild().toText().data().toDouble();
   const double c2imag = doc.elementsByTagName("C2Imag").item(0).firstChild().toText().data().toDouble();
   const std::complex<double> C1(c1real, c1imag);
   const std::complex<double> C2(c2real, c2imag);
   View->changeC1C2(C1, C2);

   // ------ Activate settings ----------------------------------------------
   View->changeAlgorithm(algorithmID);
   View->changeColorScheme(colorSchemeID);
   View->getAlgorithm()->configure(View->getSizeX(), View->getSizeY(),
                                   C1, C2,*(View->getAlgorithm()->getMaxIterations()));

   // ------ Set user options -----------------------------------------------
   QDomElement userOptionsBranch = doc.elementsByTagName("Useroptions").item(0).toElement();
   QDomNode    userOptionsChild  = userOptionsBranch.firstChild();
   while(!userOptionsChild.isNull()) {
      QListIterator<ConfigEntry*> iterator(*(View->getAlgorithm()->getConfigEntries()));
      const QString               name  = userOptionsChild.nodeName();
      const QString               value = userOptionsChild.firstChild().toText().data();
      bool                        found = false;
      while(iterator.hasNext()) {
         ConfigEntry* configEntry = iterator.next();
         if(configEntry->getName() == name) {
            configEntry->setValueFromString(value);
            found = true;
            break;
         }
      }
      if(!found) {
         QMessageBox::warning(Application, tr("Open File Warning"),
                              tr("Skipping unknown entry:") + name);
      }
      userOptionsChild = userOptionsChild.nextSibling();
   }

   // ------ Show new configuration -----------------------------------------
   setFileName(fileName);
   View->configChanged();

   Modified = false;
   return(true);
}


// ###### Save document #####################################################
bool FractalGeneratorDoc::saveDocument(const QString& fileName)
{
   QDomDocument doc("XMLFractalSave");
   QDomElement root = doc.createElement("FractalV1");
   doc.appendChild(root);

   // Create Algorithm branch
   QDomElement algorithm = doc.createElement("Algorithm");
   root.appendChild(algorithm);

   // Algorithm Name
   QDomElement tag = doc.createElement("AlgorithmName");
   algorithm.appendChild(tag);

   QDomText text = doc.createTextNode(View->getAlgorithm()->getIdentifier());
   tag.appendChild(text);

   // Algorithm C1Real
   QDomElement C = doc.createElement("C1Real");
   algorithm.appendChild(C);
   text = doc.createTextNode(QString().setNum(View->getAlgorithm()->getC1().real(), 'e', 64));
   C.appendChild(text);

   // Algorithm C1Imag
   C = doc.createElement("C1Imag");
   algorithm.appendChild(C);
   text = doc.createTextNode(QString().setNum(View->getAlgorithm()->getC1().imag(), 'e', 64));
   C.appendChild(text);

   // Algorithm C2Real
   C = doc.createElement("C2Real");
   algorithm.appendChild(C);
   text = doc.createTextNode(QString().setNum(View->getAlgorithm()->getC2().real(), 'e', 64));
   C.appendChild(text);

   // Algorithm C2Imag
   C = doc.createElement("C2Imag");
   algorithm.appendChild(C);
   text = doc.createTextNode(QString().setNum(View->getAlgorithm()->getC2().imag(), 'e', 64));
   C.appendChild(text);

   // Create UserOptions branch
   QDomElement optionRoot = doc.createElement("Useroptions");
   algorithm.appendChild(optionRoot);

   QDomElement option;
   QListIterator<ConfigEntry*> iterator(*View->getAlgorithm()->getConfigEntries());
   while(iterator.hasNext()) {
      ConfigEntry* configEntry = iterator.next();
      option = doc.createElement(configEntry->getName());
      optionRoot.appendChild(option);
      text = doc.createTextNode(configEntry->getValueAsString());
      option.appendChild(text);
   }

   // Create ColorScheme branch
   QDomElement colorScheme = doc.createElement("ColorScheme");
   root.appendChild(colorScheme);
   tag = doc.createElement("ColorSchemeName");
   colorScheme.appendChild(tag);

   text = doc.createTextNode(View->getColorScheme()->getIdentifier());
   tag.appendChild(text);

   // Resolution
   QDomElement resolution = doc.createElement("Resolution");
   root.appendChild( resolution );

   QString CurrentSize;
   CurrentSize += QString().setNum(View->getSizeX());
   CurrentSize += tr("*");
   CurrentSize += QString().setNum(View->getSizeY());

   text = doc.createTextNode( CurrentSize );
   resolution.appendChild(text);

   // Write XML document to file
   QString newFileName = fileName;
   if(newFileName.right(4) != ".fsf") {
      newFileName += ".fsf";
   }
   QFile file(newFileName);
   file.open(QIODevice::WriteOnly);
   file.write(doc.toString().toLocal8Bit());
   setFileName(newFileName);
   Modified = false;
   return(true);
}
