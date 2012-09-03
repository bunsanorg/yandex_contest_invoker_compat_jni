package yandex.contest.invoker.impl.lxc;

import yandex.contest.invoker.lxc.IMountConfig;
import yandex.contest.invoker.unistd.IMountEntry;

import java.util.List;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 15:49
 */
public class MountConfig implements IMountConfig {
    private MountConfig() {}

    public MountConfig(IMountConfig mountConfig) {
        create(mountConfig);
    }

    private native void create(IMountConfig mountConfig);

    @Override
    public native String fstab();

    @Override
    public native List<IMountEntry> entries();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
