#include <qpieslice.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class CustomSlice : public QPieSlice
{
    Q_OBJECT

public:
    CustomSlice(qreal value, QObject* parent = 0);

public Q_SLOTS:
    void updateLabel();
    void toggleExploded();
};
