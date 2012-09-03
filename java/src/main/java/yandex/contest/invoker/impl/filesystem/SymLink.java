package yandex.contest.invoker.impl.filesystem;

import yandex.contest.invoker.filesystem.ISymLink;

/**
 * User: sarum9in
 * Date: 21.08.12
 * Time: 21:39
 */
public class SymLink extends File implements ISymLink {
    private SymLink() {}

    @Override
    public native String getValue();

    public static native void classInit();
}
