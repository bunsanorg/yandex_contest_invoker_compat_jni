package com.yandex.contest.invoker.lxc;

/**
 * Created with IntelliJ IDEA.
 * User: sarum9in
 * Date: 14.11.12
 * Time: 20:43
 */
public interface IRootfsConfig {

    /**
     * @return Image file, a directory or a block device for root file system.
     */
    String fsname();

    /**
     * @return Where to recursively bind lxc.rootfs before pivoting.
     */
    String mount();
}
