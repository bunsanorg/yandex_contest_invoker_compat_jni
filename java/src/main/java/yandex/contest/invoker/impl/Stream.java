package yandex.contest.invoker.impl;

import yandex.contest.invoker.IStream;

/**
 * User: sarum9in
 * Date: 05.08.12
 * Time: 6:51
 */
public class Stream implements IStream {
    private Stream() {}

    @Override
    public native AccessMode getAccessMode();

    @Override
    public native String toString();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
