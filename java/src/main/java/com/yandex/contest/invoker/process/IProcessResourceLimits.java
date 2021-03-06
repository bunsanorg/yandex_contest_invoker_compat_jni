package com.yandex.contest.invoker.process;

/**
 * User: sarum9in
 * Date: 05.07.12
 * Time: 09:55
 */
public interface IProcessResourceLimits {
    long getTimeLimitNanos();
    long getUserTimeLimitMillis();
    long getSystemTimeLimitMillis();
    long getMemoryLimitBytes();
    long getOutputLimitBytes();
    long getNumberOfProcesses();
}
