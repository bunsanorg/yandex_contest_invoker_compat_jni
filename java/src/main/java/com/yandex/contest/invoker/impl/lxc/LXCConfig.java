package yandex.contest.invoker.impl.lxc;

import yandex.contest.invoker.lxc.ILXCConfig;
import yandex.contest.invoker.lxc.IMountConfig;

import java.util.Map;
import java.util.Set;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 15:48
 */
public class LXCConfig implements ILXCConfig {
    private LXCConfig() {}

    public LXCConfig(ILXCConfig lxcConfig) {
        create(lxcConfig);
    }

    private native void create(ILXCConfig lxcConfig);

    @Override
    public native Arch arch();

    @Override
    public native String utsname();

    @Override
    public native String console();

    @Override
    public native Integer tty();

    @Override
    public native IMountConfig mount();

    @Override
    public String rootfs() {
        return null;
    }

    @Override
    public native Map<String, String> cgroup();

    @Override
    public native Set<String> cap_drop();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
