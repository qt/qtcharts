#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeGrayscale: public ChartTheme
{
public:
    ChartThemeGrayscale():ChartTheme(QChart::ChartThemeGrayscale)
    {
        m_seriesColors << QRgb(0xff869299);
        m_seriesColors << QRgb(0xffa5bdcc);
        m_seriesColors << QRgb(0xffe8fffc);
        m_seriesColors << QRgb(0xffccc2c2);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffe0e3e5));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
