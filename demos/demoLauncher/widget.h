#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>

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
    QDir m_appFolder;
    QProcess *m_demoApp;
};

#endif // WIDGET_H
