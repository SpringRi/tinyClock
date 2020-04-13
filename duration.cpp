#include "duration.h"

Duration::Duration()
{
    // 初始化

    // 初始化一个空的 datetime(i.e. null date and null time)
    // 可用 isValid() 函数检测
    from = QDateTime();
    to = QDateTime();

    // 时长初始化为0
    duration_minutes = 0;
}
