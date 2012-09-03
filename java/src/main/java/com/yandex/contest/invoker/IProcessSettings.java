package com.yandex.contest.invoker;

import com.yandex.contest.invoker.process.IProcessResourceLimits;
import com.yandex.contest.invoker.unistd.access.IId;

import java.util.List;

/**
 * User: sarum9in
 * Date: 07.08.12
 * Time: 15:28
 */
public interface IProcessSettings {
    String getExecutable();
    List<String> getArguments();

    /**
     * @return null if no redirection is needed.
     */
    String getStdinRedirection();

    /**
     * @return null if no redirection is needed.
     */
    String getStdoutRedirection();

    /**
     * @return null if no redirection is needed.
     */
    String getStderrRedirection();

    /**
     * @return null if should not be changed
     */
    IProcessResourceLimits getResourceLimits();

    /**
     * @return null if should not be changed
     */
    IId getOwnerId();

    /**
     * @return null if should not be changed
     */
    String getCurrentPath();

    IProcess createProcess(IProcessGroup processGroup);
}
