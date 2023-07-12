#include "mytimer.h"

#include <QtCore>
#include <QtDebug>

Mytimer::Mytimer()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    timer->start(0); // Interval 0 means to refresh as fast as possible
}
