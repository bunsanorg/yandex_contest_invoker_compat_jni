package com.yandex.contest.invoker.lxc;

import com.yandex.contest.invoker.unistd.IMountEntry;

import java.util.List;

/**
 * User: sarum9in
 * Date: 11.07.12
 * Time: 16:05
 *
 * Note: IMountEntry#dir() is treated relative to the container root.
 */
public interface IMountConfig {
    /**
     * @return Path to fstab file.
     */
    String fstab();

    /**
     * @return List of mount entries.
     */
    List<IMountEntry> entries();
}
