/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2018 by Thomas Dreibholz
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

#ifndef FRACTALGENERATORDOC_H
#define FRACTALGENERATORDOC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QObject>
#include <QString>
#include <QList>


class FractalGeneratorView;
class FractalGeneratorApp;


class FractalGeneratorDoc : public QObject
{
   Q_OBJECT
   public:

   FractalGeneratorDoc(QWidget* parent, FractalGeneratorView* view);
   ~FractalGeneratorDoc();

   inline const QString& getFileName() const { return(FileName); }
   inline void setFileName(const QString& fileName) {
      FileName = fileName;
      emit updateFileName(FileName);
   }
   inline void setModified(bool modified) { Modified = modified; };
   inline bool isModified() { return Modified; };
   void newDocument();
   bool openDocument(const QString& fileName);
   bool saveDocument(const QString& fileName);
   bool saveModified();
   void closeDocument();

   signals:
   void updateFileName(const QString& fileName);

   private:
   bool                  Modified;
   QString               FileName;
   FractalGeneratorApp*  Application;
   FractalGeneratorView* View;
};

#endif // FRACTALGENERATORDOC_H
