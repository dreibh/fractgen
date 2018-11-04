/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2019 by Thomas Dreibholz
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

#include "fractalbuffer.h"

#include <stdlib.h>


// ###### Constructor #######################################################
FractalBuffer::FractalBuffer()
{
   Buffer     = NULL;
   BufferSize = 0;
   Width      = 0;
   Height     = 0;
}


// ###### Desstructor ########################################################
FractalBuffer::~FractalBuffer()
{
   reset(0,0);
}


// ###### Reset FractalBuffer ###############################################
bool FractalBuffer::reset(const unsigned int width, const unsigned int height)
{
   if(Buffer) {
      delete Buffer;
   }
   Width      = width;
   Height     = height;
   BufferSize = width * height;
   if(BufferSize > 0) {
      Buffer = new unsigned int[BufferSize];
      if(Buffer == NULL) {
         reset(0,0);
         return(false);
      }
      clear();
   }
   else {
      Buffer = NULL;
   }
   return(true);
}


// ###### Clear FractalBuffer ###############################################
void FractalBuffer::clear()
{
   for(unsigned int i = 0;i < BufferSize;i++) {
      Buffer[i] = (unsigned int)~0;
   }
}
