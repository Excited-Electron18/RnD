#ifndef MYTIMER_H
#define MYTIMER_H

#include <QtCore>


class Mytimer : public QObject
{
    Q_OBJECT

public:
    Mytimer();
    QTimer *timer;
};

#endif // MYTIMER_H
