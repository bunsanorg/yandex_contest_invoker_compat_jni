package com.yandex.contest.invoker.impl.process;

import com.yandex.contest.invoker.process.IProcessResourceUsage;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 13:49
 */
public class ProcessResourceUsage implements IProcessResourceUsage {
    private ProcessResourceUsage() {}

    @Override
    public native long getTimeUsageNanos();

    @Override
    public native long getUserTimeUsageMillis();

    @Override
    public native long getSystemTimeUsageMillis();

    @Override
    public native long getMemoryUsageBytes();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
