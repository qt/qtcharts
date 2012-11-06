#include "widget.h"
#include <QPushButton>
#include <QDir>
#include <QGridLayout>
#include <QApplication>
#include <QProcess>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_demoApp(0)
{
    // Create a list of executables
    QList<QFileInfo> appList;
    m_appFolder = QDir(QApplication::applicationDirPath());
#ifdef Q_WS_MAC
    // The executable is inside an application bundle (a folder) on OSX
    m_appFolder.cdUp();
    m_appFolder.cdUp();
    m_appFolder.cdUp();
    appList = m_appFolder.entryInfoList(QStringList("*.app"), QDir::Executable | QDir::Dirs | QDir::NoDotAndDotDot);
#elif defined(Q_WS_WIN)
    appList = m_appFolder.entryInfoList(QStringList("*.exe"), QDir::Executable | QDir::Files | QDir::NoDotAndDotDot);
#else
    appList = m_appFolder.entryInfoList(QDir::Executable | QDir::Files | QDir::NoDotAndDotDot);
#endif
    for (int k = appList.count() - 1; k >= 0; k--) {
        QString name = appList[k].fileName();
        if (name.startsWith("tst_") || name.startsWith("demoLauncher"))
            appList.removeAt(k);
    }

    // Create push buttons for starting the executables
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
    QString program = m_appFolder.absolutePath() + QDir::separator() + name;
    m_demoApp = new QProcess(this);
    m_demoApp->start(program);
}
