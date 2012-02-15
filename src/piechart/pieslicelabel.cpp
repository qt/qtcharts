#include "pieslicelabel.h"
#include <QPainter>
#include <qmath.h>
#include <QGraphicsTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#define PI 3.14159265

PieSliceLabel::PieSliceLabel(QGraphicsItem* parent)
    :QGraphicsItem(parent)
{
    // set defaults
    m_pen = QPen(Qt::black);
}

void PieSliceLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setRenderHint(QPainter::Antialiasing);

    painter->setPen(m_pen);
    painter->drawPath(m_armPath);

    // TODO: do we need a pen for text?
    painter->setFont(m_font);
    painter->drawText(m_textRect, m_text);
}

void PieSliceLabel::updateGeometry()
{
    prepareGeometryChange();

    // calculate text size
    QFontMetricsF fm(m_font);
    QRectF textRect = fm.boundingRect(m_text);

    // calculate path for arm and text start point
    qreal dx = qSin(m_armAngle*(PI/180)) * m_armLength;
    qreal dy = -qCos(m_armAngle*(PI/180)) * m_armLength;
    QPointF parm1 = m_armStartPoint + QPointF(dx, dy);

    // calculate horizontal arm and text position
    QPointF parm2 = parm1;
    textRect.moveBottomLeft(parm1);
    if (m_armAngle < 180) { // arm swings the other way on the left side
         parm2 += QPointF(m_textRect.width(), 0);
    } else {
         parm2 += QPointF(-m_textRect.width(),0);
         textRect.moveBottomLeft(parm2);
    }

    // update arm path
    QPainterPath path;
    path.moveTo(m_armStartPoint);
    path.lineTo(parm1);
    path.lineTo(parm2);

    // update paths & rects
    m_armPath = path;
    m_textRect = textRect;
    m_rect = path.boundingRect().united(m_textRect);
}

QTCOMMERCIALCHART_END_NAMESPACE
