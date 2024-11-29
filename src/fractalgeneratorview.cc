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

#include "fractalgeneratorview.h"
#include "fractalgeneratordoc.h"
#include "fractalgenerator.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QEvent>
#include <QImage>
#include <QPainter>
#include <QResizeEvent>
#include <QScreen>



// ###### Constructor #######################################################
FractalGeneratorView::FractalGeneratorView(QWidget* parent)
   : // Set initial size to 75% of the screen dimensions:
     FractalGeneratorViewBase(parent,
                              QGuiApplication::primaryScreen()->geometry().width()  * 0.75,
                              QGuiApplication::primaryScreen()->geometry().height() * 0.75)
{
   // ====== Initialise widgets =============================================
   Display = new ImageDisplay(this);
   Q_CHECK_PTR(Display);
   connect(Display, SIGNAL(offsetUpdate(int, int)),
           this, SLOT(slotOffsetUpdate(int, int)));
   connect(Display, SIGNAL(zoomInToSelection()),
           this, SLOT(zoomInToSelection()));
   connect(Display, SIGNAL(zoomAdjustment(int, int, int)),
           this, SLOT(zoomAdjustment(int, int, int)));
   connect(Display,
           SIGNAL(selection(unsigned int, unsigned int, unsigned int, unsigned int)),
           this,
           SLOT(slotSelectionUpdate(unsigned int, unsigned int, unsigned int, unsigned int)));
   XScrollBar = new QScrollBar(Qt::Horizontal, this);
   Q_CHECK_PTR(XScrollBar);
   connect(XScrollBar, SIGNAL(valueChanged(int)),
           this, SLOT(slotXScrollBarChange(int)));
   YScrollBar = new QScrollBar(Qt::Vertical, this);
   Q_CHECK_PTR(YScrollBar);
   connect(YScrollBar, SIGNAL(valueChanged(int)), this,
           SLOT(slotYScrollBarChange(int)));

 #ifndef WITH_KDE
   ControlLED = new QLabel(this);
   Q_CHECK_PTR(ControlLED);
   ControlLED->setFrameStyle(QFrame::Panel|QFrame::Sunken);
#else
   ControlLED = new KLed(QColor(Qt::red), KLed::State::Off,
                         KLed::Look::Raised, KLed::Shape::Circular, this);
   Q_CHECK_PTR(ControlLED);
#endif

   // ====== Initialise layout ==============================================
   QGridLayout* layout = new QGridLayout(this);
   Q_CHECK_PTR(layout);
   layout->addWidget(Display, 0, 0);
   layout->addWidget(XScrollBar, 1, 0);
   layout->addWidget(YScrollBar, 0, 1);
   layout->addWidget(ControlLED, 1, 1);

   Display->reset(Width, Height);
   Display->setMinimumSize(Width, Height);
   Buffer->reset(Display->imageWidth(), Display->imageHeight());

   // ====== Start calculation ==============================================
   Selection = false;
   updateScrollBars();
   startCalculation(Display->image());
}


// ###### Destructor ########################################################
FractalGeneratorView::~FractalGeneratorView()
{
}


// ###### Change image size #################################################
void FractalGeneratorView::changeSize(const unsigned int width,
                                          const unsigned int height)
{
   FractalGeneratorViewBase::changeSize(width, height);
   Selection = false;
   Display->reset(Width, Height);
   updateScrollBars();
}


// ###### Configuration update -> restart calculation #######################
void FractalGeneratorView::configChanged()
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change configuration ===========================================
   Buffer->clear();
   Display->reset(Display->imageWidth(), Display->imageHeight());
   emit updateZoomInPossible();
   emit updateZoomBackPossible();
   startCalculation(Display->image());
}


// ###### Change fractal algorithm ##########################################
void FractalGeneratorView::changeAlgorithm(const QString& identifier)
{
   FractalGeneratorViewBase::changeAlgorithm(identifier);
   Selection = false;
   ZoomList.clear();
}


// ###### Resize ############################################################
void FractalGeneratorView::resizeEvent(QResizeEvent*)
{
   updateScrollBars();
}


// ###### Vertical scollbar update ##########################################
void FractalGeneratorView::slotXScrollBarChange(const int value)
{
   int newOffset = value;

   if(newOffset + Display->width() >= (int)Display->imageWidth()) {
      newOffset = Display->imageWidth() - Display->width();
   }
   if(newOffset < 0) {
      newOffset = 0;
   }

   if(Display->offsetX() != (unsigned int)newOffset) {
      Display->setOffsetX((unsigned int)newOffset);
      Display->update();
   }
}


// ###### Horizontal scollbar update ########################################
void FractalGeneratorView::slotYScrollBarChange(const int value)
{
   int newOffset = value;

   if(newOffset + Display->height() >= (int)Display->imageHeight()) {
      newOffset = Display->imageHeight() - Display->height();
   }
   if(newOffset < 0) {
      newOffset = 0;
   }

   if(Display->offsetY() != (unsigned int)newOffset) {
      Display->setOffsetY((unsigned int)newOffset);
      Display->update();
   }
}


// ###### Offset update #####################################################
void FractalGeneratorView::slotOffsetUpdate(const int newOffsetX,
                                            const int newOffsetY)
{
   XScrollBar->setValue(newOffsetX);
   YScrollBar->setValue(newOffsetY);
}


// ###### Selection update ###################################################
void FractalGeneratorView::slotSelectionUpdate(const unsigned int x1,
                                               const unsigned int y1,
                                               const unsigned int x2,
                                               const unsigned int y2)
{
   SelectionC1 = std::complex<double>(C1.real() + x1 * ((C2.real() - C1.real()) / Display->imageWidth()),
                                      C1.imag() + y1 * ((C2.imag() - C1.imag()) / Display->imageHeight()));
   SelectionC2 = std::complex<double>(C1.real() + x2 * ((C2.real() - C1.real()) / Display->imageWidth()),
                                      C1.imag() + y2 * ((C2.imag() - C1.imag()) / Display->imageHeight()));
   // printf("Selected: %d %d - %d %d\n",x1,y1,x2,y2);
   if((x1 != x2) && (y1 != y2)) {
      Selection = true;
   }
   else {
      Selection = false;
   }
   emit updateZoomInPossible();
}



// ###### Update scroll bars ################################################
void FractalGeneratorView::updateScrollBars()
{
   XScrollBar->setMaximum(std::max(0, Display->imageWidth()  - Display->width()));
   XScrollBar->setPageStep(std::min(Display->width(), Display->imageWidth()) / 4);
   YScrollBar->setMaximum(std::max(0, Display->imageHeight() - Display->height()));
   YScrollBar->setPageStep(std::min(Display->height(), Display->imageHeight()) / 4);
}


// ###### Update status LED #################################################
void FractalGeneratorView::updateLED(const bool busy)
{
#ifndef WITH_KDE
   QPixmap pixmap(16, 16);
   pixmap.fill((busy == true) ? Qt::red : Qt::green);
   ControlLED->setPixmap(pixmap);
#else
   ControlLED->setState((busy == true) ? KLed::State::On : KLed::State::Off);
#endif
}


// ###### Start calculation #################################################
void FractalGeneratorView::startCalculation(QImage* image)
{
   updateLED(true);
   FractalGeneratorViewBase::startCalculation(image);
}


// ###### Calculation made progress #########################################
void FractalGeneratorView::calculationProgressed(FractalCalculationThread* thread,
                                                 const bool                finished)
{
   FractalGeneratorViewBase::calculationProgressed(thread, finished);
   Display->update();
   if(ThreadList.size() == 0) {
      updateLED(false);
   }
}


// ###### Print image #######################################################
void FractalGeneratorView::print(QPrinter* printer)
{
   const int width  = Display->imageWidth();
   const int height = Display->imageHeight();
   char titleString[512];
   snprintf((char*)&titleString, sizeof(titleString),
            "%s  -  c1=%f - %fi; c2=%f - %fi; %d iterations",
            Algorithm->getDescription().toUtf8().constData(),
            C1.real(), C1.imag(), C2.real(), C2.imag(),
            *Algorithm->getMaxIterations());
   const QString title = QString::fromLocal8Bit(titleString);

   QFont font(QStringLiteral("Times"), 9);
   font.setBold(true);

   QFontMetrics fontMetrics(font);
   QRect        boundingRect = fontMetrics.boundingRect(title);
   const int textwidth  = boundingRect.width();
   const int textheight = boundingRect.height();

   printer->setDocName(title);
   printer->setCreator(QStringLiteral("Thomas Dreibholz's Fractal Generator II"));

   int pagesx = 1;
   int pagesy = 1;

   QPainter p;
   p.begin(printer);
   const int xstep = width  / pagesx;
   const int ystep = height / pagesy;
   for(int y = 0;y < pagesy;y++) {
     for(int x = 0;x < pagesx;x++) {
        p.setWindow(0, 0, xstep, ystep);
        p.drawImage(0, 0, *(Display->image()), x * xstep, y * ystep, xstep, ystep);

        if((x == pagesx - 1) && (y == pagesy - 1)) {
           p.setWindow(0, 0, (int)(1.1 * textwidth), textheight * 50);
           p.setPen(Qt::black);
           p.setFont(font);
           p.drawText(0, textheight * 48, (int)(1.1 * textwidth), textheight, Qt::AlignHCenter|Qt::AlignVCenter, title);
        }
        else {
           printer->newPage();
        }

        /*
        p.setWindow(0, 0, width, height);
        p.setPen(Qt::red);
        p.drawLine(0, 0, Display->imageWidth() - 1, Display->imageHeight() - 1);
        p.drawLine(0, Display->imageHeight() - 1, Display->imageWidth() - 1, 0);
        p.setPen(Qt::black);
        char str[16];
        snprintf((char*)&str,sizeof(str),"x=%d y=%d\n",x,y);
        p.drawText(0, 0, str);
        p.drawRect(0, 0, Display->imageWidth() - 1, Display->imageHeight() - 1);
        */
     }
   }
   p.end();
}


// ###### Reset zoom ########################################################
void FractalGeneratorView::zoomReset()
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change zoom ====================================================
   C1 = Algorithm->defaultC1();
   C2 = Algorithm->defaultC2();
   Algorithm->configure(Display->imageWidth(),
                        Display->imageHeight(),
                        C1, C2,
                        *Algorithm->getMaxIterations());
   ZoomList.clear();
   configChanged();
}


// ###### Copy full image to clipboard ######################################
void FractalGeneratorView::copyToClipboard()
{
   Display->copyToClipboard();
}


// ###### Copy selection to clipboard #######################################
void FractalGeneratorView::copySelectionToClipboard()
{
   Display->copySelectionToClipboard();
}


// ###### Zoom in ###########################################################
void FractalGeneratorView::zoomInToSelection()
{
   if(Selection) {
      // ====== Abort a running calculation =================================
      stopCalculation();

      // ====== Zoom in =====================================================
      ZoomList.push_back(std::pair<std::complex<double>, std::complex<double>>(C1, C2));
      const double               halfWidth  = (SelectionC2.real() - SelectionC1.real()) / 2.0;
      const double               halfHeight = (SelectionC2.imag() - SelectionC1.imag()) / 2.0;
      const std::complex<double> center     = std::complex<double>(
         SelectionC1.real() + halfWidth, SelectionC1.imag() + halfHeight);
      const double newHalfHeight = halfWidth * ((double)Display->imageHeight() / (double)Display->imageWidth());
      C1 = std::complex<double>(center.real() - halfWidth, center.imag() + newHalfHeight);
      C2 = std::complex<double>(center.real() + halfWidth, center.imag() - newHalfHeight);

      // ====== Update parameters ===========================================
      Selection = false;
      Display->reset(Display->imageWidth(), Display->imageHeight());
      Algorithm->configure(Display->imageWidth(), Display->imageHeight(),
                           C1, C2,
                           *Algorithm->getMaxIterations());
      configChanged();
   }
}


// ###### Zoom adjustment by mouse wheel ####################################
void FractalGeneratorView::zoomAdjustment(const int deltaX,
                                          const int deltaY,
                                          const int deltaZoom)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Adjust zoom ====================================================
   ZoomList.push_back(std::pair<std::complex<double>, std::complex<double>>(C1, C2));
   const double stepX   = (C2.real() - C1.real()) / Display->imageWidth();
   const double stepY   = (C2.imag() - C1.imag()) / Display->imageHeight();
   const int halfWidth  = Display->imageWidth()  / 2;
   const int halfHeight = Display->imageHeight() / 2;
   const std::complex<double> center = std::complex<double>(
      C1.real() - deltaX * stepX  +  halfWidth  * stepX,
      C1.imag() - deltaY * stepY  +  halfHeight * stepY);
   const double zoomFactor = (double)(Display->imageHeight() - deltaZoom) /
                                Display->imageHeight();
   C1 = std::complex<double>(center.real() - zoomFactor * halfWidth * stepX,
                             center.imag() - zoomFactor * halfHeight * stepY);
   C2 = std::complex<double>(center.real() + zoomFactor * halfWidth * stepX,
                             center.imag() + zoomFactor * halfHeight * stepY);

   // ====== Update parameters ==============================================
   Selection = false;
   Algorithm->configure(Display->imageWidth(), Display->imageHeight(),
                        C1, C2,
                        *Algorithm->getMaxIterations());
   configChanged();
}


// ###### Zoom back #########################################################
void FractalGeneratorView::zoomBack()
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Zoom back ======================================================
   if(ZoomList.size() > 0) {
      C1 = ZoomList.back().first;
      C2 = ZoomList.back().second;
      ZoomList.pop_back();
      Algorithm->configure(Display->imageWidth(), Display->imageHeight(),
                           C1, C2,
                           *Algorithm->getMaxIterations());
      configChanged();
   }
}
