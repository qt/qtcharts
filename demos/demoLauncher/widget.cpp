#include "widget.h"
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QApplication>
#include <QProcess>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_demoApp(0)
{
    QList<QFileInfo> appList;
    QDir appFolder = QDir(BINPATH);
    appList = appFolder.entryInfoList(QDir::Files);

    for (int k = appList.count() - 1; k >= 0; k--) {
        QString name = appList[k].fileName();
        if (name.endsWith("exp")
                || name.endsWith("dll")
                || name.endsWith("lib")
                || name.startsWith("tst_")
                || name.startsWith("demoLauncher"))
            appList.removeAt(k);
    }

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
    if (m_demoApp)
        m_demoApp->close();
}

void Widget::runApp()
{
    QString name = qobject_cast<QPushButton *>(sender())->text();
    QString program = QApplication::applicationDirPath() + QDir::separator() + name;

    m_demoApp = new QProcess(this);
    m_demoApp->start(program);
}
