package com.yandex.contest.invoker.process_group;

import com.yandex.contest.invoker.process.IProcessDefaultSettings;

/**
 * User: sarum9in
 * Date: 13.08.12
 * Time: 20:47
 */
public interface IProcessGroupDefaultSettings {
    IProcessGroupResourceLimits getResourceLimits();
    IProcessDefaultSettings getProcessDefaultSettings();
}
