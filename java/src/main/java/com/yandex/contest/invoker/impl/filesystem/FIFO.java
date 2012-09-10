package com.yandex.contest.invoker.impl.filesystem;

import com.yandex.contest.invoker.filesystem.IFIFO;

/**
 * User: sarum9in
 * Date: 10.09.12
 * Time: 11:59
 */
public class FIFO extends File implements IFIFO {
    private FIFO() {}

    public static native void classInit();
}
