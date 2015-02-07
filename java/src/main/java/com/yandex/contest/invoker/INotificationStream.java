package com.yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 07.02.15
 * Time: 22:23
 */
public interface INotificationStream {
    IStream getPipeEnd();
    NotificationStreamProtocol getProtocol();
}
