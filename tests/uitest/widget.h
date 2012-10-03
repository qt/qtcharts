#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QChartGlobal>

class QVBoxLayout;

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QValueAxis;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void handleClick();

private:
    QVBoxLayout* createButtons();

    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
};

#endif // WIDGET_H
