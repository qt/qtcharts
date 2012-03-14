#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeLight: public ChartTheme
{
public:
    ChartThemeLight() : ChartTheme(QChart::ChartThemeLight)
    {
        // Series colors
        m_seriesColors << QRgb(0x1c9dde);
        m_seriesColors << QRgb(0xf7a015);
        m_seriesColors << QRgb(0x8dc444);
        generateSeriesGradients();

        // Background
        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffffff));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_chartBackgroundGradient = backgroundGradient;

        // Axes and other
        m_masterFont = QFont();
        m_axisLinePen = QPen(QRgb(0x424242));
        m_axisLinePen.setWidth(1);
        m_axisLabelBrush = QBrush(QRgb(0x424242));
        m_axisLabelPen = Qt::NoPen; // NoPen for performance reasons
        m_backgroundShadesPen = Qt::NoPen;
        m_backgroundShades = BackgroundShadesNone;
        m_gridLinePen = QPen(QRgb(0x424242));
        m_gridLinePen.setWidth(1);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
