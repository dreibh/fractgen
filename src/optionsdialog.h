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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTableWidget>

#include "configentry.h"


class OptionsDialog : public QDialog  {
   Q_OBJECT

   public:
   OptionsDialog(QWidget* parent = NULL, QList<ConfigEntry*>* configEntries = NULL);
   ~OptionsDialog();

   private:
   QTableWidget*        TableWidget;
   QList<ConfigEntry*>* ConfigEntries;

   public slots:
   void slotItemChanged(QTableWidgetItem* item);
};

#endif
