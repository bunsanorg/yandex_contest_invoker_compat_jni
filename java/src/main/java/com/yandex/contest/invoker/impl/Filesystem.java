package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IFilesystem;
import com.yandex.contest.invoker.InvokerException;
import com.yandex.contest.invoker.unistd.IFileStatus;
import com.yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 05.08.12
 * Time: 6:50
 */
public class Filesystem implements IFilesystem {
    private Filesystem() {}

    @Override
    public native String containerRoot();

    @Override
    public native String keepInRoot(String path);

    @Override
    public native void push(String local, String remote, IId ownerId, int mode) throws InvokerException;

    @Override
    public native void pushLink(String local, String remote, IId ownerId, int mode) throws InvokerException;

    @Override
    public native IFileStatus getFileStatus(String remote) throws InvokerException;

    @Override
    public native void setOwnerId(String remote, IId ownerId) throws InvokerException;

    @Override
    public native void setMode(String remote, int mode) throws InvokerException;

    @Override
    public native void pull(String remote, String local) throws InvokerException;

    // we store reference here, no finalization is needed
    private long impl = 0;

    public static native void classInit();
}
