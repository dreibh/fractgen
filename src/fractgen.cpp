/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2009 by Thomas Dreibholz
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

#include "fractalgenerator.h"

#include <QApplication>
#include <QFile>


static QString parseToken(QString& string)
{
    QString token;
    bool    inString  = false;
    bool    isSpecial = false;         

    string = string.trimmed();
    while(string.size() > 0) {
        const QChar c = string[0];
        string.remove(0, 1);
        if(c == '\\') {
            if(isSpecial) {
                token.append(c);
                isSpecial = false;
            }
            else {
                isSpecial = true;
            }
        }
        else {
            if((c == '\"') && (!isSpecial)) {
                inString = !inString;
                if(!inString) {
                   break;
                }
            }
            else if((c == ':') && (!inString)) {
                token += c;
                break;
            }
            else if((c == ' ') && (!inString)) {
                break;
            }
            else {
                token += c;
            }
            isSpecial = false;
        }
    }
    return(token.trimmed());
}

void parse(QString s)
{
   printf("s=<%s>\n", s.toLocal8Bit().constData());
   while(s != "") {
      QString c = parseToken(s);
      printf("   c=<%s>\n", c.toLocal8Bit().constData());
//       printf("   c=<%s>   <rest=%s>\n", c.toLocal8Bit().constData(), s.toLocal8Bit().constData());
   }
}


// ###### Main program ######################################################
int main(int argc, char *argv[])
{
   QApplication application(argc, argv);


parse(QString("# Kommentar title: \"pc 88\" token: \"ssh pc88 -c ls dh0:\""));
parse(QString("title: \"pc 88\" token: \"ssh pc88 -c ls dh0:\""));
parse(QString("title: PC-71 token: \"ssh pc88 -c ls dh0:\""));
parse(QString("title: PC-71 token: \"ssh pc88 -c ls dh0:"));
parse(QString("title: PC-71 token: \"ssh pc88 -c ls dh0:\" profile: xy"));
   
return 0;   
   
   
   FractalGeneratorApp* fractalGeneratorApp = NULL;
   for(int i = 1;i < argc;i++) {
      const QString fileName = argv[i];
      if( (fractalGeneratorApp == NULL) &&
          (fileName.right(4) == ".fsf") &&
          (QFile::exists(fileName)) ) {
         fractalGeneratorApp = new FractalGeneratorApp(NULL, fileName);
         fractalGeneratorApp->show();
      }
   }

   if(fractalGeneratorApp == NULL) {
      fractalGeneratorApp = new FractalGeneratorApp(NULL);
      fractalGeneratorApp->show();
   }

   return application.exec();
}
