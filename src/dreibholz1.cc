/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2021 by Thomas Dreibholz
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

#include "dreibholz1.h"

// #include <iostream>


Dreibholz1* Dreibholz1::Registration = new Dreibholz1();

/*
 ---- Tests ----

 Start: z = c
 01.  z = z*z - pow(z, c) - c;
 02.  z = z*z - pow(c, (double)i);
 03.  z = pow(z, (double)i) - c;
 04.  z = pow(z, 2.0) - exp(c);
 05.  z = pow(z, 2.0) - log(d*c);
 06.  z = pow(z, 2.0) - log(c);
 07.  z = pow(z, 2.0) - sin(c);
 08.  z = sin(pow(z, 2.0)) - c;
 09.  z = cos(pow(z, 2.0)) - c;
 10.  z = z*z*z + z*z + (pow(z, log(z))) - c;
 11.  z = pow(z, 3) - pow(z, 5) + pow(z, 7) - pow(z, 11) + pow(z, 13) - c;
 12.  z = cos(pow(z, 3.0)) - c;
 13.    z = c;
        z2 = (z.real(), -z.imag());
        for(i = 0;i < MaxIterations;i++) {
           z = z2*z2 - c;
           z2 = z*z*z - c;

 14.  z = 0.5*z*z + 0.333*z*z*z + 0.25*z*z*z*z - c;

 15.  for(int j = 2;j <= 7;j++) {
         if((j % 2) == 0)
            z += pow(z, (double)j) / (double)j;
         else
            z -= pow(z, (double)j) / (double)j;
      }
      z -= c;

 16.  z2 = z;
      for(int j = 2;j <= 7;j++) {
         if((j % 2) == 0)
            z += pow(z2, (double)j) / (double)j;
         else
            z -= pow(z2, (double)j) / (double)j;
      }
      z -= c;

 17.  z2 = z;
      for(int j = 2;j <= 23;j++) {
         if((j % 2) == 0)
            z += pow(z2, (double)j) / (double)j;
         else
            z -= pow(z2, (double)j) / (double)j;
      }
      z -= c;

 18.  z2 = z;
      for(int j = 2;j <= 5;j++) {
         if((j % 2) == 0)
            z += sin(pow(z2, (double)j) / (double)j);
         else
            z -= cos(pow(z2, (double)j) / (double)j);
      }
      z -= c;

 19.  z = pow(z, 2.5) - std::complex<double>(0.75, -0.34);

 20.  z = pow(z, 2.5 + c) - c;

 21.  z = z + pow(z, 2.0) + pow(z, 3.0) - c - c*c - c*c*c;

 22.  z2 = z;
      c2 = c;
      z3 = 0.0;
      for(int j = 2;j <= 11;j++) {
         z3 += z2 - c2;
         z2 *= z;
         c2 *= c;
      }
      z = z3;

 23.  z2 = z;
      c2 = c;
      z3 = 0.0;
      for(int j = 1;j <= 4;j++) {
         z3 += (z2 - c2) / (double)j;
         z2 *= z;
         c2 *= c;
      }
      z = z3;

 24.  z2 = z;
      c2 = c;
      z3 = 0.0;
      for(int j = 2;j <= 11;j++) {
         z3 += (z2 - c2);
         z2 *= z;
         c2 *= c;
      }
      z = z3;

 25.  z2 = z;
      c2 = c;
      z3 = 0.0;
      for(int j = 2;j <= 5;j++) {
         z3 += (z2 - c2);
         z2 *= z;
         c2 *= c/(double)j;
      }
      z = z3;

26.   z2 = 1.0;
      c2 = 1.0;
      z3 = 0.0;
      for(int j = 1;j <= 4;j++) {
         z2 *= z;
         c2 *= c / (double)j;
         z3 += (z2 - c2);
      }
      z = z3;

27.   z2 = 1.0;
      c2 = 1.0;
      z3 = 0.0;
      for(int j = 1;j <= 4;j++) {
         z2 *= z;
         c2 *= c / (double)j;
         z3 += (z2 - c2);
      }
      z = sin(z3);

28.  ...
     z = tan(z3);

29.  ...
     z = cos(exp(z3));

30.  ...
     z = sin(exp(z3));
*/


// ###### Constructor #######################################################
Dreibholz1::Dreibholz1(const char* identifier, const char* name)
   : FractalAlgorithmInterface(identifier, name)
{
   // ConfigEntries.append(new DoubleConfigEntry(&N, "N"));
}


// ###### Destructor ########################################################
Dreibholz1::~Dreibholz1()
{
}


// ###### Get default for C1 ################################################
std::complex<double> Dreibholz1::defaultC1() const
{
   return(std::complex<double>(-3.5, 3.5));
}


// ###### Get default for C2 ################################################
std::complex<double> Dreibholz1::defaultC2() const
{
   return(std::complex<double>(3.5, -3.5));
}


// ###### Calculate graphics point (x,y) ####################################
unsigned int Dreibholz1::calculatePoint(const unsigned int x,
                                        const unsigned int y)
{
   const std::complex<double> c = std::complex<double>(C1.real() + ((double)x * StepX),
                                                       C1.imag() + ((double)y * StepY));
   std::complex<double> z(0.0, 0.0);
   std::complex<double> z2(0.0, 0.0);
   std::complex<double> z3(0.0, 0.0);
   // std::complex<double> c2;
   unsigned int         i;

   // const double d = abs(c);

   z = c;
   z2 = (z.real(), -z.imag());
   for(i = 0;i < MaxIterations;i++) {
     /*
      z2 = 1.0;
      c2 = 1.0;
      z3 = 0.0;
      for(int j = 1;j <= 4;j++) {
         z2 *= z;
         c2 *= c / (double)j;
         z3 += (z2 - c2);
      }
     */
     z3 = z*z-c;
      z = cos(exp(z3));

      if(z.real() * z.real() + z.imag() * z.imag() >= 2.0) {
         return(i);
      }
   }

   return(i);
}
