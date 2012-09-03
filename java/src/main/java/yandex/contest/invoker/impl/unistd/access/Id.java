package yandex.contest.invoker.impl.unistd.access;

import yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 08.08.12
 * Time: 12:42
 */
public class Id implements IId {
    private Id() {}

    private native void create(int uid, int gid);

    public Id(int uid, int gid) {
        create(uid, gid);
    }

    @Override
    public native int getUid();

    @Override
    public native int getGid();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
