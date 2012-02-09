#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeGrayscale: public ChartTheme
{
public:
    ChartThemeGrayscale():ChartTheme(QChart::ChartThemeGrayscale)
    {
        m_seriesColor.append(QRgb(0xFF869299));
        m_seriesColor.append(QRgb(0xFFA5BDCC));
        m_seriesColor.append(QRgb(0xFFE8FFFC));
        m_seriesColor.append(QRgb(0xFFCCC2C2));

        m_gradientStartColor = QColor(QRgb(0xffffffff));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
