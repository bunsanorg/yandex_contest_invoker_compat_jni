package yandex.contest.invoker.impl.process;

import yandex.contest.invoker.process.IProcessResourceLimits;

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
    public native long getTimeLimitMillis();

    @Override
    public native long getMemoryLimitBytes();

    @Override
    public native long getHardMemoryLimitBytes();

    @Override
    public native long getOutputLimitBytes();

    @Override
    public native long getNumberOfProcesses();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
