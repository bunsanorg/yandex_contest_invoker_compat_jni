package yandex.contest.invoker.impl.filesystem;

import yandex.contest.invoker.filesystem.IDirectory;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 21:38
 */
public class Directory extends File implements IDirectory {
    private Directory() {}

    public static native void classInit();
}
