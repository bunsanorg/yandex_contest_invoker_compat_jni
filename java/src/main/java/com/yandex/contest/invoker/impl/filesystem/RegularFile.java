package yandex.contest.invoker.impl.filesystem;

import yandex.contest.invoker.filesystem.IRegularFile;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 21:36
 */
public class RegularFile extends File implements IRegularFile {
    private RegularFile() {}

    @Override
    public native String getSource();

    public static native void classInit();
}
