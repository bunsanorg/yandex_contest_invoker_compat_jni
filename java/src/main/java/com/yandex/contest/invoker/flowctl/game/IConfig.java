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

    /**
     * Location of killer's log.
     */
    String getKillerLog();

    /**
     * Location of judge's log.
     */
    String getJudgeLog();

    /**
     * Location of broker's log.
     */
    String getBrokerLog();

    /**
     * Tokenizer library,
     * e.g. "yandex_contest_invoker_flowctl_game_tokenizer_split_char",
     * "/libtokenizer.so".
     */
    String getTokenizer();

    /**
     * Default resource limits for iteration.
     */
    IResourceLimits getDefaultResourceLimits();

    /**
     * Default tokenizer's argument for iteration.
     */
    String getDefaultTokenizerArgument();
}
