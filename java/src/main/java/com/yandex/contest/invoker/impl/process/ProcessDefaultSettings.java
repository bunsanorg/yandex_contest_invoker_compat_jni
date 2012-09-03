package yandex.contest.invoker.impl.process;

import yandex.contest.invoker.INonPipeStream;
import yandex.contest.invoker.process.IProcessDefaultSettings;
import yandex.contest.invoker.process.IProcessResourceLimits;
import yandex.contest.invoker.unistd.access.IId;

import java.util.Map;

/**
 * User: sarum9in
 * Date: 07.08.12
 * Time: 20:32
 */
public class ProcessDefaultSettings implements IProcessDefaultSettings {
    private ProcessDefaultSettings() {}

    public ProcessDefaultSettings(IProcessDefaultSettings processDefaultSettings) {
        create(processDefaultSettings);
    }

    private native void create(IProcessDefaultSettings processDefaultSettings);

    @Override
    public native IProcessResourceLimits getResourceLimits();

    @Override
    public native Map<String, String> getEnvironment();

    @Override
    public native String getCurrentPath();

    @Override
    public native IId getOwnerId();

    @Override
    public native Map<Integer, INonPipeStream> getDescriptors();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
