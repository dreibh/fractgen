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

#include "simplehsv.h"

#include <qcolor.h>


const QString SimpleHSV::Identifier(QStringLiteral("SimpleHSV"));
const QString SimpleHSV::Description(QStringLiteral("Simple HSV"));
const bool SimpleHSV::Registered =
   ColorSchemeInterface::registerClass(
      SimpleHSV::Identifier,
      SimpleHSV::Description,
      &SimpleHSV::makeNewInstance
   );


// ###### Constructor #######################################################
SimpleHSV::SimpleHSV()
{
}


// ###### Destructor ########################################################
SimpleHSV::~SimpleHSV()
{
}


// ###### Get identifier ####################################################
const QString& SimpleHSV::getIdentifier() const
{
   return SimpleHSV::Identifier;
}


// ###### Get description ###################################################
const QString& SimpleHSV::getDescription() const
{
   return SimpleHSV::Description;
}


// ###### Create new instance ###############################################
ColorSchemeInterface* SimpleHSV::makeNewInstance()
{
   return new SimpleHSV();
}


// ###### Get color for value ###############################################
unsigned int SimpleHSV::getColor(const unsigned int value)
{
   QColor color;
   color.setHsv((value % 72) * 5, 255, 255);
   return color.rgb();
}
