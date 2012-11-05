#include "widget.h"
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QApplication>
#include <QProcess>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_demoApp(0)
{
    QList<QFileInfo> appList;

    QDir appFolder(QApplication::applicationDirPath());
    QStringList nameFilters;
    nameFilters << "[^t][^s][^t]*";
    appFolder.setNameFilters(nameFilters);
    appList = appFolder.entryInfoList(QDir::Files);

    QGridLayout* demosLayout = new QGridLayout;
    for( int i = 0; i < appList.count(); i++) {
        QPushButton *button = new QPushButton(appList[i].fileName());
        connect(button, SIGNAL(clicked()), this, SLOT (runApp()));
        demosLayout->addWidget(button, i%10, i/10);
    }
    setLayout(demosLayout);
}

Widget::~Widget()
{
    m_demoApp->close();
}

void Widget::runApp()
{
    QString name = qobject_cast<QPushButton *>(sender())->text();
    QString program = QApplication::applicationDirPath() + QDir::separator() + name;

    m_demoApp = new QProcess(this);
    m_demoApp->start(program);
}
