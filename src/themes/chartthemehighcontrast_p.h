#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeHighContrast : public ChartTheme
{
public:
    ChartThemeHighContrast() : ChartTheme(QChart::ChartThemeHighContrast)
    {
        // Series colors
        m_seriesColors << QRgb(0x202020);
        m_seriesColors << QRgb(0x596a74);
        m_seriesColors << QRgb(0xffab03);
        m_seriesColors << QRgb(0x038e9b);
        m_seriesColors << QRgb(0xff4a41);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_titleBrush = QBrush(QRgb(0x181818));
        m_axisLinePen = QPen(QRgb(0x8c8c8c));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x181818));
        m_gridLinePen = QPen(QRgb(0x8c8c8c));
        m_gridLinePen.setWidth(1);
        m_backgroundShadesBrush = QBrush(QRgb(0xffeecd));
        m_backgroundShades = BackgroundShadesHorizontal;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
