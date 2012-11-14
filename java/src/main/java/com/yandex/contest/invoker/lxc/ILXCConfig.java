package com.yandex.contest.invoker.lxc;

import java.util.Set;
import java.util.Map;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:19
 */
public interface ILXCConfig {
    enum Arch {
        x86,
        i686,
        x86_64,
        amd64
    }

    Arch arch();

    /**
     * @return Hostname
     */
    String utsname();

    // TODO: network (seems to be useless for now)

    // TODO: pts (is not fully implemented by LXC, seems to be useless for now)

    /**
     * @return Path to a file where the console output will be written.
     */
    String console();

    /**
     * @return The number of tty available to the container.
     */
    Integer tty();

    /**
     * @return A directory under /dev under which to create the container console devices.
     */
    String devttydir();

    /**
     * @return Mount settings.
     */
    IMountConfig mount();

    /**
     * Is not used.
     * @return
     */
    IRootfsConfig rootfs();

    /**
     * @return here to pivot the original root file system under lxc.rootfs,
     * specified relatively to that.
     */
    String pivotdir();

    /**
     * @return The control group values to be set.
     * Example (map as json): {"cpuset.cpus": "0", "memory.memsw.limit_in_bytes": "1G"}
     */
    Map<String, String> cgroup();

    /**
     * @return List of capabilities to be dropped in the container.
     * The format is the lower case of the  capability  definition without the "CAP_" prefix,
     * eg. CAP_SYS_MODULE should be specified as sys_module.
     * See capabilities(7).
     */
    Set<String> cap_drop();
}
