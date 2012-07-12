#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDonutGroup>

QTCOMMERCIALCHART_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void updateRotation();

private:
    QDonutGroup m_donutsGroup;
};

#endif // WIDGET_H
