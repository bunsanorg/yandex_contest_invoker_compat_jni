package com.yandex.contest.invoker.impl.unistd.access;

import com.yandex.contest.invoker.impl.InvokerFixture;
import com.yandex.contest.invoker.unistd.access.IId;
import org.junit.Assert;
import org.junit.Test;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 17:39
 */
public class IdTest extends InvokerFixture {
    @Test
    public void create() {
        IId id = new Id(1, 2);
        Assert.assertEquals(id.getUid(), 1);
        Assert.assertEquals(id.getGid(), 2);
    }
}
