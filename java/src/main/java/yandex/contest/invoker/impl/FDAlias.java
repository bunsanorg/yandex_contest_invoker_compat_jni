package yandex.contest.invoker.impl;

import yandex.contest.invoker.IFDAlias;
import yandex.contest.invoker.jimpl.AbstractFDAlias;

/**
 * User: sarum9in
 * Date: 30.08.12
 * Time: 20:22
 */
public class FDAlias extends AbstractFDAlias implements IFDAlias {
    private FDAlias() {}

    @Override
    public native int getFD();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
