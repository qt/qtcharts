#ifndef CHART_H
#define CHART_H

#include <QDeclarativeItem>
#include <QPainter>

class Chart : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(int theme READ theme WRITE setTheme NOTIFY themeChanged)

public:
    Chart(QDeclarativeItem *parent = 0) :
            QDeclarativeItem(parent), m_theme(0)
    {
        setFlag(QGraphicsItem::ItemHasNoContents, false);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        // TODO: remove
        QPen pen(QColor(0, 0, 0), 10);
        painter->setPen(pen);
        if(smooth() == true) {
            painter->setRenderHint(QPainter::Antialiasing, true);
        }
        painter->drawLine(0, 0, 100, 100);
    }

    int theme() const { return m_theme; }

    // Set methods
    void setTheme(int theme) {
        if (theme != m_theme) {
            m_theme = theme;
            updateSize();
            emit themeChanged();
            update();
        }
    }

signals:
    void themeChanged();

private:
    void updateSize() {
//        setX(qMin(m_x1, m_x2) - m_penWidth/2);
//        setY(qMin(m_y1, m_y2) - m_penWidth/2);
//        setWidth(qAbs(m_x2 - m_x1) + m_penWidth);
//        setHeight(qAbs(m_y2 - m_y1) + m_penWidth);
    }

private:
    int m_theme;
};

QML_DECLARE_TYPE(Chart)

#endif // CHART_H
