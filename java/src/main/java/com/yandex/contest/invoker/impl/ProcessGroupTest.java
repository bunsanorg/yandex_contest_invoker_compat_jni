package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.IPipe;
import com.yandex.contest.invoker.IProcess;
import com.yandex.contest.invoker.process.IProcessResult;
import junit.framework.Assert;
import org.junit.Test;

import java.util.Arrays;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 19:19
 */
public class ProcessGroupTest extends ProcessGroupFixture {
    @Test
    public void create() {}

    @Test
    public void setProcessDefaultSettings() throws Exception {
        getProcessGroup().setProcessDefaultSettings(getProcessDefaultSettings());
        IProcess p0 = getProcessGroup().createProcess("true");
        runOK();
    }

    @Test
    public void startWaitResult() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        getProcessGroup().start();
        getProcessGroup().waitFor();
        verifyOK();
        IProcessResult pr = p0.getResult();
        Assert.assertEquals(pr.getCompletionStatus(), IProcessResult.CompletionStatus.OK);
        Assert.assertEquals(pr.getExitStatus().intValue(), 0);
        Assert.assertNull(pr.getTermSig());
        Assert.assertNotNull(pr.getResourceUsage());
    }

    @Test
    public void createPipe() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("echo");
        final String msg = "123";
        p0.setArguments(Arrays.asList(new String[]{"echo", msg}));
        IProcess p1 = getProcessGroup().createProcess("sh");
        p1.setArguments(Arrays.asList(
                new String[]{"sh", "-ec", "read x; test $x = \"" + msg + "\""}));
        IPipe pipe = getProcessGroup().createPipe();
        p0.setStream(1, pipe.getOutputStream());
        p1.setStream(0, pipe.getInputStream());
        runOK();
    }

    @Test
    public void poll() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("sleep");
        p0.setArguments(Arrays.asList(new String[]{"sleep", "0.1"}));
        getProcessGroup().start();
        while (getProcessGroup().poll() == null);
        verifyOK();
    }

    @Test
    public void stop() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("sleep");
        p0.setArguments(Arrays.asList(new String[]{"sleep", "0.1"}));
        getProcessGroup().start();
        getProcessGroup().stop();
        verifySTOPPED();
    }

    @Test
    public void freezing() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("sleep");
        p0.setArguments(Arrays.asList(new String[]{"sleep", "0.1"}));
        getProcessGroup().start();
        getProcessGroup().freeze();
        getProcessGroup().unfreeze();
        getProcessGroup().waitFor();
        verifyOK();
    }
}
