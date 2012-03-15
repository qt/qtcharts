#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeVanilla: public ChartTheme
{
public:
    ChartThemeVanilla() : ChartTheme(QChart::ChartThemeVanilla)
    {
        // Series
        m_seriesColors << QRgb(0xd9c574);
        m_seriesColors << QRgb(0xd6a896);
        m_seriesColors << QRgb(0xa0a071);
        m_seriesColors << QRgb(0xd2d234);
        m_seriesColors << QRgb(0x88723a);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xfbf9f1));
        backgroundGradient.setColorAt(1.0, QRgb(0xf5f0dc));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_axisLinePen = QPen(QRgb(0x0f0f0f));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0xa0a071));
        m_gridLinePen = QPen(QRgb(0x0f0f0f));
        m_gridLinePen.setWidth(2);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
