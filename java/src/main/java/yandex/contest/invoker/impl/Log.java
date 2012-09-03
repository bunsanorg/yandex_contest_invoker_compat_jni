package yandex.contest.invoker.impl;

import yandex.contest.invoker.ILog;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:55
 */
public class Log {
    public static native void registerInstance(ILog log);

    public static native void classInit();
}
