package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.*;
import com.yandex.contest.invoker.lxc.ILxcConfig;
import com.yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;

/**
 * User: sarum9in
 * Date: 05.07.12
 * Time: 10:27
 */
public class Container implements IContainer, IHandle {
    public Container() throws InvokerException {
        create();
        createFilesystem();
    }

    public Container(IContainerConfig containerConfig) throws InvokerException {
        create(containerConfig);
        createFilesystem();
    }

    public Container(ILxcConfig lxcConfig) throws InvokerException {
        create(lxcConfig);
        createFilesystem();
    }

    public Container(IContainerConfig containerConfig,
                     ILxcConfig lxcConfig) throws InvokerException {
        create(containerConfig, lxcConfig);
        createFilesystem();
    }

    /**
     * Create container. Must be called from constructor.
     * Does nothing if container was already created.
     */
    private native void create() throws InvokerException;

    private native void create(IContainerConfig containerConfig) throws InvokerException;

    private native void create(ILxcConfig lxcConfig) throws InvokerException;

    private native void create(IContainerConfig containerConfig,
                               ILxcConfig lxcConfig) throws InvokerException;

    private native void createFilesystem();

    @Override
    public native void destroy();

    @Override
    public native boolean exists();

    @Override
    public native IProcessGroup createProcessGroup();

    private Filesystem filesystem;

    @Override
    public IFilesystem getFilesystem() {
        return filesystem;
    }

    @Override
    public native IProcessGroupDefaultSettings getProcessGroupDefaultSettings();

    @Override
    public native void setProcessGroupDefaultSettings(
            IProcessGroupDefaultSettings settings);

    @Override
    protected native void finalize();

    private long impl;

    public static native void classInit();
}
