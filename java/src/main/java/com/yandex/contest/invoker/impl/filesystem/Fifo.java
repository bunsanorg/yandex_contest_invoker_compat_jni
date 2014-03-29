package com.yandex.contest.invoker.impl.filesystem;

import com.yandex.contest.invoker.filesystem.IFifo;

/**
 * User: sarum9in
 * Date: 10.09.12
 * Time: 11:59
 */
public class Fifo extends File implements IFifo {
    private Fifo() {}

    public static native void classInit();
}
