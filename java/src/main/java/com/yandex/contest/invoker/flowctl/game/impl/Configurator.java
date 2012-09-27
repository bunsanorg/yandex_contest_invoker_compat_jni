package com.yandex.contest.invoker.flowctl.game.impl;

import com.yandex.contest.invoker.flowctl.game.IConfig;

/**
 * User: sarum9in
 * Date: 26.09.12
 * Time: 19:51
 */
public class Configurator {
    public static native void configure(IConfig config);

    public static native void configure(IConfig config,
                                        String brokerConfig,
                                        String killerConfig);

    public static native void classInit();
}
