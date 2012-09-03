package yandex.contest.invoker;

import yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;

/**
 * User: sarum9in
 * Date: 03.07.12
 * Time: 19:13
 */
public interface IContainer {

    /**
     * Destroy existing container.
     * Does nothing if container was already destroyed.
     */
    void destroy();

    /**
     * @return filesystem object, associated with container
     */
    IFilesystem getFilesystem();

    /**
     * @return new process group, associated with container
     */
    IProcessGroup createProcessGroup();

    IProcessGroupDefaultSettings getProcessGroupDefaultSettings();

    void setProcessGroupDefaultSettings(
            IProcessGroupDefaultSettings processGroupDefaultSettings);
}
