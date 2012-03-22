#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBrownSand: public ChartTheme
{
public:
    ChartThemeBrownSand() : ChartTheme(QChart::ChartThemeBrownSand)
    {
        // Series colors
        m_seriesColors << QRgb(0xb39b72);
        m_seriesColors << QRgb(0xb3b376);
        m_seriesColors << QRgb(0xc35660);
        m_seriesColors << QRgb(0x536780);
        m_seriesColors << QRgb(0x494345);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xf3ece0));
        backgroundGradient.setColorAt(1.0, QRgb(0xf3ece0));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont("arial");
        m_titleBrush = QBrush(QRgb(0x404044));
        m_axisLinePen = QPen(QRgb(0xb5b0a7));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x404044));
        m_gridLinePen = QPen(QRgb(0xd4cec3));
        m_gridLinePen.setWidth(1);
        m_backgroundShades = BackgroundShadesNone;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
