package yandex.contest.invoker.impl.process_group;

import yandex.contest.invoker.process_group.IProcessGroupResourceUsage;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 14:23
 */
public class ProcessGroupResourceUsage implements IProcessGroupResourceUsage {
    private ProcessGroupResourceUsage() {}

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
