/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2026 by Thomas Dreibholz
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

#ifndef COLORSCHEMEINTERFACE_H
#define COLORSCHEMEINTERFACE_H

#include "classregistry.h"


class ColorSchemeInterface {
   // ====== Constructor/Destructor =========================================
   public:
   ColorSchemeInterface();
   virtual ~ColorSchemeInterface();

   // ====== Color scheme information =======================================
   virtual const QString& getIdentifier()  const = 0;
   virtual const QString& getDescription() const = 0;

   // ====== Color scheme parameters ========================================
   virtual void configure(const unsigned int* maxIterations);

   // ====== The actual coloring rule =======================================
   virtual unsigned int getColor(const unsigned int value) = 0;

   // ====== Color scheme registry ==========================================
   inline static const QMap<QString, ClassRegistry::Registration*>& getColorSchemes() {
      return Registry->getClassMap();
   }
   inline static ColorSchemeInterface* makeColorSchemeInstance(const QString& identifier) {
      return (ColorSchemeInterface*)Registry->makeNewInstance(identifier);
   }

   // ====== Protected attributes ===========================================
   protected:
   // ------ Color scheme registry ------------------------------------------
   static bool registerClass(const QString& identifier,
                             const QString& description,
                             ColorSchemeInterface* (*makeInstanceFunction)());

   // ------ Color scheme parameters ----------------------------------------
   const unsigned int* MaxIterations;

   // ====== Private attributes =============================================
   private:
   static ClassRegistry* Registry;
};

#endif
