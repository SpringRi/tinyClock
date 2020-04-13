#ifndef DURATION_H
#define DURATION_H

#include <QObject>
#include <QDateTime>

/*
 * Duration 类用于记录一个时间段的时间信息，起始时间，终止时间和持续时长
 */

class Duration
{
public:
    Duration();

    // 起始时间
    QDateTime from;
    // 终止时间
    QDateTime to;
    // 时长（以分钟计）
    quint64 duration_minutes;

signals:

};

#endif // DURATION_H
