package com.yandex.contest.invoker.unistd;

import com.yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 23.08.12
 * Time: 20:18
 */
public interface IFileStatus {
    /**
     * ID of device containing file
     */
    //dev_t dev();

    /**
     * inode number
     */
    long ino();

    /**
     * protection
     */
    int mode();

    /**
     * number of hard links
     */
    long nlink();

    /**
     * uid/gid of owner
     */
    IId ownerId();

    /**
     * device ID (if special file)
     */
    //dev_t rdev();

    /**
     * total size, in bytes
     */
    long size();

    /**
     * blocksize for file system I/O
     */
    long blksize();

    /**
     * number of 512B blocks allocated
     */
    long blocks();

    /**
     * time of last access
     */
    long atime();

    /**
     * time of last modification
     */
    long mtime();

    /**
     * time of last status change
     */
    long ctime();

    /**
     * File access mode.
     *
     * @return mode & O_ACCMODE
     */
    int getAccmode();

    /**
     * File type.
     *
     * @return mode & S_IFMT
     */
    int getType();

    boolean isFifo();

    boolean isCharDevice();

    boolean isDirectory();

    boolean isBlockDevice();

    boolean isRegularFile();

    boolean isSymbolicLink();

    boolean isSocket();

    int getPermissions();
}
