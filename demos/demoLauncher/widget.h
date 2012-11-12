#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QDir m_appFolder;
};

#endif // WIDGET_H
