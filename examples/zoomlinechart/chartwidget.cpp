#include "chartwidget.h"
#include <QMouseEvent>

ChartWidget::ChartWidget(QWidget *parent)
    : QChartView(parent),
 m_rubberBand(QRubberBand::Rectangle,this)
{
}

void ChartWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton) return;

    int margin = 25;
    QRect rect(margin,margin,width()-2*margin,height()-2*margin);

    m_origin = event->pos();

    if (!rect.contains(m_origin)) return;

    m_rubberBand.setGeometry(QRect(m_origin, QSize()));
    m_rubberBand.show();

    event->accept();
}

void ChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_rubberBand.isVisible())
        m_rubberBand.setGeometry(QRect(m_origin, event->pos()).normalized());
}

void ChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if( event->button()==Qt::LeftButton && m_rubberBand.isVisible()) {
        m_rubberBand.hide();

        QRect rect = m_rubberBand.geometry();
        zoomIn(rect);
        event->accept();
    }

    if(event->button()==Qt::RightButton) {
        zoomOut();
    }
}


void ChartWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Left:
        scrollLeft();
        break;
    case Qt::Key_Right:
        scrollRight();
        break;
    case Qt::Key_Up:
        scrollUp();
        break;
    case Qt::Key_Down:
        scrollDown();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
