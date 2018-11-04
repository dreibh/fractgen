/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2019 by Thomas Dreibholz
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

#include "optionsdialog.h"

#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>


// ###### Constructor #######################################################
OptionsDialog::OptionsDialog(QWidget* parent, QList<ConfigEntry*>* configEntries)
   : QDialog(parent)
{
   setWindowTitle(tr("Fractal Algorithm Options"));
   ConfigEntries = configEntries;

   QVBoxLayout* layout = new QVBoxLayout(this);
   Q_CHECK_PTR(layout);

   TableWidget = new QTableWidget(configEntries->size(), 2, this);
   Q_CHECK_PTR(TableWidget);
   QTableWidgetItem* parameterName = new QTableWidgetItem(tr("Parameter Name"));
   Q_CHECK_PTR(parameterName);
   parameterName->setTextAlignment(Qt::AlignLeft);
   TableWidget->setHorizontalHeaderItem(0, parameterName);
   QTableWidgetItem* parameterValue = new QTableWidgetItem(tr("Parameter Value"));
   Q_CHECK_PTR(parameterValue);
   parameterValue->setTextAlignment(Qt::AlignLeft);
   TableWidget->setHorizontalHeaderItem(1, parameterValue);

   QListIterator<ConfigEntry*> iterator(*configEntries);
   int row = 0;
   while(iterator.hasNext()) {
      ConfigEntry* configEntry = iterator.next();

      QTableWidgetItem* parameterName = new QTableWidgetItem(configEntry->getName());
      Q_CHECK_PTR(parameterName);
      parameterName->setFlags(Qt::ItemIsEnabled);
      QTableWidgetItem* parameterValue = new QTableWidgetItem(configEntry->getValueAsString());
      Q_CHECK_PTR(parameterValue);

      TableWidget->setItem(row, 0, parameterName);
      TableWidget->setItem(row, 1, parameterValue);
      row++;
   }
   connect(TableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), SLOT(slotItemChanged(QTableWidgetItem*)));

   TableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   TableWidget->setMinimumSize(560,420);
   layout->addWidget(TableWidget);

   QPushButton* button = new QPushButton("&Okay");
   connect(button, SIGNAL(clicked()), SLOT(accept()));
   layout->addWidget(button);
}


// ###### Destructor ########################################################
OptionsDialog::~OptionsDialog()
{
}


// ###### Update value ######################################################
void OptionsDialog::slotItemChanged(QTableWidgetItem* item)
{
   const int row    = item->row();
   const int column = item->column();
   const QTableWidgetItem* parameterName = item->tableWidget()->item(row, column - 1);
   Q_CHECK_PTR(parameterName);

   const QString parameterNameString  = parameterName->text();
   const QString parameterValueString = item->text();

   QListIterator<ConfigEntry*> iterator(*ConfigEntries);
   while(iterator.hasNext()) {
      ConfigEntry* configEntry = iterator.next();
      if(configEntry->getName() == parameterNameString) {
          configEntry->setValueFromString(parameterValueString);
          break;
      }
   }
}
