package yandex.contest.invoker.impl;

import yandex.contest.invoker.IProcess;
import yandex.contest.invoker.IStream;
import yandex.contest.invoker.process.IProcessResourceLimits;
import yandex.contest.invoker.process.IProcessResult;
import yandex.contest.invoker.unistd.access.IId;

import java.util.List;
import java.util.Map;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:54
 */
public class Process implements IProcess, IHandle {
    private Process() {}

    @Override
    public native void destroy();

    @Override
    public native boolean exists();

    @Override
    public native String getExecutable();

    @Override
    public native boolean groupWaitsForTermination();

    @Override
    public native void setGroupWaitsForTermination(boolean groupWaitsForTermination);

    @Override
    public native boolean terminateGroupOnCrash();

    @Override
    public native void setTerminateGroupOnCrash(boolean terminateGroupOnCrash);

    @Override
    public native List<String> getArguments();

    @Override
    public native void setArguments(List<String> arguments);

    @Override
    public native String getCurrentPath();

    @Override
    public native void setCurrentPath(String currentPath);

    @Override
    public native Map<String, String> getEnvironment();

    @Override
    public native void setEnvironment(Map<String, String> environment);

    @Override
    public native IProcessResourceLimits getResourceLimits();

    @Override
    public native void setResourceLimits(IProcessResourceLimits resourceLimits);

    @Override
    public native IId getOwnerId();

    @Override
    public native void setOwnerId(IId ownerId);

    @Override
    public native IProcessResult getResult();

    @Override
    public native void setStream(int descriptor, IStream stream);

    @Override
    public native IStream getStream(int descriptor);

    @Override
    public native void closeStream(int descriptor);

    @Override
    public native boolean hasStream(int descriptor);

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
