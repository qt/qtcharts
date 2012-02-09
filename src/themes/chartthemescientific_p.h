#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeScientific: public ChartTheme
{
public:
    ChartThemeScientific():ChartTheme(QChart::ChartThemeScientific)
    {
        m_seriesColor.append(QRgb(0xFF000000));
        m_seriesColor.append(QRgb(0xFFFFAD00));
        m_seriesColor.append(QRgb(0xFF596A75));
        m_seriesColor.append(QRgb(0xFF474747));

        m_gradientStartColor = QColor(QRgb(0xffafafaf));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
