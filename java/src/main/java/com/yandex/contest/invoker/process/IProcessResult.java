package com.yandex.contest.invoker.process;

import com.yandex.contest.invoker.Signal;

/**
 * User: sarum9in
 * Date: 04.07.12
 * Time: 12:20
 */
public interface IProcessResult {
    // TODO: enum values documentation
    enum CompletionStatus {
        OK,
        ABNORMAL_EXIT,
        TERMINATED_BY_SYSTEM,
        MEMORY_LIMIT_EXCEEDED,
        TIME_LIMIT_EXCEEDED,
        USER_TIME_LIMIT_EXCEEDED,
        SYSTEM_TIME_LIMIT_EXCEEDED,
        OUTPUT_LIMIT_EXCEEDED,
        START_FAILED,
        STOPPED
    }

    CompletionStatus getCompletionStatus();

    IProcessResourceUsage getResourceUsage();

    /**
     * See wait(3), WEXITSTATUS, WIFEXITED.
     *
     * @return If process terminated normally, exit status is returned,
     *         null otherwise.
     */
    Integer getExitStatus();

    /**
     * See wait(3), WTERMSIG, WIFSIGNALED.
     *
     * @return If child process was terminated due to the receipt of a signal
     *         that was not caught, the signal is returned,
     *         null otherwise.
     */
    Signal getTermSig();
}
