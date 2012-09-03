package com.yandex.contest.invoker.impl.process;

import com.yandex.contest.invoker.Signal;
import com.yandex.contest.invoker.process.*;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:55
 */
public class ProcessResult implements IProcessResult {
    private ProcessResult() {}

    @Override
    public native CompletionStatus getCompletionStatus();

    @Override
    public native IProcessResourceUsage getResourceUsage();

    @Override
    public native Integer getExitStatus();

    @Override
    public native Signal getTermSig();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
