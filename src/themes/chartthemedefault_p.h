#include "charttheme_p.h"
#ifdef Q_OS_WIN
#include <windows.h>
#include <stdio.h>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeDefault: public ChartTheme
{
public:
    ChartThemeDefault():ChartTheme(QChart::ChartThemeDefault)
    {
#ifdef Q_OS_WIN
        // TODO: use theme specific window frame color as a series base color (it would give more
        // variation to the base colors in addition to the blue and black used now)
        // TODO: COLOR_WINDOWTEXT for text color?
        // TODO: COLOR_INFOTEXT for tooltip text color?
        // TODO: COLOR_INFOBK for tooltip background color?

        // First series base color from COLOR_HIGHLIGHT
        DWORD colorHighlight;
        colorHighlight = GetSysColor(COLOR_HIGHLIGHT);
        m_seriesColors.append(QColor(GetRValue(colorHighlight),
                                     GetGValue(colorHighlight),
                                     GetBValue(colorHighlight)));

        // Second series base color from COLOR_WINDOWFRAME
        DWORD colorWindowFrame;
        colorWindowFrame = GetSysColor(COLOR_WINDOWFRAME);
        m_seriesColors.append(QColor(GetRValue(colorWindowFrame),
                                     GetGValue(colorWindowFrame),
                                     GetBValue(colorWindowFrame)));

        // Third series base color from the middle of the COLOR_ACTIVECAPTION /
        // COLOR_GRADIENTACTIVECAPTION gradient
        DWORD colorGradientActiveCaptionLeft;
        colorGradientActiveCaptionLeft = GetSysColor(COLOR_ACTIVECAPTION);
        DWORD colorGradientActiveCaptionRight;
        colorGradientActiveCaptionRight = GetSysColor(COLOR_GRADIENTACTIVECAPTION);
        QLinearGradient g;
        QColor start = QColor(GetRValue(colorGradientActiveCaptionLeft),
                              GetGValue(colorGradientActiveCaptionLeft),
                              GetBValue(colorGradientActiveCaptionLeft));
        g.setColorAt(0.0, start);
        QColor end = QColor(GetRValue(colorGradientActiveCaptionRight),
                              GetGValue(colorGradientActiveCaptionRight),
                              GetBValue(colorGradientActiveCaptionRight));
        g.setColorAt(1.0, end);
        m_seriesColors.append(colorAt(g, 0.5));

        // Generate gradients from the base colors
        generateSeriesGradients();

        // Background fill color from COLOR_WINDOW
        QLinearGradient backgroundGradient;
        DWORD colorWindow;
        colorWindow = GetSysColor(COLOR_WINDOW);
        backgroundGradient.setColorAt(0.0, QColor(GetRValue(colorWindow),
                                                  GetGValue(colorWindow),
                                                  GetBValue(colorWindow)));
        backgroundGradient.setColorAt(1.0, QColor(GetRValue(colorWindow),
                                                  GetGValue(colorWindow),
                                                  GetBValue(colorWindow)));
        // Axes and other
        m_masterFont = QFont();
        m_masterFont.setPointSizeF(10.0);
        m_axisLinePen = QPen(Qt::black);
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(Qt::black);
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShadesBrush = QBrush(QColor(0xaf, 0xaf, 0xaf, 0x50));
        m_backgroundShades = BackgroundShadesVertical;

#elif defined(Q_OS_LINUX)
        // TODO: replace this dummy theme with linux specific theme
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xe9e9e9));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_masterFont.setPointSizeF(10.0);
        m_axisLinePen = QPen(Qt::black);
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(Qt::black);
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShadesBrush = QBrush(QColor(0xaf, 0xaf, 0xaf, 0x50));
        m_backgroundShades = BackgroundShadesVertical;

#elif defined(Q_OS_MAC)
        // TODO: replace this dummy theme with OSX specific theme
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xe9e9e9));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_masterFont.setPointSizeF(10.0);
        m_axisLinePen = QPen(Qt::black);
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(Qt::black);
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShadesBrush = QBrush(QColor(0xaf, 0xaf, 0xaf, 0x50));
        m_backgroundShades = BackgroundShadesVertical;

#else
        // TODO: replace this dummy theme with generic (not OS specific) theme
        m_seriesColors << QRgb(0x60a6e6);
        m_seriesColors << QRgb(0x92ca66);
        m_seriesColors << QRgb(0xeba85f);
        m_seriesColors << QRgb(0xfc5751);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_masterFont.setPointSizeF(10.0);
        m_axisLinePen = QPen(Qt::black);
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(Qt::black);
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShadesBrush = QBrush(QColor(0xaf, 0xaf, 0xaf, 0x50));
        m_backgroundShades = BackgroundShadesVertical;
#endif
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
