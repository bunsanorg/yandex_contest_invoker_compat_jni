package com.yandex.contest.invoker.impl.lxc;

import com.yandex.contest.invoker.lxc.ILxcConfig;
import com.yandex.contest.invoker.lxc.IMountConfig;
import com.yandex.contest.invoker.lxc.IRootfsConfig;

import java.util.Map;
import java.util.Set;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 15:48
 */
public class LxcConfig implements ILxcConfig {
    private LxcConfig() {}

    public LxcConfig(ILxcConfig lxcConfig) {
        create(lxcConfig);
    }

    private native void create(ILxcConfig lxcConfig);

    @Override
    public native Arch arch();

    @Override
    public native String utsname();

    @Override
    public native String console();

    @Override
    public native Integer tty();

    @Override
    public native String devttydir();

    @Override
    public native IMountConfig mount();

    @Override
    public native IRootfsConfig rootfs();

    @Override
    public native String pivotdir();

    @Override
    public native Map<String, String> cgroup();

    @Override
    public native Set<String> cap_drop();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
