package com.yandex.contest.invoker.jimpl;

import com.yandex.contest.invoker.IFDAlias;

/**
 * User: sarum9in
 * Date: 30.08.12
 * Time: 20:29
 */
public abstract class AbstractFDAlias implements IFDAlias {
    @Override
    public AccessMode getAccessMode() {
        throw new IllegalArgumentException("FDAlias does not support accessMode");
    }
}
