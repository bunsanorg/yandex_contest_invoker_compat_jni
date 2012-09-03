package com.yandex.contest.invoker.impl.unistd;

import com.yandex.contest.invoker.unistd.IMountEntry;

/**
 * User: sarum9in
 * Date: 08.08.12
 * Time: 12:39
 */
public class MountEntry implements IMountEntry {
    private MountEntry() {}

    private native void create(String fsname,
                               String dir,
                               String type,
                               String opts,
                               int freq,
                               int passno);

    public MountEntry(String fsname,
                      String dir,
                      String type,
                      String opts,
                      int freq,
                      int passno) {
        create(fsname, dir, type, opts, freq, passno);
    }

    public static native MountEntry proc();

    public static native MountEntry bind(String from, String to, String opts);

    public static native MountEntry bind(String from, String to);

    public static native MountEntry bindRO(String from, String to);

    @Override
    public native String fsname();

    @Override
    public native String dir();

    @Override
    public native String type();

    @Override
    public native String opts();

    @Override
    public native int freq();

    @Override
    public native int passno();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
