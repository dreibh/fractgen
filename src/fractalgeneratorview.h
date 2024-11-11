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
#include <KLed>
#endif


class FractalGeneratorDoc;
class FractalGeneratorApp;


class FractalGeneratorViewBase : public QWidget
{
   Q_OBJECT
   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorViewBase(QWidget*           parent,
                            const unsigned int width,
                            const unsigned int height);
   ~FractalGeneratorViewBase();

   // ====== Access methods =================================================
   inline FractalAlgorithmInterface* getAlgorithm() const { return Algorithm;   }
   inline ColorSchemeInterface* getColorScheme() const    { return ColorScheme; }
   inline unsigned int getWidth() const                   { return Width;       }
   inline unsigned int getHeight() const                  { return Height;      }

   virtual void changeSize(const unsigned int width, const unsigned int height);
   virtual void changeAlgorithm(const QString& identifier);
   void changeColorScheme(const QString& identifier);
   void changeC1C2(const std::complex<double>& newC1,
                   const std::complex<double>& newC2);

   // ====== Signals ========================================================
   Q_SIGNALS:
   void updateAlgorithm();
   void updateColorScheme();

   // ====== Protected methods and attributes ===============================
   protected:
   virtual void startCalculation(QImage* image);
   void stopCalculation();

   FractalBuffer*                   Buffer;
   FractalAlgorithmInterface*       Algorithm;
   ColorSchemeInterface*            ColorScheme;
   QList<FractalCalculationThread*> ThreadList;

   unsigned int                     ProgStep;
   unsigned int                     Width;
   unsigned int                     Height;
   std::complex<double>             C1;
   std::complex<double>             C2;
};


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

   virtual void configChanged();
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

   protected:
   void resizeEvent(QResizeEvent* resizeEvent) override;
   bool eventFilter(QObject* object, QEvent* event) override;

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
