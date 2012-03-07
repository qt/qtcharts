#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeGrayscale: public ChartTheme
{
public:
    ChartThemeGrayscale():ChartTheme(QChart::ChartThemeGrayscale)
    {
        m_seriesColors << QRgb(0xFF869299);
        m_seriesColors << QRgb(0xFFA5BDCC);
        m_seriesColors << QRgb(0xFFE8FFFC);
        m_seriesColors << QRgb(0xFFCCC2C2);

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
        backgroundGradient.setColorAt(0.0, QRgb(0xffffffff));
        backgroundGradient.setColorAt(1.0, QRgb(0xffafafaf));
        backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        m_backgroundGradient = backgroundGradient;
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
