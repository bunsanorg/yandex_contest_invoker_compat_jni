package yandex.contest.invoker;

import yandex.contest.invoker.process.IProcessResourceLimits;
import yandex.contest.invoker.process.IProcessResult;

import java.util.List;
import java.util.Map;

/**
 * User: sarum9in
 * Date: 03.07.12
 * Time: 19:34
 */
public interface IProcess {
    String getExecutable();

    /**
     * ProcessGroup is running while at least
     * on of processes marked with that flag
     * is running.
     */
    boolean groupWaitsForTermination();

    /**
     * Default is true.
     *
     * @see IProcess#groupWaitsForTermination()
     */
    void setGroupWaitsForTermination(boolean groupWaitsForTermination);

    /**
     * Default is true.
     *
     * Process group will terminate
     * if one of processes marked with this flag
     * has crashed (completion status is not OK).
     */
    boolean terminateGroupOnCrash();

    /**
     * @see IProcess#terminateGroupOnCrash()
     */
    void setTerminateGroupOnCrash(boolean terminateGroupOnCrash);

    List<String> getArguments();
    void setArguments(List<String> arguments);

    String getCurrentPath();
    void setCurrentPath(String currentPath);

    Map<String, String> getEnvironment();
    void setEnvironment(Map<String, String> environment);

    IProcessResourceLimits getResourceLimits();
    void setResourceLimits(IProcessResourceLimits resourceLimits);

    yandex.contest.invoker.unistd.access.IId getOwnerId();
    void setOwnerId(yandex.contest.invoker.unistd.access.IId ownerId);

    /**
     * @return Process result previously set by associated process group.
     * @throws IllegalStateException if associated process group has not set result.
     */
    IProcessResult getResult() throws IllegalStateException;

    /**
     * Assign descriptor to stream.
     */
    void setStream(int descriptor, IStream stream);

    /**
     * Get assigned stream.
     *
     * @throws IllegalArgumentException if no assigned stream exists.
     */
    IStream getStream(int descriptor);

    /**
     * Close descriptor.
     */
    void closeStream(int descriptor);

    /**
     * @return If descriptor has assigned stream.
     */
    boolean hasStream(int descriptor);
}
