package com.yandex.contest.invoker.jimpl;

import com.yandex.contest.invoker.IFdAlias;

/**
 * User: sarum9in
 * Date: 30.08.12
 * Time: 20:29
 */
public abstract class AbstractFdAlias implements IFdAlias {
    @Override
    public AccessMode getAccessMode() {
        throw new IllegalArgumentException("FdAlias does not support accessMode");
    }
}
