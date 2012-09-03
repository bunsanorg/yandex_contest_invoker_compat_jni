package com.yandex.contest.invoker.impl.process_group;

import com.yandex.contest.invoker.process_group.IProcessGroupResourceLimits;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 16:37
 */
public class ProcessGroupResourceLimits implements IProcessGroupResourceLimits {
    private ProcessGroupResourceLimits() {}

    public ProcessGroupResourceLimits(IProcessGroupResourceLimits processGroupResourceLimits) {
        create(processGroupResourceLimits);
    }

    private native void create(IProcessGroupResourceLimits processGroupResourceLimits);

    @Override
    public native long getRealTimeLimitMillis();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
