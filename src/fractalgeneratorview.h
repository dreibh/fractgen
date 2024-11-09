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


class FractalGeneratorView : public QWidget
{
   Q_OBJECT
   // ====== Constructor/Destructor =========================================
   public:
   FractalGeneratorView(QWidget* parent);
   ~FractalGeneratorView();

   // ====== Access methods =================================================
   inline ImageDisplay* getDisplay() const                { return Display;             }
   inline FractalAlgorithmInterface* getAlgorithm() const { return Algorithm;           }
   inline ColorSchemeInterface* getColorScheme() const    { return ColorScheme;         }
   inline unsigned int getWidth() const                   { return Width;               }
   inline unsigned int getHeight() const                  { return Height;              }
   inline bool isZoomInPossible() const                   { return Selection;           }
   inline bool isZoomBackPossible() const                 { return ZoomList.size() > 0; }

   void configChanged();
   void changeSize(const int width, const int height);
   void changeAlgorithm(const QString& identifier);
   void changeColorScheme(const QString& identifier);
   void changeC1C2(const std::complex<double>& newC1,
                   const std::complex<double>& newC2);
   void print(QPrinter* printer);

   // ====== Slots ==========================================================
   public Q_SLOTS:
   void slotXScrollBarChange(int value);
   void slotYScrollBarChange(int value);
   void slotOffsetUpdate(const int newOffsetX, const int newOffsetY);
   void slotSelectionUpdate(const unsigned int x1, const unsigned int y1,
                            const unsigned int x2, const unsigned int y2);
   void copyToClipboard();
   void copySelectionToClipboard();
   void zoomIn();
   void zoomBack();
   void zoomReset();

   // ====== Signals ========================================================
   Q_SIGNALS:
   void updateZoomInPossible();
   void updateZoomBackPossible();
   void updateFractalAlgorithm();
   void updateColorScheme();

   protected:
   void resizeEvent(QResizeEvent* resizeEvent) override;
   bool eventFilter(QObject* object, QEvent* event) override;

   // ====== Private methods and attributes =================================
   private:
   void updateScrollBars();
   void updateLED(const bool busy);
   void updateView();
   void startCalculation();
   void stopCalculation();

   QScrollBar*                      XScrollBar;
   QScrollBar*                      YScrollBar;
#ifndef WITH_KDE
   QLabel*                          ControlLED;
#else
   KLed*                            ControlLED;
#endif
   ImageDisplay*                    Display;
   FractalBuffer*                   Buffer;
   QList<FractalCalculationThread*> ThreadList;
   FractalAlgorithmInterface*       Algorithm;
   ColorSchemeInterface*            ColorScheme;

   unsigned int                     ProgStep;
   std::complex<double>             C1;
   std::complex<double>             C2;
   std::complex<double>             SelectionC1;
   std::complex<double>             SelectionC2;
   bool                             Selection;
   unsigned int                     Width;
   unsigned int                     Height;
   std::list<std::pair<std::complex<double>,
                       std::complex<double>>> ZoomList;
};

#endif
