package com.yandex.contest.invoker.impl;

import org.junit.*;

/**
 * User: sarum9in
 * Date: 13.08.12
 * Time: 19:11
 */
public class ContainerTest extends ContainerFixture {
    @Test
    public void create() throws Exception {
    }

    @Test
    public void setProcessGroupDefaultSettings() throws Exception {
        getContainer().setProcessGroupDefaultSettings(
                getProcessGroupDefaultSettings());
    }

    @Test
    public void create0() throws Exception {
        Container cnt = new Container();
        Assert.assertTrue(cnt.exists());
        cnt.destroy();
        Assert.assertFalse(cnt.exists());
    }

    @Test
    public void create1() throws Exception {
        Container cnt = new Container(getLXCConfig());
        Assert.assertTrue(cnt.exists());
        cnt.destroy();
        Assert.assertFalse(cnt.exists());
    }

    @Test
    public void create2() throws Exception {
        Container cnt = new Container(getContainerConfig(), getLXCConfig());
        Assert.assertTrue(cnt.exists());
        cnt.destroy();
        Assert.assertFalse(cnt.exists());
    }
}
