#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeScientific: public ChartTheme
{
public:
    ChartThemeScientific():ChartTheme(QChart::ChartThemeScientific)
    {
        m_seriesColors << QRgb(0xFFFFAD00);
        m_seriesColors << QRgb(0xFF596A75);
        m_seriesColors << QRgb(0xFF202020);
        m_seriesColors << QRgb(0xFF474747);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xfffffefc));
        backgroundGradient.setColorAt(1.0, QRgb(0xfffffefc));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
