package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IFdAlias;
import com.yandex.contest.invoker.jimpl.AbstractFdAlias;

/**
 * User: sarum9in
 * Date: 30.08.12
 * Time: 20:22
 */
public class FdAlias extends AbstractFdAlias implements IFdAlias {
    private FdAlias() {}

    @Override
    public native int getFd();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
