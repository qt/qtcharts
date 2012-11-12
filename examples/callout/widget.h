#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>

class QGraphicsScene;
class QGraphicsView;
class Callout;

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsScene *m_scene;
    QChart *m_chart;
    QGraphicsView *m_view;
    Callout *m_tooltip;
};

#endif // WIDGET_H
