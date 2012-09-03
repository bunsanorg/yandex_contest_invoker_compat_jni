package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IControlProcessConfig;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 20:00
 */
public class ControlProcessConfig implements IControlProcessConfig {
    private ControlProcessConfig() {}

    public ControlProcessConfig(IControlProcessConfig controlProcessConfig) {
        create(controlProcessConfig);
    }

    private native void create(IControlProcessConfig controlProcessConfig);

    @Override
    public native String getExecutable();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
