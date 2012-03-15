#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBlueCerulean: public ChartTheme
{
public:
    ChartThemeBlueCerulean() : ChartTheme(QChart::ChartThemeBlueCerulean)
    {
        // Series colors
        m_seriesColors << QRgb(0x38ad6b);
        m_seriesColors << QRgb(0x3c84a7);
        m_seriesColors << QRgb(0xeb8817);
        m_seriesColors << QRgb(0x7b7f8c);
        m_seriesColors << QRgb(0xbf593e);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0x2e303a));
        backgroundGradient.setColorAt(1.0, QRgb(0x121218));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont("arial");
        m_titleBrush = QBrush(QRgb(0xffffff));
        m_axisLinePen = QPen(QRgb(0x86878c));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0xffffff));
        m_gridLinePen = QPen(QRgb(0x86878c));
        m_gridLinePen.setWidth(1);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
