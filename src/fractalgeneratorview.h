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

#ifndef FRACTALGENERATORVIEW_H
#define FRACTALGENERATORVIEW_H

#include "imagedisplay.h"
#include "fractalgeneratorviewbase.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollBar>
#include <QtPrintSupport/QPrinter>
#include <QResizeEvent>
#ifdef WITH_KDE
#include <KLed>
#endif


class FractalGeneratorView : public FractalGeneratorViewBase
{
   Q_OBJECT
   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorView(QWidget* parent);
   ~FractalGeneratorView();

   // ====== Access methods =================================================
   inline bool isZoomInPossible()    const { return Selection;           }
   inline bool isZoomBackPossible()  const { return ZoomList.size() > 0; }
   inline ImageDisplay* getDisplay() const { return Display;             }
   void print(QPrinter* printer);

   virtual void configChanged() override;
   virtual void changeSize(const unsigned int width,
                           const unsigned int height) override;
   virtual void changeAlgorithm(const QString& identifier) override;

   // ====== Signals ========================================================
   Q_SIGNALS:
   void updateZoomInPossible();
   void updateZoomBackPossible();

   // ====== Slots ==========================================================
   public Q_SLOTS:
   void slotXScrollBarChange(int value);
   void slotYScrollBarChange(int value);
   void slotOffsetUpdate(const int newOffsetX, const int newOffsetY);
   void slotSelectionUpdate(const unsigned int x1, const unsigned int y1,
                            const unsigned int x2, const unsigned int y2);
   void copyToClipboard();
   void copySelectionToClipboard();
   void zoomInToSelection();
   void zoomAdjustment(const int deltaX, const int deltaY, const int deltaZoom);
   void zoomBack();
   void zoomReset();
   virtual void calculationProgressed(FractalCalculationThread* thread,
                                      bool                      finished) override;

   protected:
   void resizeEvent(QResizeEvent* resizeEvent) override;

   // ====== Protected methods ==============================================
   virtual void startCalculation(QImage* image) override;

   // ====== Private methods and attributes =================================
   private:
   void updateScrollBars();
   void updateLED(const bool busy);
   void updateView();

   QScrollBar*          XScrollBar;
   QScrollBar*          YScrollBar;
   ImageDisplay*        Display;
#ifndef WITH_KDE
   QLabel*              ControlLED;
#else
   KLed*                ControlLED;
#endif

   std::complex<double> SelectionC1;
   std::complex<double> SelectionC2;
   bool                 Selection;

   std::list<std::pair<std::complex<double>,
                       std::complex<double>>> ZoomList;
};

#endif
