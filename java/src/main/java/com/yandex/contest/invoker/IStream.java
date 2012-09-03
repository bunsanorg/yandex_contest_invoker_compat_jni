package com.yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 05.07.12
 * Time: 16:37
 */
public interface IStream {
    /**
     * See man for fcntl.h(0):
     * O_ACCMODE, O_RDONLY, O_RDWR, O_WRONLY.
     */
    enum AccessMode {
        READ_ONLY,
        WRITE_ONLY,
        READ_WRITE
    }

    AccessMode getAccessMode();
}
