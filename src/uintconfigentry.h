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

#ifndef UINTCONFIGENTRY_H
#define UINTCONFIGENTRY_H

#include <configentry.h>


/**
  * @author Thomas Dreibholz
  */
class UIntConfigEntry : public ConfigEntry  {
   public:
   UIntConfigEntry(unsigned int* valuePtr, const char* name);
   ~UIntConfigEntry();

   virtual QString getName() const;
   virtual QString getValueAsString() const;
   virtual void setValueFromString(const QString& valueString);

   private:
   QString       EntryName;
   unsigned int* ValuePtr;
};

#endif
