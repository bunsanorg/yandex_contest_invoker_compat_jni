package yandex.contest.invoker.impl;

import yandex.contest.invoker.IContainerConfig;
import yandex.contest.invoker.IControlProcessConfig;
import yandex.contest.invoker.filesystem.IFilesystemConfig;
import yandex.contest.invoker.lxc.ILXCConfig;
import yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 15:43
 */
public class ContainerConfig implements IContainerConfig {
    private ContainerConfig() {}

    public ContainerConfig(IContainerConfig containerConfig) {
        create(containerConfig);
    }

    private native void create(IContainerConfig containerConfig);

    @Override
    public native String getContainersDir();

    @Override
    public native ILXCConfig getLXCConfig();

    @Override
    public native IProcessGroupDefaultSettings getProcessGroupDefaultSettings();

    @Override
    public native IControlProcessConfig getControlProcessConfig();

    @Override
    public native IFilesystemConfig getFilesystemConfig();

    public static native ContainerConfig fromEnvironment();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
