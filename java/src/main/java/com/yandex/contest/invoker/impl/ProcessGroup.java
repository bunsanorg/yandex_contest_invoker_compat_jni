package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.INotificationStream;
import com.yandex.contest.invoker.InvokerException;
import com.yandex.contest.invoker.IPipe;
import com.yandex.contest.invoker.IProcess;
import com.yandex.contest.invoker.IProcessGroup;
import com.yandex.contest.invoker.IStream;
import com.yandex.contest.invoker.NotificationStreamProtocol;
import com.yandex.contest.invoker.process.IProcessDefaultSettings;
import com.yandex.contest.invoker.process_group.IProcessGroupResourceLimits;
import com.yandex.contest.invoker.process_group.IProcessGroupResult;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:54
 */
public class ProcessGroup implements IProcessGroup, IHandle {
    private ProcessGroup() {}

    @Override
    public native void destroy();

    @Override
    public native boolean exists();

    @Override
    public native void start() throws InvokerException;

    @Override
    public native void stop() throws InvokerException;

    @Override
    public native IProcessGroupResult synchronizedCall() throws InvokerException;

    @Override
    public native IProcessGroupResult poll() throws InvokerException;

    @Override
    public native IProcessGroupResult waitFor() throws InvokerException;

    @Override
    public native IProcessGroupResult getResult();

    @Override
    public native IProcess createProcess(String executable);

    @Override
    public native IPipe createPipe();

    @Override
    public native IProcessGroupResourceLimits getResourceLimits();

    @Override
    public native void setResourceLimits(IProcessGroupResourceLimits resourceLimits);

    @Override
    public native INotificationStream getNotifier(long notifierId);

    @Override
    public native void setNotifier(long notifierId,
                                   INotificationStream notificationStream);

    @Override
    public native void setNotifier(long notifierId,
                                   IStream pipeEnd,
                                   NotificationStreamProtocol protocol);

    @Override
    public native void setNotifier(long notifierId, IStream pipeEnd);

    @Override
    public native long addNotifier(INotificationStream notificationStream);

    @Override
    public native long addNotifier(IStream pipeEnd,
                                   NotificationStreamProtocol protocol);

    @Override
    public native long addNotifier(IStream pipeEnd);

    @Override
    public native IStream addNotifier(NotificationStreamProtocol protocol);

    @Override
    public native IStream addNotifier();

    @Override
    public native IProcessDefaultSettings getProcessDefaultSettings();

    @Override
    public native void setProcessDefaultSettings(
            IProcessDefaultSettings processDefaultSettings);

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
