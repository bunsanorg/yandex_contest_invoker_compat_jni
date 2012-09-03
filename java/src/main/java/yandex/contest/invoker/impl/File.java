package yandex.contest.invoker.impl;

import yandex.contest.invoker.IFile;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 17:26
 */
public class File implements IFile {
    private File() {}

    @Override
    public native String getPath();

    @Override
    public native AccessMode getAccessMode();

    private long impl = 0;

    public static native void classInit();
}
