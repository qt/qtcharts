#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeLight: public ChartTheme
{
public:
    ChartThemeLight() : ChartTheme(QChart::ChartThemeLight)
    {
        // Series colors
        m_seriesColors << QRgb(0x209fdf);
        m_seriesColors << QRgb(0x99ca53);
        m_seriesColors << QRgb(0xf6a625);
        m_seriesColors << QRgb(0x6d5fd5);
        m_seriesColors << QRgb(0xbf593e);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont("arial");
        m_axisLinePen = QPen(0xd6d6d6);
        m_axisLinePen.setWidth(1);
        m_axisLabelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xe2e2e2));
        m_gridLinePen.setWidth(1);
        m_backgroundShades = BackgroundShadesNone;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
