#ifndef QCHARTVIEW_H
#define QCHARTVIEW_H

#include <QGraphicsView>
#include "qbarchart.h"

class QChartView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QChartView(QGraphicsScene *scene, QWidget *parent = 0);

signals:

public slots:

protected:
    void resizeEvent(QResizeEvent *event);

private:

    QBarChart *mChart;
};

#endif // QCHARTVIEW_H
