package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.ILog;
import org.junit.AfterClass;
import org.junit.Assert;
import org.junit.BeforeClass;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 15:15
 */
public class InvokerFixture {
    private static boolean inited = false;
    @BeforeClass
    public static void oneTimeSetUp() throws Exception {
        Assert.assertFalse(inited);
        PackageInit.init();
        Log.registerInstance(new ILog() {
            @Override
            public void append(ILog.Level level, String position, String message) {
                System.out.println("[" + level + "] at [" + position + "] " + message);
            }
        });
        inited = true;
    }

    @AfterClass
    public static void oneTimeTearDown() {
        Assert.assertTrue(inited);
        PackageInit.deinit();
        inited = false;
    }
}
