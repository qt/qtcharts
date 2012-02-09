#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeVanilla: public ChartTheme
{
public:
    ChartThemeVanilla():ChartTheme(QChart::ChartThemeVanilla)
    {
        m_seriesColor.append(QColor(217, 197, 116));
        m_seriesColor.append(QColor(214, 168, 150));
        m_seriesColor.append(QColor(160, 160, 113));
        m_seriesColor.append(QColor(210, 210, 52));
        m_seriesColor.append(QColor(136, 114, 58));

        m_gradientStartColor = QColor(QRgb(0xff9d844d));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
