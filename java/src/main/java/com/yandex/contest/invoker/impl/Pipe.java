package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IPipe;
import com.yandex.contest.invoker.IStream;

/**
 * User: sarum9in
 * Date: 05.08.12
 * Time: 7:05
 */
public class Pipe implements IPipe {
    private Pipe() {}

    @Override
    public native IStream getInputStream();

    @Override
    public native IStream getOutputStream();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
