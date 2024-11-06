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

#include "fractalgeneratorview.h"
#include "fractalgeneratordoc.h"
#include "fractalgenerator.h"

#include <stdio.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QPainter>
#include <QImage>
#include <QResizeEvent>
#include <QEvent>
#include <QScreen>


// ###### Constructor #######################################################
FractalGeneratorView::FractalGeneratorView(QWidget* parent)
   : QWidget(parent)
{
   installEventFilter(this);

   // ====== Initialise widgets =============================================
   Buffer = new FractalBuffer();
   Q_CHECK_PTR(Buffer);
   Display = new ImageDisplay(this);
   Q_CHECK_PTR(Display);
   connect(Display, SIGNAL(offsetUpdate(int, int)), this, SLOT(slotOffsetUpdate(int, int)));
   connect(Display, SIGNAL(zoom()), this, SLOT(zoomIn()));
   connect(Display, SIGNAL(selection(unsigned int, unsigned int, unsigned int, unsigned int)),
           this, SLOT(slotSelectionUpdate(unsigned int, unsigned int, unsigned int, unsigned int)));
   XScrollBar = new QScrollBar(Qt::Horizontal, this);
   Q_CHECK_PTR(XScrollBar);
   connect(XScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slotXScrollBarChange(int)));
   YScrollBar = new QScrollBar(Qt::Vertical, this);
   Q_CHECK_PTR(YScrollBar);
   connect(YScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slotYScrollBarChange(int)));

 #ifndef WITH_KDE
   ControlLED = new QLabel(this);
   Q_CHECK_PTR(ControlLED);
   ControlLED->setFrameStyle(QFrame::Panel|QFrame::Sunken);
#else
   ControlLED = new KLed(QColor(Qt::red), KLed::State::Off, KLed::Look::Raised, KLed::Shape::Circular, this);
   Q_CHECK_PTR(ControlLED);
#endif

   // ====== Initialise layout ==============================================
   QGridLayout* layout = new QGridLayout(this);
   Q_CHECK_PTR(layout);
   layout->addWidget(Display, 0, 0);
   layout->addWidget(XScrollBar, 1, 0);
   layout->addWidget(YScrollBar, 0, 1);
   layout->addWidget(ControlLED, 1, 1);

   // Set initial size to 75% of the screen dimensions:
   const QScreen* screen = QGuiApplication::primaryScreen();
   SizeWidth  = (int)rint(screen->geometry().width() * 0.75);
   SizeHeight = (int)rint(screen->geometry().height() * 0.75);

   Display->reset(SizeWidth, SizeHeight);
   Display->setMinimumSize(SizeWidth, SizeHeight);
   Buffer->reset(Display->imageWidth(), Display->imageHeight());

   // ====== Set up algorithm and color scheme ==============================
   Algorithm = FractalAlgorithmInterface::makeAlgorithmInstanceByIdentifier("Mandelbrot");
   Q_CHECK_PTR(Algorithm);
   ColorScheme = ColorSchemeInterface::makeColorSchemeInstanceByIdentifier("SimpleHSV");
   Q_CHECK_PTR(ColorScheme);
   C1 = Algorithm->defaultC1();
   C2 = Algorithm->defaultC2();
   Selection = false;
   ProgStep  = 8;
   Algorithm->configure(Display->imageWidth(),
                        Display->imageHeight(),
                        C1, C2,
                        Algorithm->defaultMaxIterations());
   ColorScheme->configure(Algorithm->getMaxIterations());

   // ====== Start calculation ==============================================
   updateScrollBars();
   startCalculation();
}


// ###### Destructor ########################################################
FractalGeneratorView::~FractalGeneratorView()
{
   delete Buffer;
   Buffer = nullptr;
}


// ###### Resize ############################################################
void FractalGeneratorView::resizeEvent(QResizeEvent*)
{
   updateScrollBars();
}


// ###### Vertical scollbar update ##########################################
void FractalGeneratorView::slotXScrollBarChange(int value)
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
void FractalGeneratorView::slotYScrollBarChange(int value)
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
void FractalGeneratorView::slotOffsetUpdate(int newOffsetX, int newOffsetY)
{
   XScrollBar->setValue(newOffsetX);
   YScrollBar->setValue(newOffsetY);
}


// ###### Selection update ###################################################
void FractalGeneratorView::slotSelectionUpdate(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
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


// ###### Change image size #################################################
void FractalGeneratorView::changeSize(int X, int Y)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change size ====================================================
   SizeWidth  = X;
   SizeHeight = Y;
   Display->reset(SizeWidth, SizeHeight);
   Buffer->reset(Display->imageWidth(), Display->imageHeight());

   Selection = false;
   Algorithm->changeSize(Display->imageWidth(),
                         Display->imageHeight());
   updateScrollBars();
}


// ###### Change C1 and C2 ##################################################
void FractalGeneratorView::changeC1C2(std::complex<double> NewC1, std::complex<double> NewC2)
{
   stopCalculation();
   C1 = NewC1;
   C2 = NewC2;
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


// ###### Print image #######################################################
void FractalGeneratorView::print(QPrinter* printer)
{
   int width  = Display->imageWidth();
   int height = Display->imageHeight();
   char titleString[512];
   snprintf((char*)&titleString, sizeof(titleString), "%s  -  c1=%f - %fi; c2=%f - %fi; %d iterations",
            Algorithm->getName(),
            C1.real(), C1.imag(), C2.real(), C2.imag(), *Algorithm->getMaxIterations());
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


// ###### Start calculation #################################################
void FractalGeneratorView::startCalculation()
{
   if(ThreadList.size() == 0) {
      const unsigned int threads = QThread::idealThreadCount();
      for(unsigned int i = 0; i < threads; i++) {
         FractalCalculationThread* thread =
            new FractalCalculationThread(this,
                                         Algorithm, ColorScheme, Buffer,
                                         Display->image(),
                                         ProgStep,
                                         threads, i);
         Q_CHECK_PTR(thread);
         thread->start();
         ThreadList.append(thread);
      }
      updateLED(true);
   }
}


// ###### Stop calculation ##################################################
void FractalGeneratorView::stopCalculation()
{
   if(ThreadList.size() > 0) {
      foreach(FractalCalculationThread* thread, ThreadList) {
         thread->stop();
      }
      while(ThreadList.size() > 0) {
         qApp->processEvents();
      }
   }
}


// ###### Handle events #####################################################
bool FractalGeneratorView::eventFilter(QObject*, QEvent* event)
{
   if(ThreadList.size() > 0) {
      if(event->type() == QEvent::User) {
         Display->update();
      }
      else if(event->type() == (QEvent::Type)(QEvent::User + 1)) {
         QList<FractalCalculationThread*>::iterator iterator = ThreadList.begin();
         while(iterator != ThreadList.end()) {
            FractalCalculationThread* thread = *iterator;
            if(thread->isFinished()) {
               delete thread;
               iterator = ThreadList.erase(iterator);
            }
            else {
               iterator++;
            }
         }
         Display->update();
         if(ThreadList.size() == 0) {
            updateLED(false);
         }
      }
   }
   return(false);
}


// ###### Change fractal algorithm ##########################################
void FractalGeneratorView::changeAlgorithm(int index)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change algorithm ===============================================
   delete Algorithm;
   Algorithm = FractalAlgorithmInterface::makeAlgorithmInstanceByIndex(index);
   Q_CHECK_PTR(Algorithm);
   C1 = Algorithm->defaultC1();
   C2 = Algorithm->defaultC2();
   Selection = false;
   Algorithm->configure(Display->imageWidth(), Display->imageHeight(),
                        C1, C2,
                        Algorithm->defaultMaxIterations());
   ColorScheme->configure(Algorithm->getMaxIterations());
   ZoomList.clear();
   emit updateFractalAlgorithm();
}


// ###### Change color scheme ###############################################
void FractalGeneratorView::changeColorScheme(int index)
{
   // ====== Abort a running calculation ====================================
   stopCalculation();

   // ====== Change color scheme ============================================
   delete ColorScheme;
   ColorScheme = ColorSchemeInterface::makeColorSchemeInstanceByIndex(index);
   Q_CHECK_PTR(ColorScheme);
   ColorScheme->configure(Algorithm->getMaxIterations());
   emit updateColorScheme();
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
   startCalculation();
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


// ###### Zoom in ###########################################################
void FractalGeneratorView::zoomIn()
{
   if(Selection) {
      // ====== Abort a running calculation =================================
      stopCalculation();

      // ====== Zoom in =====================================================
      ZoomList.push_back(std::pair<std::complex<double>, std::complex<double> >(C1, C2));
      const double halfWidth  = (SelectionC2.real() - SelectionC1.real()) / 2.0;
      const double halfHeight = (SelectionC2.imag() - SelectionC1.imag()) / 2.0;
      const std::complex<double> center = std::complex<double>(SelectionC1.real() + halfWidth,
                                                               SelectionC1.imag() + halfHeight);
      const double newHalfHeight = halfWidth * ((double)Display->imageHeight() / (double)Display->imageWidth());
      C1 = std::complex<double>(center.real() - halfWidth, center.imag() + newHalfHeight);
      C2 = std::complex<double>(center.real() + halfWidth, center.imag() - newHalfHeight);
      Selection = false;
      Buffer->clear();
      Display->reset(Display->imageWidth(), Display->imageHeight());
      Algorithm->configure(Display->imageWidth(), Display->imageHeight(),
                           C1, C2,
                           *Algorithm->getMaxIterations());
      configChanged();
   }
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
