#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDir>
#include <QMap>

class QProcess;
class QMouseEvent;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent * event);

public slots:
    void runApp();

private:
    QDir m_appFolder;
    QProcess *m_demoApp;
    QMap<QWidget*, QString> m_map;
};

#endif // WIDGET_H
