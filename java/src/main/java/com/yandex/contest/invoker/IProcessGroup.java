package com.yandex.contest.invoker;

import com.yandex.contest.invoker.process.IProcessDefaultSettings;
import com.yandex.contest.invoker.process_group.IProcessGroupResourceLimits;
import com.yandex.contest.invoker.process_group.IProcessGroupResult;

/**
 * User: sarum9in
 * Date: 03.07.12
 * Time: 19:31
 */
public interface IProcessGroup {
    /**
     * Start all processes, associated with process group.
     * It is not possible to start multiple process groups,
     * associated with the same container.
     */
    void start() throws InvokerException;

    /**
     * Stop all processes, started by process group.
     *
     * This function will kill all associated processes and controlling process.
     * All CompletionStatus fields will be set STOPPED.
     */
    void stop() throws InvokerException;

    /**
     * TODO: Do we really need this function?
     * TODO: It works like "start(); return waitFor();".
     * @see IProcessGroup#start()
     * @see IProcessGroup#waitFor()
     */
    IProcessGroupResult synchronizedCall() throws InvokerException;

    /**
     * Check if process group has terminated.
     * Set process group result if terminated.
     * @return Process group result if terminated,
     *         null otherwise.
     */
    IProcessGroupResult poll() throws InvokerException;

    /**
     * Wait for process group termination.
     * Set process group result.
     * @return Process group result.
     */
    IProcessGroupResult waitFor() throws InvokerException;

    /**
     * @return Process group result previously set by poll() or waitFor().
     * @throws IllegalStateException if process group result was not set.
     */
    IProcessGroupResult getResult();

    /**
     * Prepare new process.
     *
     * @throws IllegalStateException if process group has already started.
     * @see IProcessGroup#start()
     */
    IProcess createProcess(String executable);

    /**
     * Create new pipe, associated with ProcessGroup.
     *
     * @throws IllegalStateException if process group has already started.
     */
    IPipe createPipe();

    IProcessGroupResourceLimits getResourceLimits();
    void setResourceLimits(IProcessGroupResourceLimits resourceLimits);

    IProcessDefaultSettings getProcessDefaultSettings();

    void setProcessDefaultSettings(IProcessDefaultSettings processDefaultSettings);
}
