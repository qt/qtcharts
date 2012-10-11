#include "callout.h"
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

Callout::Callout(QGraphicsItem * parent):
    QGraphicsItem(parent)
{
}

QRectF Callout::boundingRect() const
{
    QPointF anchor = mapFromParent(m_anchor);
    QRectF rect;
    rect.setLeft(qMin(m_textRect.left(), anchor.x()));
    rect.setRight(qMax(m_textRect.right(), anchor.x()));
    rect.setTop(qMin(m_textRect.top(), anchor.y()));
    rect.setBottom(qMax(m_textRect.bottom(), anchor.y()));
    return rect;
}

void Callout::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPainterPath path;
    path.addRoundedRect(m_textRect, 5, 5);

    QPointF anchor = mapFromParent(m_anchor);
    if (!m_textRect.contains(anchor)) {
        QPointF point1, point2;

        // establish the position of the anchor point in relation to m_textRect
        bool above = anchor.y() <= m_textRect.top();
        bool aboveCenter = anchor.y() > m_textRect.top() && anchor.y() <= m_textRect.center().y();
        bool belowCenter = anchor.y() > m_textRect.center().y() && anchor.y() <= m_textRect.bottom();
        bool below = anchor.y() > m_textRect.bottom();

        bool onLeft = anchor.x() <= m_textRect.left();
        bool leftOfCenter = anchor.x() > m_textRect.left() && anchor.x() <= m_textRect.center().x();
        bool rightOfCenter = anchor.x() > m_textRect.center().x() && anchor.x() <= m_textRect.right();
        bool onRight = anchor.x() > m_textRect.right();

        // get the nearest m_textRect corner.
        qreal x = (onRight + rightOfCenter) * m_textRect.width();
        qreal y = (below + belowCenter) * m_textRect.height();
        bool cornerCase = (above && onLeft) || (above && onRight) || (below && onLeft) || (below && onRight);
        bool vertical = qAbs(anchor.x() - x) > qAbs(anchor.y() - y);

        qreal x1 = x + leftOfCenter * 10 - rightOfCenter * 20 + cornerCase * !vertical * (onLeft * 10 - onRight * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20 + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftOfCenter * 20 - rightOfCenter * 10 + cornerCase * !vertical * (onLeft * 20 - onRight * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10 + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        path.lineTo(mapFromParent(m_anchor));
        path.lineTo(point2);
        path = path.simplified();
    }
    painter->setBrush(QColor(255, 255, 255));
    painter->drawPath(path);
    painter->drawText(m_textRect.adjusted(2, 2, 0, 0), m_text);
}

void Callout::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_textRect.contains(event->pos())) {
        m_clickOffset = event->pos();
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
}

void Callout::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_textRect.contains(event->pos())){
        setPos(mapToParent(event->pos() - m_clickOffset));
        event->setAccepted(true);
    } else {
        event->setAccepted(false);
    }
}

void Callout::setText(const QString &text)
{
    m_text = text;
    QFontMetrics metrics(m_font);
    prepareGeometryChange();
    m_textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, m_text).adjusted(0, 0, 4, 4);
}

void Callout::setAnchor(QPointF point)
{
    m_anchor = point;
}
