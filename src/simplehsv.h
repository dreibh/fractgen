/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2024 by Thomas Dreibholz
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

#ifndef SIMPLEHSV_H
#define SIMPLEHSV_H

#include <colorschemeinterface.h>

/**
  *@author Thomas Dreibholz
  */
class SimpleHSV : public ColorSchemeInterface  {
   public:
   SimpleHSV(const char* identifier = "SimpleHSV",
             const char* name       = "Simple HSV");
   ~SimpleHSV();

   virtual unsigned int getColor(const unsigned int value) override;

   private:
   static SimpleHSV* Registration;
};

#endif
