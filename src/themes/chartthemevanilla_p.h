#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeVanilla: public ChartTheme
{
public:
    ChartThemeVanilla():ChartTheme(QChart::ChartThemeVanilla)
    {
        m_seriesColors << QColor(217, 197, 116);
        m_seriesColors << QColor(214, 168, 150);
        m_seriesColors << QColor(160, 160, 113);
        m_seriesColors << QColor(210, 210, 52);
        m_seriesColors << QColor(136, 114, 58);

        generateSeriesGradients();

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xff9d844d));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
