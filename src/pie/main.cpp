#include <QtGui/QApplication>
#include <QtGui>
#include <QDebug>

class Slice : public QGraphicsItem
{
public:
    Slice(const QColor& color, qreal startAngle, qreal span)
        :m_color(color),
        m_startAngle(startAngle),
        m_span(span)
    {
        setAcceptHoverEvents(true);
    }

    ~Slice()
    {

    }

    virtual QRectF boundingRect() const
    {
        return parentItem()->boundingRect();
    }

    QPainterPath shape() const
    {
        qreal angle = (-m_startAngle) + (90);
        qreal span = -m_span;

        QPainterPath path;
        path.moveTo(boundingRect().center());
        path.arcTo(boundingRect(), angle, span);

        // TODO: draw the shape so that it might have a hole in the center
        // - Sin & Cos will be needed to find inner/outer arc endpoints

        // dx, dy are offsets from the center
        //qreal l = boundingRect().height();
        //qreal dx = qSin(angle*(M_PI/180)) * l;
        //qreal dy = qCos(angle*(M_PI/180)) * l;

        // TODO: exploded slice?

        return path;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        // Setup painter
        painter->setBrush(m_color);
        QPen pen;
        //pen.setColor(m_color.darker());
        pen.setColor(Qt::gray);
        pen.setWidth(1);
        painter->setPen(pen);

        // From Qt docs:
        // The startAngle and spanAngle must be specified in 1/16th of a degree, i.e. a full circle equals 5760 (16 * 360).
        // Positive values for the angles mean counter-clockwise while negative values mean the clockwise direction.
        // Zero degrees is at the 3 o'clock position.
        //
        // For sake of simplicity convert this so that zero degrees is at 12 o'clock and full circle is 360.
        //qreal angle = (-m_startAngle*16) + (90*16);
        //qreal span = -m_span*16;
        //painter->drawPie(boundingRect(), angle, span);

        painter->drawPath(shape());
    }

    virtual void hoverEnterEvent( QGraphicsSceneHoverEvent * event)
    {
        QGraphicsItem::hoverEnterEvent(event);
        qDebug() << "hover" << m_color << m_startAngle << m_span;
    }

private:
    QColor m_color;
    qreal m_startAngle;
    qreal m_span;
};

class PieChart : public QGraphicsItem
{
public:
    PieChart()
    {
        qsrand(QTime::currentTime().msec());
    }

    ~PieChart()
    {

    }

    QColor randomColor()
    {
        QColor c;
        c.setRed(qrand() % 255);
        c.setGreen(qrand() % 255);
        c.setBlue(qrand() % 255);
        return c;
    }

    void setData(QList<int> data)
    {
        qreal fullPie = 360;

        qreal total = 0;
        foreach (qreal value, data)
            total += value;

        qreal angle = 0;
        foreach (qreal value, data) {
            qreal span = value / total * fullPie;
            Slice *slice = new Slice(randomColor(), angle, span);
            slice->setParentItem(this);
            m_slices.append(slice);
            angle += span;
        }
    }

    virtual QRectF boundingRect() const
    {
        return QRectF(-200, -200, 200, 200);
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        //painter->setBrush(Qt::red);
        //painter->drawRect(boundingRect());
    }

private:
    QList<Slice*> m_slices;
    QSizeF m_size;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene;

    PieChart *pieChart = new PieChart();
    scene.addItem(pieChart);

    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.resize(400, 300);
    view.show();

    QList<int> data;
    data << 1;
    data << 2;
    data << 3;
    data << 20;
    data << 2;
    data << 3;
    data << 10;
    data << 2;
    data << 1;
    data << 5;
    pieChart->setData(data);

    return a.exec();
}
