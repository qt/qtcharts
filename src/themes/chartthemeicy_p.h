#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeIcy: public ChartTheme
{
public:
    ChartThemeIcy():ChartTheme(QChart::ChartThemeIcy)
    {
        m_seriesColors << QRgb(0xFF0D2673);
        m_seriesColors << QRgb(0xFF2685BF);
        m_seriesColors << QRgb(0xFF3DADD9);
        m_seriesColors << QRgb(0xFF62C3D9);

        QLinearGradient g1;
        g1.setColorAt(0.0, m_seriesColors.at(0));
        g1.setColorAt(1.0, m_seriesColors.at(1));
        m_seriesGradients << g1;

        QLinearGradient g2;
        g2.setColorAt(0.0, m_seriesColors.at(1));
        g2.setColorAt(1.0, m_seriesColors.at(2));
        m_seriesGradients << g2;

        QLinearGradient g3;
        g3.setColorAt(0.0, m_seriesColors.at(2));
        g3.setColorAt(1.0, m_seriesColors.at(3));
        m_seriesGradients << g3;

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xffBDE3F2));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
