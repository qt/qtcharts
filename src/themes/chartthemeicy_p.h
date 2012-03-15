#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeIcy: public ChartTheme
{
public:
    ChartThemeIcy() : ChartTheme(QChart::ChartThemeIcy)
    {
        // Series
        m_seriesColors << QRgb(0x0d2673);
        m_seriesColors << QRgb(0x2685bf);
        m_seriesColors << QRgb(0x3dadd9);
        m_seriesColors << QRgb(0x62c3d9);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xebebeb));
        backgroundGradient.setColorAt(1.0, QRgb(0xf8f9fb));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_axisLinePen = QPen(QRgb(0x0f0f0f));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x3f3f3f));
        m_gridLinePen = QPen(QRgb(0x0f0f0f));
        m_gridLinePen.setWidth(2);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
