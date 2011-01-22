/* $Id$
 * ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2011 by Thomas Dreibholz
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

#ifndef IMAGEDISPLAY_H
#define IMAGEDISPLAY_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QDateTime>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>


class ImageDisplay : public QWidget {
   Q_OBJECT
   public:
   ImageDisplay(QWidget* parent);
   ~ImageDisplay();

   bool reset(const unsigned int width, const unsigned int height);
   inline void setPoint(const unsigned int x, const unsigned int y, const QRgb color) {
      Image->setPixel(x, y, color);
   }
   inline QImage* image() {
      return(Image);
   }
   inline int imageWidth() {
      return(Image->width());
   }
   inline int imageHeight() {
      return(Image->height());
   }
   inline unsigned int offsetX() {
      return(OffsetX);
   }
   inline unsigned int offsetY() {
      return(OffsetY);
   }
   inline void setOffsetX(const unsigned int offsetX) {
      OffsetX = offsetX;
   }
   inline void setOffsetY(const unsigned int offsetY) {
      OffsetY = offsetY;
   }
   inline bool saveImage(QString &path, const char *format) {
       return Image->save(path, format); }

   signals:
   void offsetUpdate(int newOffsetX, int newOffsetY);
   void selection(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
   void zoom();

   protected:
   void resizeEvent(QResizeEvent* resizeEvent);
   void paintEvent(QPaintEvent* paintEvent);
   void mousePressEvent(QMouseEvent* mouseEvent);
   void mouseReleaseEvent(QMouseEvent* mouseEvent);
   void mouseMoveEvent(QMouseEvent* mouseEvent);

   private:
   void getMarkPosition(QMouseEvent* mouseEvent, int& x, int& y);
   void drawMarkerRect(QPainter* painter, int x1, int y1, int x2, int y2, bool draw = true);

   QImage*      Image;
   unsigned int OffsetX;
   unsigned int OffsetY;
   QTime        LastOffsetUpdate;
   int          MarkX1;
   int          MarkY1;
   int          MarkX2;
   int          MarkY2;
   bool         Marking;
};

#endif
