package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.INotificationStream;
import com.yandex.contest.invoker.IStream;
import com.yandex.contest.invoker.NotificationStreamProtocol;

/**
 * User: sarum9in
 * Date: 07.02.15
 * Time: 22:27
 */
public class NotificationStream implements INotificationStream {
    private NotificationStream() {}

    private native void create(IStream pipeEnd, NotificationStreamProtocol protocol);

    public NotificationStream(IStream pipeEnd, NotificationStreamProtocol protocol) {
        create(pipeEnd, protocol);
    }

    @Override
    public native IStream getPipeEnd();

    @Override
    public native NotificationStreamProtocol getProtocol();

    @Override
    public native String toString();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
