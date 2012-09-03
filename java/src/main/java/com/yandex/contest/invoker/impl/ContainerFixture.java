package yandex.contest.invoker.impl;

import yandex.contest.invoker.IContainer;
import yandex.contest.invoker.IContainerConfig;
import yandex.contest.invoker.lxc.ILXCConfig;
import yandex.contest.invoker.process.IProcessDefaultSettings;
import yandex.contest.invoker.process_group.IProcessGroupDefaultSettings;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 15:45
 */
public class ContainerFixture extends InvokerFixture {
    private ContainerConfig containerConfig = null;
    private Container container = null;

    @Before
    public void setUp() throws Exception {
        containerConfig = ContainerConfig.fromEnvironment();
        container = new Container(containerConfig);
        Assert.assertTrue(container.exists());
    }

    @After
    public void tearDown() {
        container.destroy();
        Assert.assertFalse(container.exists());
        container = null;
    }

    public IContainer getContainer() {
        Assert.assertNotNull(container);
        return container;
    }

    public IContainerConfig getContainerConfig() {
        Assert.assertNotNull(containerConfig);
        return containerConfig;
    }

    public IProcessGroupDefaultSettings getProcessGroupDefaultSettings() {
        Assert.assertNotNull(containerConfig);
        return containerConfig.getProcessGroupDefaultSettings();
    }

    public IProcessDefaultSettings getProcessDefaultSettings() {
        Assert.assertNotNull(containerConfig);
        return getProcessGroupDefaultSettings().getProcessDefaultSettings();
    }

    public ILXCConfig getLXCConfig() {
        Assert.assertNotNull(containerConfig);
        return containerConfig.getLXCConfig();
    }
}
