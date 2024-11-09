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

#ifndef DOUBLECONFIGENTRY_H
#define DOUBLECONFIGENTRY_H

#include <configentry.h>


/**
  * @author Thomas Dreibholz
  */
class DoubleConfigEntry : public ConfigEntry  {
   public:
   DoubleConfigEntry(double* valuePtr, const char* name);
   ~DoubleConfigEntry();

   virtual QString getName() const override;
   virtual QString getValueAsString() const override;
   virtual void setValueFromString(const QString& valueString) override;

   private:
   QString EntryName;
   double* ValuePtr;
};

#endif
