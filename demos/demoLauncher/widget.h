#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QProcess;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void runApp();

private:
    QProcess *m_demoApp;
};

#endif // WIDGET_H
