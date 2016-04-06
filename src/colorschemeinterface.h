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

#ifndef COLORSCHEMEINTERFACE_H
#define COLORSCHEMEINTERFACE_H

#include <qlist.h>


/**
  *@author Thomas Dreibholz
  */
class ColorSchemeInterface {
   public:
   ColorSchemeInterface(const char* identifier, const char* name);
   virtual ~ColorSchemeInterface();
   inline const char* getIdentifier() { return(Identifier); }
   inline const char* getName() const { return(Name); }

   virtual void configure(unsigned int* maxIterations);
   virtual unsigned int getColor(const unsigned int value) = 0;

   static ColorSchemeInterface* getColorScheme(const unsigned int index);
   static ColorSchemeInterface* getColorSchemeByIdentifier(const char* identifier);

   protected:
   const char*   Name;
   const char*   Identifier;
   unsigned int* MaxIterations;

   private:
   static QList<ColorSchemeInterface*>* ColorSchemeList;
   static bool                          Updated;
};

#endif
