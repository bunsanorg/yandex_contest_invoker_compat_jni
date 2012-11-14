package com.yandex.contest.invoker.impl.lxc;

import com.yandex.contest.invoker.lxc.IRootfsConfig;

/**
 * Created with IntelliJ IDEA.
 * User: sarum9in
 * Date: 14.11.12
 * Time: 20:57
 */
public class RootfsConfig implements IRootfsConfig {
    private RootfsConfig() {}

    public RootfsConfig(IRootfsConfig rootfsConfig) {
        create(rootfsConfig);
    }

    private native void create(IRootfsConfig rootfsConfig);

    @Override
    public native String fsname();

    @Override
    public native String mount();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
