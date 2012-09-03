package com.yandex.contest.invoker.impl.process_group;

import com.yandex.contest.invoker.process_group.*;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:55
 */
public class ProcessGroupResult implements IProcessGroupResult {
    private ProcessGroupResult() {}

    @Override
    public native CompletionStatus getCompletionStatus();

    @Override
    public native IProcessGroupResourceUsage getResourceUsage();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
