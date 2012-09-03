package yandex.contest.invoker;

import yandex.contest.invoker.filesystem.IFilesystemConfig;
import yandex.contest.invoker.lxc.ILXCConfig;
import yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:27
 */
public interface IContainerConfig {
    String getContainersDir();
    ILXCConfig getLXCConfig();
    IProcessGroupDefaultSettings getProcessGroupDefaultSettings();
    IControlProcessConfig getControlProcessConfig();
    IFilesystemConfig getFilesystemConfig();
}
