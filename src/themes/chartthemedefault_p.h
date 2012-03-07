#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeDefault: public ChartTheme
{
public:
    ChartThemeDefault():ChartTheme(QChart::ChartThemeDefault)
    {
        m_seriesColors << QRgb(0xff000000);
        m_seriesColors << QRgb(0xff707070);

        QLinearGradient g1;
        g1.setColorAt(0.0, m_seriesColors.at(0));
        g1.setColorAt(1.0, m_seriesColors.at(1));
        m_seriesGradients << g1;

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
