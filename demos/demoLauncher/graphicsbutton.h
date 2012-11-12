#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QWidget>
#include <QDir>

class QProcess;

class GraphicsButton : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsButton(const QString& path, QDir appFolder, const QString& app, QWidget *parent = 0);
    ~GraphicsButton();
    
protected:
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *);

private:
    QPixmap m_pixmap;
    QString m_path;
    QDir m_appFolder;
    QString m_app;
    QProcess *m_demoApp;
};

#endif // GRAPHICSBUTTON_H
