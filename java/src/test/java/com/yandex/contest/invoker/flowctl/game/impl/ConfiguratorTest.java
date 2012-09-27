package com.yandex.contest.invoker.flowctl.game.impl;

import com.yandex.contest.invoker.flowctl.game.IConfig;
import com.yandex.contest.invoker.flowctl.game.IResourceLimits;
import com.yandex.contest.invoker.flowctl.game.Protocol;
import com.yandex.contest.invoker.impl.*;
import com.yandex.contest.invoker.impl.Process;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

/**
 * User: sarum9in
 * Date: 27.09.12
 * Time: 18:15
 */
public class ConfiguratorTest extends ProcessGroupFixture {
    private Process broker = null, killer = null, judge = null;
    private List<Process> solutions = null;

    @Before
    public void setUp() throws Exception {
        super.setUp();
        broker = (Process)getProcessGroup().createProcess(
                "yandex_contest_invoker_flowctl_game_broker");
        killer = (Process)getProcessGroup().createProcess(
                "yandex_contest_invoker_flowctl_game_killer");
        judge = (Process)getProcessGroup().createProcess("true");
        solutions = Arrays.asList((Process)getProcessGroup().createProcess("true"));
    }

    @After
    public void tearDown() {
        super.tearDown();
    }

    public IConfig getConfig() {
        final ConfiguratorTest cfg = this;
        return new IConfig() {
            @Override
            public Container getContainer() {
                return (Container)cfg.getContainer();
            }

            @Override
            public ProcessGroup getProcessGroup() {
                return (ProcessGroup)cfg.getProcessGroup();
            }

            @Override
            public Process getBroker() {
                return cfg.broker;
            }

            @Override
            public Process getKiller() {
                return cfg.killer;
            }

            @Override
            public Process getJudge() {
                return cfg.judge;
            }

            @Override
            public List<Process> getSolutions() {
                return cfg.solutions;
            }

            @Override
            public Protocol getProtocol() {
                return Protocol.TEXT;
            }

            @Override
            public String getKillerLog() {
                return "/killerLog";
            }

            @Override
            public String getJudgeLog() {
                return "/judgeLog";
            }

            @Override
            public String getBrokerLog() {
                return "/brokerLog";
            }

            @Override
            public String getTokenizer() {
                return "yandex_contest_invoker_flowctl_game_tokenizer_split_char";
            }

            @Override
            public IResourceLimits getDefaultResourceLimits() {
                return new IResourceLimits() {
                    @Override
                    public long getRealTimeLimitsMillis() {
                        return 60 * 60 * 1000;
                    }

                    @Override
                    public long getUserTimeLimitMillis() {
                        return 60 * 60 * 1000;
                    }
                };
            }

            @Override
            public String getDefaultTokenizerArgument() {
                return "\n";
            }
        };
    }

    @Test
    public void test1() throws Exception {
        Configurator.configure(getConfig());
        runOK();
    }

    @Test
    public void test3() throws Exception {
        Configurator.configure(getConfig(), "/brokerConfig", "/killerConfig");
        runOK();
    }
}
