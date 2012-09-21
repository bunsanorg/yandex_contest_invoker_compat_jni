package com.yandex.contest.invoker.process;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 13:44
 */
public interface IProcessResourceUsage {
    long getTimeUsageNanos();
    long getUserTimeUsageMillis();
    long getSystemTimeUsageMillis();
    long getMemoryUsageBytes();
}
