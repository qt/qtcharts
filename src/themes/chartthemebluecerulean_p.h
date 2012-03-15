#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeBlueCerulean: public ChartTheme
{
public:
    ChartThemeBlueCerulean() : ChartTheme(QChart::ChartThemeBlueCerulean)
    {
        // Series colors
        m_seriesColors << QRgb(0xc7e85b);
        m_seriesColors << QRgb(0x5dbe9b);
        m_seriesColors << QRgb(0x4fbef3);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0x056188));
        backgroundGradient.setColorAt(1.0, QRgb(0x101a33));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_axisLinePen = QPen(QRgb(0xf7f7ff));
        m_axisLinePen.setWidth(2);
        m_axisLabelBrush = QBrush(QRgb(0xf7f7ff));
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShades = BackgroundShadesNone;
        m_gridLinePen = QPen(QRgb(0xf7f7ff));
        m_gridLinePen.setWidth(1);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
