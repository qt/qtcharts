#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeIcy: public ChartTheme
{
public:
    ChartThemeIcy():ChartTheme(QChart::ChartThemeIcy)
    {
        m_seriesColors << QRgb(0xff0d2673);
        m_seriesColors << QRgb(0xff2685bf);
        m_seriesColors << QRgb(0xff3dadd9);
        m_seriesColors << QRgb(0xff62c3d9);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffebebeb));
        backgroundGradient.setColorAt(1.0, QRgb(0xfff8f9fb));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
