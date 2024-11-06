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

#include "colorschemeinterface.h"

#include <string.h>

#include <algorithm>

QList<ColorSchemeInterface*>* ColorSchemeInterface::ColorSchemeList = nullptr;
bool                          ColorSchemeInterface::Updated         = false;


// ###### Constructor #######################################################
ColorSchemeInterface::ColorSchemeInterface(const char* identifier, const char* name)
{
   Updated    = true;
   Identifier = identifier;
   Name       = name;

   if(ColorSchemeInterface::ColorSchemeList == nullptr) {
      ColorSchemeInterface::ColorSchemeList = new QList<ColorSchemeInterface*>;
   }
   ColorSchemeList->append(this);
}


// ###### Constructor #######################################################
ColorSchemeInterface::~ColorSchemeInterface()
{
   ColorSchemeList->removeAll(this);
}


// ###### Destructor ########################################################
void ColorSchemeInterface::configure(unsigned int* maxIterations)
{
   MaxIterations = maxIterations;
}


// ###### Comparison function for names #####################################
static bool lessThan(const ColorSchemeInterface* c1,
                     const ColorSchemeInterface* c2)
{
   return strcmp(c1->getName(), c2->getName()) < 0;
}


// ###### Get color scheme by number ########################################
const ColorSchemeInterface* ColorSchemeInterface::getColorSchemeByIndex(const unsigned int colorSchemeIndex)
{
   if(Updated) {
      std::sort(ColorSchemeList->begin(), ColorSchemeList->end(), lessThan);
      Updated = false;
   }
   return ColorSchemeList->value(colorSchemeIndex, nullptr);
}


// ###### Make color scheme instance by index ###############################
ColorSchemeInterface* ColorSchemeInterface::makeColorSchemeInstanceByIndex(const unsigned int colorSchemeIndex)
{
   if(Updated) {
      std::sort(ColorSchemeList->begin(), ColorSchemeList->end(), lessThan);
      Updated = false;
   }
   return ColorSchemeList->value(colorSchemeIndex, nullptr)->makeInstance();
}


// ###### Make color scheme instance by identifier ##########################
ColorSchemeInterface* ColorSchemeInterface::makeColorSchemeInstanceByIdentifier(const char* colorSchemeIdentifier)
{
   QListIterator<ColorSchemeInterface*> iterator(*ColorSchemeList);
   while(iterator.hasNext()) {
      ColorSchemeInterface* colorScheme = iterator.next();
      if(strcmp(colorSchemeIdentifier, colorScheme->getIdentifier()) == 0) {
         return colorScheme->makeInstance();
      }
   }
   return nullptr;
}
