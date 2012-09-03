package yandex.contest.invoker.impl;

import junit.framework.Assert;
import org.junit.Test;

/**
 * User: sarum9in
 * Date: 24.08.12
 * Time: 23:52
 */
public class LogTest extends InvokerFixture {
    @Test
    public void registerInstanceNull() {
        boolean thrown = false;
        try {
            Log.registerInstance(null);
        } catch (NullPointerException e) {
            thrown = true;
        }
        Assert.assertTrue(thrown);
    }
}
