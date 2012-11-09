#include "widget.h"
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QApplication>
#include <QProcess>
#include <QDebug>
#include <QLabel>
#include <QMouseEvent>
#include "graphicsbutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_demoApp(0)
{
    setMinimumSize(200, 200);
    // Create a list of executables
    QList<QFileInfo> appList;
    m_appFolder = QDir(QApplication::applicationDirPath());

    QStringList filter;
    filter << "audio";
    filter << "callout";
    filter << "chartthemes";
    filter << "nesteddonuts";
    filter << "zoomlinechart";
    filter << "stackedbarchartdrilldown";
    filter << "piechartcustomization";
    filter << "barmodelmapper";
    m_appFolder.setNameFilters(filter);
#ifdef Q_OS_MAC
    // The executable is inside an application bundle (a folder) on OSX
    m_appFolder.cdUp();
    m_appFolder.cdUp();
    m_appFolder.cdUp();
#endif

    QDir imageFolder = m_appFolder;
    imageFolder.cdUp();
    imageFolder.cdUp();

    int width = 300;

    // Create push buttons for starting the executables
    QGridLayout* demosLayout = new QGridLayout;

    GraphicsButton *button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/demos_audio.png", m_appFolder, "audio", this);
    demosLayout->addWidget(button, 0, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/examples_callout.png", m_appFolder, "callout", this);
    demosLayout->addWidget(button, 0, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/demo_chartthemes_blue_cerulean.png", m_appFolder, "chartthemes", this);
    demosLayout->addWidget(button, 0, 2);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/demos_nesteddonuts.png", m_appFolder, "nesteddonuts", this);
    demosLayout->addWidget(button, 1, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/examples_zoomlinechart1.png", m_appFolder, "zoomlinechart", this);
    demosLayout->addWidget(button, 1, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/examples_stackedbarchartdrilldown1.png", m_appFolder, "stackedbarchartdrilldown", this);
    demosLayout->addWidget(button, 1, 2);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/piechart_customization.png", m_appFolder, "piechartcustomization", this);
    demosLayout->addWidget(button, 2, 0);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/examples_datetimeaxis.png", m_appFolder, "datetimeaxis", this);
    demosLayout->addWidget(button, 2, 1);

    button = new GraphicsButton(imageFolder.absolutePath() + "/doc/images/examples_donutbreakdown.png", m_appFolder, "donutbreakdown", this);
    demosLayout->addWidget(button, 2, 2);

    setLayout(demosLayout);
}

Widget::~Widget()
{
    QList<QObject *> children = this->children();
    for (int i = 0; i < children.count(); i++) {
        QProcess *app = qobject_cast<QProcess *>(children.at(i));
        if (app)
            app->close();
    }
}

void Widget::runApp()
{
    QString name = qobject_cast<QPushButton *>(sender())->text();
    QString program = m_appFolder.absolutePath() + QDir::separator() + name;
    m_demoApp = new QProcess(this);
    m_demoApp->start(program);
}

void Widget::mousePressEvent(QMouseEvent * event)
{
    for (int i = 0; i < layout()->count(); i++) {
        QWidget *pic = layout()->itemAt(i)->widget();
        if (pic && pic->rect().contains(pic->mapFromParent(event->pos()))) {
            QString value = m_map.value(pic);
            QString program = m_appFolder.absolutePath() + QDir::separator() + value;
            m_demoApp = new QProcess(this);
            m_demoApp->start(program);
            event->accept();
            return;
        }
    }
}
