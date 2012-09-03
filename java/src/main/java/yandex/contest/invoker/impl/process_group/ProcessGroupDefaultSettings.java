package yandex.contest.invoker.impl.process_group;

import yandex.contest.invoker.process.IProcessDefaultSettings;
import yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;
import yandex.contest.invoker.process_group.IProcessGroupResourceLimits;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 16:37
 */
public class ProcessGroupDefaultSettings implements IProcessGroupDefaultSettings {
    private ProcessGroupDefaultSettings() {}

    public ProcessGroupDefaultSettings(IProcessGroupDefaultSettings processGroupDefaultSettings) {
        create(processGroupDefaultSettings);
    }

    private native void create(IProcessGroupDefaultSettings processGroupDefaultSettings);

    @Override
    public native IProcessGroupResourceLimits getResourceLimits();

    @Override
    public native IProcessDefaultSettings getProcessDefaultSettings();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
