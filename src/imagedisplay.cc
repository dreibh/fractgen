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

#include "imagedisplay.h"

#include <QApplication>
#include <QClipboard>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>


// ###### Constructor #######################################################
ImageDisplay::ImageDisplay(QWidget* parent)
   : QWidget(parent)
{
   Image = new QImage();
   Q_CHECK_PTR(Image);
   OffsetX = 0;
   OffsetY = 0;
   MarkX1  = 0;
   MarkY1  = 0;
   MarkX2  = 0;
   MarkY2  = 0;
   Marking = false;
}


// ###### Destructor #######################################################
ImageDisplay::~ImageDisplay()
{
   delete Image;
}


// ###### Reset image #######################################################
bool ImageDisplay::reset(const unsigned int width, const unsigned int height)
{
   if(Image) {
     delete Image;
   }
   Image = new QImage(width, height, QImage::Format_RGB32);
   Q_CHECK_PTR(Image);
   for(int y = 0;y < Image->height();y++) {
      for(int x = 0;x < Image->width();x++) {
         Image->setPixel(x, y, qRgb(255, 255, 255));
      }
   }

   OffsetX = 0;
   OffsetY = 0;
   MarkX1  = 0;
   MarkY1  = 0;
   MarkX2  = 0;
   MarkY2  = 0;
   Marking = false;
   return true;
}


// ###### Copy to clipboard #################################################
void ImageDisplay::copyToClipboard()
{
   QApplication::clipboard()->setImage(*Image);
}


// ###### Copy selection to clipboard #######################################
void ImageDisplay::copySelectionToClipboard()
{
   if(Marking) {
      QImage selection(Image->copy(MarkX1, MarkY1,
                                   MarkX2 - MarkX1, MarkY2 - MarkY1));
      QApplication::clipboard()->setImage(selection);
   }
}


// ###### Draw marking rectangle ############################################
void ImageDisplay::drawMarkerRect(QPainter* painter,
                                  const int x1, const int y1,
                                  const int x2, const int y2,
                                  const bool draw)
{
   const int x  = std::min(x1, x2) - OffsetX;
   const int y  = std::min(y1, y2) - OffsetY;
   const int w  = (std::max(x1, x2) - OffsetX) - x;
   const int h  = (std::max(y1, y2) - OffsetY) - y;
   const int bw = std::min(w / 2, 5);
   const int bh = std::min(h / 2, 5);

   if(draw) {
      painter->fillRect(x - bw, y - bh,    w + 2 * bw, bh,     Qt::blue);
      painter->fillRect(x - bw, y + h + 1, w + 2 * bw, bh,     Qt::blue);
      painter->fillRect(x - bw, y,         bw,         h + 1,  Qt::blue);
      painter->fillRect(x + w,  y,         bw,         h + 1,  Qt::blue);
   }
   else {
      painter->drawImage(x - bw, y - bh,    *Image, x - bw + (int)OffsetX, y - bh +    (int)OffsetY, w + 2 * bw,  bh);
      painter->drawImage(x - bw, y + h + 1, *Image, x - bw + (int)OffsetX, y + h + 1 + (int)OffsetY, w + 2 * bw,  bh);
      painter->drawImage(x - bw, y,         *Image, x - bw + (int)OffsetX, y +         (int)OffsetY, bw, h + 1);
      painter->drawImage(x + w,  y,         *Image, x + w  + (int)OffsetX, y +         (int)OffsetY, bw, h + 1);
   }
}


// ###### Resize ############################################################
void ImageDisplay::resizeEvent(QResizeEvent*)
{
   update();
}


// ###### Repaint ###########################################################
void ImageDisplay::paintEvent(QPaintEvent* paintEvent)
{
   QPainter p;
   p.begin(this);
   p.drawImage(paintEvent->rect().left(), paintEvent->rect().top(),
               *Image,
               paintEvent->rect().left() + OffsetX,
               paintEvent->rect().top()  + OffsetY,
               paintEvent->rect().width(),
               paintEvent->rect().height());
   if(Marking) {
      drawMarkerRect(&p, MarkX1, MarkY1, MarkX2, MarkY2);
   }
   p.end();
}


// ###### Handle mouse press for marking ####################################
void ImageDisplay::mousePressEvent(QMouseEvent* mouseEvent)
{
   if(mouseEvent->button() & Qt::LeftButton) {
      selection(0, 0, 0, 0);   // Unmark
      getMarkPosition(mouseEvent, MarkX1, MarkY1);
      MarkX2  = MarkX1;
      MarkY2  = MarkY1;
      Marking = true;
      LastOffsetUpdate.restart();
      update();
   }
}


// ###### Handle mouse release for marking ##################################
void ImageDisplay::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
   LastOffsetUpdate.restart();
   mouseMoveEvent(mouseEvent);

   if((mouseEvent->button() & Qt::LeftButton) && (Marking)) {
      getMarkPosition(mouseEvent, MarkX2, MarkY2);
      if((MarkX1 != MarkX2) && (MarkY1 != MarkY2)) {
         selection(MarkX1, MarkY1, MarkX2, MarkY2);
      }
      update();
   }
   else if((mouseEvent->button() & Qt::RightButton) && (Marking)) {
      Marking = false;
      selection(0, 0, 0, 0);   // Unmark
      update();
   }
   if(mouseEvent->button() & Qt::MiddleButton) {
      emit zoomInToSelection();
   }
}


// ###### Handle mouse movement for marking #################################
void ImageDisplay::mouseMoveEvent(QMouseEvent* mouseEvent)
{
   if((Marking) && (LastOffsetUpdate.elapsed() >= 50)) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
      const int mouseX = (int)mouseEvent->position().x();
      const int mouseY = (int)mouseEvent->position().y();
#else
      const int mouseX = mouseEvent->x();
      const int mouseY = mouseEvent->y();
#endif
      int movex = 0;
      int movey = 0;
      if(mouseX < 0) {
         movex = std::max(mouseX, -((int)OffsetX));
      }
      else if(mouseX >= width()) {
         movex = std::min(mouseX - width(), Image->width() - width() - (int)OffsetX);
      }
      if(mouseY < 0) {
         movey = std::max(mouseY, -((int)OffsetY));
      }
      else if(mouseY >= height()) {
         movey = std::min(mouseY - height(), Image->height() - height() - (int)OffsetY);
      }

      if((movex != 0) || (movey != 0)) {
         offsetUpdate((int)OffsetX + movex, (int)OffsetY + movey);
         LastOffsetUpdate.restart();
      }

      getMarkPosition(mouseEvent, MarkX2, MarkY2);
      update();
   }
}


// ###### Handle mouse wheel event for zooming #################################
void ImageDisplay::wheelEvent(QWheelEvent* wheelEvent)
{
   const QPoint& wheelDelta = wheelEvent->pixelDelta();
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
   const int mouseX = (int)wheelEvent->position().x();
   const int mouseY = (int)wheelEvent->position().y();
#else
   const int mouseX = wheelEvent->x();
   const int mouseY = wheelEvent->y();
#endif
   // Mouse cursor's position relative to center of image display:
   const int deltaX = (width()  / 2) - mouseX;
   const int deltaY = (height() / 2) - mouseY;

   emit zoomAdjustment(deltaX, deltaY, wheelDelta.y());
   wheelEvent->accept();
}


// ###### Get (x,y)-position for marking rect ###############################
void ImageDisplay::getMarkPosition(QMouseEvent* mouseEvent, int& x, int& y)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
   const int mouseX = (int)mouseEvent->position().x();
   const int mouseY = (int)mouseEvent->position().y();
#else
   const int mouseX = mouseEvent->x();
   const int mouseY = mouseEvent->y();
#endif
   x = mouseX + (int)OffsetX;
   if(x < 0) {
      x = 0;
   }
   if(x >= Image->width()) {
      x = Image->width() - 1;
   }
   y = mouseY + (int)OffsetY;
   if(y < 0) {
      y = 0;
   }
   if(y >= Image->height()) {
      y = Image->height() - 1;
   }
}
