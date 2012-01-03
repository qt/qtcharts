#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QtCore/QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    #include <QWidget>
#else
    #include <QtWidgets/QWidget>
#endif

#if defined(CHARTWIDGET_LIBRARY)
#  define CHARTWIDGET_EXPORT Q_DECL_EXPORT
#else
#  define CHARTWIDGET_EXPORT Q_DECL_IMPORT
#endif

class ChartWidgetPrivate;

class CHARTWIDGET_EXPORT ChartWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();

    QColor color() const;
    void setColor(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *);

private:
    Q_DISABLE_COPY(ChartWidget)
    Q_DECLARE_PRIVATE(ChartWidget)
    ChartWidgetPrivate* d_ptr;
};

#endif
