package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IProcessGroup;
import com.yandex.contest.invoker.process_group.IProcessGroupResult;
import org.junit.Assert;
import org.junit.After;
import org.junit.Before;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 19:12
 */
public class ProcessGroupFixture extends ContainerFixture {
    private ProcessGroup processGroup = null;

    @Before
    public void setUp() throws Exception {
        super.setUp();
        Assert.assertNull(processGroup);
        IProcessGroup processGroup_ = getContainer().createProcessGroup();
        // may be removed if not instance
        Assert.assertTrue(processGroup_ instanceof ProcessGroup);
        processGroup = (ProcessGroup)processGroup_;
        Assert.assertTrue(processGroup.exists());
    }

    @After
    public void tearDown() {
        Assert.assertNotNull(processGroup);
        Assert.assertTrue(processGroup.exists());
        processGroup.destroy();
        Assert.assertFalse(processGroup.exists());
        processGroup = null;
        super.tearDown();
    }

    public IProcessGroup getProcessGroup() {
        Assert.assertNotNull(processGroup);
        return processGroup;
    }

    public void verifyOK() throws Exception {
        Assert.assertEquals(IProcessGroupResult.CompletionStatus.OK,
                getProcessGroup().waitFor().getCompletionStatus());
    }

    public void verifyAE() throws Exception {
        Assert.assertEquals(IProcessGroupResult.CompletionStatus.ABNORMAL_EXIT,
                getProcessGroup().waitFor().getCompletionStatus());
    }

    public void verifySTOPPED() throws Exception {
        Assert.assertEquals(IProcessGroupResult.CompletionStatus.STOPPED,
                getProcessGroup().waitFor().getCompletionStatus());
    }

    public void runOK() throws Exception {
        getProcessGroup().synchronizedCall();
        verifyOK();
    }

    public void runAE() throws Exception {
        getProcessGroup().synchronizedCall();
        verifyAE();
    }
}
