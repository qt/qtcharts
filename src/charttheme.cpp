#include "charttheme_p.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

void ChartThemeData::setTheme(int theme)
{
    m_seriesThemes.clear();
    m_seriesIndex = 0;
    m_currentTheme = theme;

    switch (theme) {
    case QChart::ChartThemeDefault:
        // line: solid, dashed, dotted
        // line width: 1
        // line color (and opacity)
        // line shadow (on/off)
        // marker shape: "x", "o", "."
        // TODO: define the default theme based on the OS
        m_seriesThemes.append(SeriesTheme(QRgb(0xff000000), 2));
        m_seriesThemes.append(SeriesTheme(QRgb(0xff707070), 2));
        m_gradientStartColor = QColor(QRgb(0xffffffff));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
        break;
    case QChart::ChartThemeVanilla:
        m_seriesThemes.append(SeriesTheme(QColor(217, 197, 116), 6));
        m_seriesThemes.append(SeriesTheme(QColor(214, 168, 150), 4));
        m_seriesThemes.append(SeriesTheme(QColor(160, 160, 113), 6));
        m_seriesThemes.append(SeriesTheme(QColor(210, 210, 52), 4));
        m_seriesThemes.append(SeriesTheme(QColor(136, 114, 58), 6));

        m_gradientStartColor = QColor(QRgb(0xff9d844d));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
        break;
    case QChart::ChartThemeIcy:
        m_seriesThemes.append(SeriesTheme(QColor(0, 3, 165), 2));
        m_seriesThemes.append(SeriesTheme(QColor(49, 52, 123), 2));
        m_seriesThemes.append(SeriesTheme(QColor(71, 114, 187), 2));
        m_seriesThemes.append(SeriesTheme(QColor(48, 97, 87), 2));
        m_seriesThemes.append(SeriesTheme(QColor(19, 71, 90), 2));
        m_seriesThemes.append(SeriesTheme(QColor(110, 70, 228), 2));

        m_gradientStartColor = QColor(QRgb(0xffe4ffff));
        m_gradientEndColor = QColor(QRgb(0xffe4ffff));
        break;
    case QChart::ChartThemeGrayscale:
        m_seriesThemes.append(SeriesTheme(QColor(0, 0, 0), 2));
        m_seriesThemes.append(SeriesTheme(QColor(50, 50, 50), 2));
        m_seriesThemes.append(SeriesTheme(QColor(100, 100, 100), 2));
        m_seriesThemes.append(SeriesTheme(QColor(140, 140, 140), 2));
        m_seriesThemes.append(SeriesTheme(QColor(180, 180, 180), 2));

        m_gradientStartColor = QColor(QRgb(0xffffffff));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
        break;
    case QChart::ChartThemeUnnamed1:
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff3fa9f5)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xff7AC943)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF931E)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF1D25)), 2));
        m_seriesThemes.append(SeriesTheme(QColor(QRgb(0xffFF7BAC)), 2));

        m_gradientStartColor = QColor(QRgb(0xfff3dc9e));
        m_gradientEndColor = QColor(QRgb(0xffafafaf));
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}

ChartTheme::ChartTheme(QObject *parent) :
    QObject(parent),
    d(new ChartThemeData())
{
    d->m_currentTheme = QChart::ChartThemeInvalid;
    d->m_seriesIndex = 0;
}

void ChartTheme::setTheme(int theme)
{
    if (theme != d->m_currentTheme) {
        d->setTheme(theme);
        foreach (ChartThemeObserver *o, d->m_observers)
            o->themeChanged(this);
    }
}

SeriesTheme ChartTheme::themeForSeries()
{
    if (d->m_seriesThemes.count() == 0) {
        return SeriesTheme();
    } else {
        // Get the next available theme for the series; if no more themes available start over
        // beginning from the first theme in the list
        SeriesTheme nextTheme =
                d->m_seriesThemes[d->m_seriesIndex % d->m_seriesThemes.count()];
        d->m_seriesIndex++;
        return nextTheme;
    }
}


#include "moc_charttheme_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
