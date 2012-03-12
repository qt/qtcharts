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
        // First series base color from COLOR_WINDOWFRAME
        DWORD colorWindowFrame;
        colorWindowFrame = GetSysColor(COLOR_WINDOWFRAME);
        m_seriesColors.append(QColor(GetRValue(colorWindowFrame), GetGValue(colorWindowFrame),GetBValue(colorWindowFrame)));

        // Second series base color from COLOR_HIGHLIGHT
        DWORD colorHighlight;
        colorHighlight = GetSysColor(COLOR_HIGHLIGHT);
        m_seriesColors.append(QColor(GetRValue(colorHighlight), GetGValue(colorHighlight),GetBValue(colorHighlight)));

        // Thirs series base color from the middle of the COLOR_ACTIVECAPTION /
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

        // TODO: COLOR_WINDOWTEXT for text color?
        // TODO: COLOR_INFOTEXT for tooltip text color?
        // TODO: COLOR_INFOBK for tooltip background color?
#elif Q_OS_LINUX
        // TODO: replace this dummy theme with linux specific theme
        m_seriesColors << QRgb(0xff707070);
        m_seriesColors << QRgb(0xffA0A0A0);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
#elif Q_OS_MAC
        // TODO: replace this dummy theme with OSX specific theme
        m_seriesColors << QRgb(0xff707070);
        m_seriesColors << QRgb(0xffA0A0A0);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
#else
        // TODO: replace this dummy theme with generic (not OS specific) theme
        m_seriesColors << QRgb(0xff707070);
        m_seriesColors << QRgb(0xffA0A0A0);
        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
#endif
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
