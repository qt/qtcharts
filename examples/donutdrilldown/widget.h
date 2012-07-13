#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPieSeries>

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void updatedStartAngle();
    void updatedAngleSpan();
    void updateRotation();
    void highlight();

private:
    QPieSeries *mainData;
    QList<QPieSeries *> detailedData;
    int detailIndex;
    int sliceIndex;
};

#endif // WIDGET_H
