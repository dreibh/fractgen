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

#ifndef FRACTALBUFFER_H
#define FRACTALBUFFER_H

class FractalBuffer
{
   // ====== Constructor/Destructor =========================================
   public:
   FractalBuffer();
   ~FractalBuffer();

   // ====== Access =========================================================
   bool reset(const unsigned int width, const unsigned int height);
   void clear();
   inline unsigned int getPoint(const unsigned int x, const unsigned int y) const {
      const unsigned long position = y * Width + x;
      if(position < BufferSize) {
         return Buffer[position];
      }
      // printf("ERROR: FractalBuffer::getPoint() - Illegal position: x=%d y=%d in w=%d h=%d\n", x, y, Width, Height);
      // abort();
      return ~0;
   }
   inline void setPoint(const unsigned int x, const unsigned int y, const unsigned int value) {
      const unsigned long position = y * Width + x;
      if(position < BufferSize) {
         Buffer[position] = value;
      }
      // else {
      //    printf("ERROR: FractalBuffer::setPoint() - Illegal position: x=%d y=%d in w=%d h=%d\n", x, y, Width, Height);
      //    abort();
      // }
   }

   // ====== Private attributes =============================================
   private:
   unsigned int* Buffer;
   unsigned int  BufferSize;
   unsigned int  Width;
   unsigned int  Height;
};

#endif
