#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeDefault: public ChartTheme
{
public:
    ChartThemeDefault():ChartTheme(QChart::ChartThemeDefault)
    {
        // TODO: replace this dummy theme with an actual theme
        m_seriesColors << QRgb(0xff707070);
        m_seriesColors << QRgb(0xffA0A0A0);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
