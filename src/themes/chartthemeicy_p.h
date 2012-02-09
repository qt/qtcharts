#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartThemeIcy: public ChartTheme
{
public:
    ChartThemeIcy()
    {
        m_seriesColor.append(QRgb(0xFF0D2673));
        m_seriesColor.append(QRgb(0xFF2685BF));
        m_seriesColor.append(QRgb(0xFF3DADD9));
        m_seriesColor.append(QRgb(0xFF62C3D9));

        m_gradientStartColor = QColor(QRgb(0xffBDE3F2));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
    }
};

QTCOMMERCIALCHART_END_NAMESPACE
