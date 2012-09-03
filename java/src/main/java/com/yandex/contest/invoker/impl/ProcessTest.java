package yandex.contest.invoker.impl;

import yandex.contest.invoker.IPipe;
import yandex.contest.invoker.IProcess;
import yandex.contest.invoker.IStream;
import yandex.contest.invoker.impl.unistd.access.Id;
import yandex.contest.invoker.jimpl.AbstractFDAlias;
import yandex.contest.invoker.jimpl.File;
import yandex.contest.invoker.process.IProcessResult;
import junit.framework.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 19:46
 */
public class ProcessTest extends ProcessGroupFixture {
    @Test
    public void true_() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        runOK();
        IProcessResult pr = p0.getResult();
        Assert.assertEquals(pr.getCompletionStatus(), IProcessResult.CompletionStatus.OK);
        Assert.assertEquals(pr.getExitStatus().intValue(), 0);
        Assert.assertNull(pr.getTermSig());
        Assert.assertNotNull(pr.getResourceUsage());
    }

    @Test
    public void false_() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("false");
        runAE();
        IProcessResult pr = p0.getResult();
        Assert.assertEquals(pr.getCompletionStatus(), IProcessResult.CompletionStatus.ABNORMAL_EXIT);
        Assert.assertEquals(pr.getExitStatus().intValue(), 1);
        Assert.assertNull(pr.getTermSig());
        Assert.assertNotNull(pr.getResourceUsage());
    }

    @Test
    public void processSetArguments() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("sh");
        List<String> arguments = Arrays.asList("sh", "-ec", "exit 10");
        p0.setArguments(arguments);
        Assert.assertEquals(arguments, p0.getArguments());
        runAE();
        Assert.assertEquals(p0.getResult().getExitStatus(), (Integer)10);
    }

    @Test
    public void setCurrentPath() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        // /dev always exists
        p0.setCurrentPath("/dev");
        runOK();
    }

    @Test
    public void setEnvironment() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        p0.setEnvironment(new HashMap<String, String>());
        runOK();
    }

    @Test
    public void ownerId() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        p0.setOwnerId(new Id(1, 2));
        Assert.assertEquals(1, p0.getOwnerId().getUid());
        Assert.assertEquals(2, p0.getOwnerId().getGid());
    }

    @Test
    public void terminateGroupOnCrash() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        p0.setTerminateGroupOnCrash(false);
        Assert.assertFalse(p0.terminateGroupOnCrash());
        p0.setTerminateGroupOnCrash(true);
        Assert.assertTrue(p0.terminateGroupOnCrash());
        runOK();
    }

    @Test
    public void groupWaitsForTermination() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        p0.setGroupWaitsForTermination(false);
        Assert.assertFalse(p0.groupWaitsForTermination());
        p0.setGroupWaitsForTermination(true);
        Assert.assertTrue(p0.groupWaitsForTermination());
        runOK();
    }

    @Test
    public void executable() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        Assert.assertEquals("true", p0.getExecutable());
        runOK();
    }

    @Test
    public void streams() throws Exception {
        IProcess p0 = getProcessGroup().createProcess("true");
        IProcess p1 = getProcessGroup().createProcess("true");
        p0.setStream(0, new File("/dev/null", IStream.AccessMode.READ_WRITE));
        Assert.assertTrue(p0.hasStream(0));
        Assert.assertNotNull(p0.getStream(0));
        p0.closeStream(0);
        Assert.assertFalse(p0.hasStream(0));
        // FDalias
        IPipe pipe = getProcessGroup().createPipe();
        p0.setStream(1, pipe.getOutputStream());
        Assert.assertTrue(p0.hasStream(1));
        p1.setStream(0, pipe.getInputStream());
        Assert.assertTrue(p1.hasStream(0));
        p0.setStream(2, new AbstractFDAlias() {
            @Override
            public int getFD() {
                return 1;
            }
        });
        Assert.assertTrue(p0.hasStream(2));
        runOK();
    }
}
