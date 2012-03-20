#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBlueCerulean: public ChartTheme
{
public:
    ChartThemeBlueCerulean() : ChartTheme(QChart::ChartThemeBlueCerulean)
    {
        // Series colors
        m_seriesColors << QRgb(0xc7e85b);
        m_seriesColors << QRgb(0x1cb54f);
        m_seriesColors << QRgb(0x5cbf9b);
        m_seriesColors << QRgb(0x009fbf);
        m_seriesColors << QRgb(0xee7392);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient(0.5, 0.0, 0.5, 1.0);
        backgroundGradient.setColorAt(0.0, QRgb(0x056189));
        backgroundGradient.setColorAt(1.0, QRgb(0x101a31));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont("arial");
        m_titleBrush = QBrush(QRgb(0xffffff));
        m_axisLinePen = QPen(QRgb(0xd6d6d6));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0xffffff));
        m_gridLinePen = QPen(QRgb(0x84a2b0));
        m_gridLinePen.setWidth(1);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
