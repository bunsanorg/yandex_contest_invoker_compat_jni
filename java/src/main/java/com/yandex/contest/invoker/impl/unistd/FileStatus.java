package com.yandex.contest.invoker.impl.unistd;

import com.yandex.contest.invoker.unistd.IFileStatus;
import com.yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 23.08.12
 * Time: 20:32
 */
public class FileStatus implements IFileStatus {
    private FileStatus() {}

    @Override
    public native long ino();

    @Override
    public native int mode();

    @Override
    public native long nlink();

    @Override
    public native IId ownerId();

    @Override
    public native long size();

    @Override
    public native long blksize();

    @Override
    public native long blocks();

    @Override
    public native long atime();

    @Override
    public native long mtime();

    @Override
    public native long ctime();

    @Override
    public native int getAccmode();

    @Override
    public native int getType();

    @Override
    public native boolean isFIFO();

    @Override
    public native boolean isCharDevice();

    @Override
    public native boolean isDirectory();

    @Override
    public native boolean isBlockDevice();

    @Override
    public native boolean isRegularFile();

    @Override
    public native boolean isSymbolicLink();

    @Override
    public native boolean isSocket();

    @Override
    public native int getPermissions();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
