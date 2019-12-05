/* ==========================================================================
 * ====                   FRACTAL GRAPHICS GENERATOR                     ====
 * ==========================================================================
 *
 * Copyright (C) 2003-2020 by Thomas Dreibholz
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

#ifndef FRACTALGENERATORVIEW_H
#define FRACTALGENERATORVIEW_H

#include "imagedisplay.h"
#include "fractalbuffer.h"
#include "fractalalgorithminterface.h"
#include "fractalcalculationthread.h"
#include "colorschemeinterface.h"

#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtPrintSupport/QPrinter>
#include <QResizeEvent>
#include <QEvent>

#ifdef WITH_KDE
#include <KWidgetsAddons/KLed>
#endif


class FractalGeneratorDoc;
class FractalGeneratorApp;


class FractalGeneratorView : public QWidget
{
   Q_OBJECT
   public:
   FractalGeneratorView(QWidget* parent);
   ~FractalGeneratorView();

   inline ImageDisplay* getDisplay() const { return(Display); }
   inline FractalAlgorithmInterface* getAlgorithm() const { return(Algorithm); }
   inline ColorSchemeInterface* getColorScheme() const { return(ColorScheme); }
   inline int getSizeX() { return(SizeX); }
   inline int getSizeY() { return(SizeY); }
   inline bool isZoomInPossible() { return(Selection); }
   inline bool isZoomBackPossible() { return(zoomList.size() > 0); }

   void print(QPrinter *printer);
   void configChanged();
   void changeSize(int X, int Y);
   void changeAlgorithm(int index);
   void changeColorScheme(int index);
   void changeC1C2(std::complex<double> newC1, std::complex<double> newC2);


   public Q_SLOTS:
   void slotXScrollBarChange(int value);
   void slotYScrollBarChange(int value);
   void slotOffsetUpdate(int newOffsetX, int newOffsetY);
   void slotSelectionUpdate(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
   void zoomIn();
   void zoomBack();
   void zoomReset();

   Q_SIGNALS:
   void updateZoomInPossible();
   void updateZoomBackPossible();
   void updateFractalAlgorithm();
   void updateColorScheme();

   protected:
   void resizeEvent(QResizeEvent* resizeEvent) override;
   bool eventFilter(QObject* object, QEvent* event) override;

   private:
   void updateScrollBars();
   void updateLED(const bool busy);
   void updateView();
   void startCalculation();
   void stopCalculation();

   QScrollBar*                XScrollBar;
   QScrollBar*                YScrollBar;
#ifndef WITH_KDE
   QLabel*                    ControlLED;
#else
   KLed*                      ControlLED;
#endif
   ImageDisplay*              Display;
   FractalBuffer*             Buffer;

   FractalCalculationThread*  Thread;
   FractalAlgorithmInterface* Algorithm;
   ColorSchemeInterface*      ColorScheme;

   unsigned int               ProgStep;
   std::complex<double>       C1;
   std::complex<double>       C2;
   std::complex<double>       SelectionC1;
   std::complex<double>       SelectionC2;
   bool                       Selection;
   int                        SizeX;
   int                        SizeY;

   std::list<std::pair<std::complex<double>, std::complex<double> > > zoomList;
};

#endif // FRACTALGENERATORVIEW_H
