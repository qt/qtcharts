#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeScientific: public ChartTheme
{
public:
    ChartThemeScientific():ChartTheme(QChart::ChartThemeScientific)
    {
        // Series
        m_seriesColors << QRgb(0xFFAD00);
        m_seriesColors << QRgb(0x596A75);
        m_seriesColors << QRgb(0x202020);
        m_seriesColors << QRgb(0x474747);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xfffefc));
        backgroundGradient.setColorAt(1.0, QRgb(0xfffefc));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_axisLinePen = QPen(QRgb(0x0f0f0f));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0x3f3f3f));
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_gridLinePen = QPen(QRgb(0x0f0f0f));
        m_gridLinePen.setWidth(2);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
