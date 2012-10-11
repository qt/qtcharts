#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChart>

class QGraphicsScene;
class QGraphicsView;

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void addCallout(QPointF point);

private:
    QGraphicsScene *m_scene;
    QChart *m_chart;
    QGraphicsView *m_view;
};

#endif // WIDGET_H
