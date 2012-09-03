package yandex.contest.invoker.impl.filesystem;

import yandex.contest.invoker.filesystem.IFile;
import yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 21:34
 */
public class File implements IFile {
    protected File() {}

    @Override
    public native String getPath();

    @Override
    public native int getMode();

    @Override
    public native IId getOwnerId();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
