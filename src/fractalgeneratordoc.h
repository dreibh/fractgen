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

#ifndef FRACTALGENERATORDOC_H
#define FRACTALGENERATORDOC_H

#include <QObject>


class FractalGeneratorViewBase;
class FractalGeneratorApp;


class FractalGeneratorDoc : public QObject
{
   Q_OBJECT
   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorDoc(QWidget* parent, FractalGeneratorViewBase* view);
   ~FractalGeneratorDoc();

   // ====== File settings ==================================================
   inline void setModified(const bool modified) { Modified = modified; };
   inline bool isModified() const               { return Modified;     };
   inline const QString& getFileName() const    { return FileName;     }
   inline void setFileName(const QString& fileName) {
      FileName = fileName;
      emit updateFileName(FileName);
   }

   // ====== File input/output ==============================================
   void newDocument();
   bool openDocument(const QString& fileName);
   bool saveDocument(const QString& fileName);
   bool saveModified();
   void closeDocument();

   // ====== Signals ========================================================
   Q_SIGNALS:
   void updateFileName(const QString& fileName);

   // ====== Private attributes =============================================
   private:
   FractalGeneratorApp*      Application;
   FractalGeneratorViewBase* View;
   QString                   FileName;
   bool                      Modified;
};

#endif
