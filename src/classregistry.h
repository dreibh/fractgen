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

#ifndef CLASSREGISTRY_H
#define CLASSREGISTRY_H

#include <QMap>


class ClassRegistry {
   // ====== Constructor/Destructor =========================================
   public:
   ClassRegistry();
   ~ClassRegistry();

   // ====== Class registry =================================================
   bool registerClass(const QString& identifier,
                      const QString& description,
                      void*          (*makeInstanceFunction)());
   void* makeNewInstance(const QString& identifier);

   struct Registration {
       QString Identifier;
       QString Description;
       void*   (*MakeInstanceFunction)();
   };
   inline const QMap<QString, Registration*>& getClassMap() const {
      return Registry;
   }

   // ====== Private attributes =============================================
   private:
   QMap<QString, Registration*> Registry;
};

#endif
