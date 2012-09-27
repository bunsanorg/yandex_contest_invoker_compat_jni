package com.yandex.contest.invoker.flowctl.game;

import com.yandex.contest.invoker.impl.Container;
import com.yandex.contest.invoker.impl.ProcessGroup;
import com.yandex.contest.invoker.impl.Process;

import java.util.List;

/**
 * User: sarum9in
 * Date: 26.09.12
 * Time: 19:47
 */
public interface IConfig {
    Container getContainer();
    ProcessGroup getProcessGroup();
    Process getBroker();
    Process getKiller();
    Process getJudge();
    List<Process> getSolutions();
    Protocol getProtocol();
    String getKillerLog();
    String getJudgeLog();
    String getBrokerLog();
    String getTokenizer();
    IResourceLimits getDefaultResourceLimits();
    String getDefaultTokenizerArgument();
}
