#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPieSeries>

class QTimer;

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void updateRotation();
    void explodeSlice(bool exploded);

private:
    QList<QPieSeries *> m_donuts;
    QTimer *updateTimer;
};

#endif // WIDGET_H
