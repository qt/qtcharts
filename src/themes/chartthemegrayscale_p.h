#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeGrayscale: public ChartTheme
{
public:
    ChartThemeGrayscale():ChartTheme(QChart::ChartThemeGrayscale)
    {
        m_seriesColors << QRgb(0xFF869299);
        m_seriesColors << QRgb(0xFFA5BDCC);
        m_seriesColors << QRgb(0xFFE8FFFC);
        m_seriesColors << QRgb(0xFFCCC2C2);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
