#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include <QWidget>

class QGraphicsView;
class QGraphicsScene;
class QScatterSeries;

class QChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();
    void setType(/*TODO QChart::Type*/ int type);

signals:

public slots:

private:
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QScatterSeries *m_scatter;
};

#endif // QCHARTWIDGET_H
