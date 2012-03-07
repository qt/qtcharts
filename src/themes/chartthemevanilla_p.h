#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeVanilla: public ChartTheme
{
public:
    ChartThemeVanilla():ChartTheme(QChart::ChartThemeVanilla)
    {
        m_seriesColors << QColor(217, 197, 116);
        m_seriesColors << QColor(214, 168, 150);
        m_seriesColors << QColor(160, 160, 113);
        m_seriesColors << QColor(210, 210, 52);
        m_seriesColors << QColor(136, 114, 58);

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

        QLinearGradient g4;
        g4.setColorAt(0.0, m_seriesColors.at(3));
        g4.setColorAt(1.0, m_seriesColors.at(4));
        m_seriesGradients << g4;

        QLinearGradient backgroundGradient;
        backgroundGradient.setColorAt(0.0, QRgb(0xff9d844d));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
