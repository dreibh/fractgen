/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2009 by Thomas Dreibholz
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

#include "doubleconfigentry.h"


// ###### Constructor #######################################################
DoubleConfigEntry::DoubleConfigEntry(double* valuePtr, const char* name)
{
   EntryName = name;
   ValuePtr  = valuePtr;
}


// ###### Destructor ########################################################
DoubleConfigEntry::~DoubleConfigEntry()
{
}


// ###### Get name ##########################################################
QString DoubleConfigEntry::getName() const
{
   return(EntryName);
}


// ###### Get value as string ###############################################
QString DoubleConfigEntry::getValueAsString() const
{
   QString valueString;
   valueString.setNum(*ValuePtr);
   return(valueString);
}


// ###### Set value from string #############################################
void DoubleConfigEntry::setValueFromString(const QString& valueString)
{
   *ValuePtr = valueString.toDouble();
}
