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

#include "classregistry.h"


// ###### Constructor #######################################################
ClassRegistry::ClassRegistry()
{
}


// ###### Destructor ########################################################
ClassRegistry::~ClassRegistry()
{
   while(!Registry.isEmpty()) {
      delete Registry.take(Registry.firstKey());
   }
}


// ###### Register class ####################################################
bool ClassRegistry::registerClass(const QString& identifier,
                                  const QString& description,
                                  void*          (*makeInstanceFunction)())
{
   Registration* registration = new Registration;
   Q_CHECK_PTR(registration);

   registration->Identifier           = identifier;
   registration->Description          = description;
   registration->MakeInstanceFunction = makeInstanceFunction;
   Registry.insert(registration->Identifier, registration);

   return true;
}


// ###### Create new instance class #########################################
void* ClassRegistry::makeNewInstance(const QString& identifier)
{
   QMap<QString, Registration*>::iterator found = Registry.find(identifier);
   if(found == Registry.end()) {
      return nullptr;
   }
   return (*found)->MakeInstanceFunction();
}
