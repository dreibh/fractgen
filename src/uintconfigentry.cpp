/* $Id$
 * ==========================================================================
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

#include "uintconfigentry.h"


// ###### Constructor #######################################################
UIntConfigEntry::UIntConfigEntry(unsigned int* valuePtr, const char* name)
{
   EntryName = name;
   ValuePtr  = valuePtr;
}


// ###### Destructor ########################################################
UIntConfigEntry::~UIntConfigEntry()
{
}


// ###### Get name ##########################################################
QString UIntConfigEntry::getName() const
{
   return(EntryName);
}


// ###### Get value as string ###############################################
QString UIntConfigEntry::getValueAsString() const
{
   QString valueString;
   valueString.setNum(*ValuePtr);
   return(valueString);
}


// ###### Set value from string #############################################
void UIntConfigEntry::setValueFromString(const QString& valueString)
{
   *ValuePtr = valueString.toUInt();
}
