package com.yandex.contest.invoker.impl.process;

import com.yandex.contest.invoker.process.IProcessResourceLimits;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 16:40
 */
public class ProcessResourceLimits implements IProcessResourceLimits {
    private ProcessResourceLimits() {}

    public ProcessResourceLimits(IProcessResourceLimits processResourceLimits) {
        create(processResourceLimits);
    }

    private native void create(IProcessResourceLimits processResourceLimits);

    @Override
    public native long getTimeLimitNanos();

    @Override
    public native long getUserTimeLimitMillis();

    @Override
    public native long getSystemTimeLimitMillis();

    @Override
    public native long getMemoryLimitBytes();

    @Override
    public native long getOutputLimitBytes();

    @Override
    public native long getNumberOfProcesses();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
