package com.yandex.contest.invoker.unistd;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 13:43
 */
public interface IResourceUsage {
    long getTimeUsageMillis();
    long getMemoryUsageBytes();
}
