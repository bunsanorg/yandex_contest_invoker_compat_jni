package com.yandex.contest.invoker.impl.filesystem;

import com.yandex.contest.invoker.filesystem.IDevice;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 21:37
 */
public class Device extends File implements IDevice {
    private Device() {}

    @Override
    public native Type getType();

    @Override
    public native int getMajor();

    @Override
    public native int getMinor();

    public static native void classInit();
}
