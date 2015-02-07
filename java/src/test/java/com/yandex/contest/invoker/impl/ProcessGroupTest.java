package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.impl.NotificationStream;
import com.yandex.contest.invoker.INotificationStream;
import com.yandex.contest.invoker.IPipe;
import com.yandex.contest.invoker.IProcess;
import com.yandex.contest.invoker.IProcessGroup;
import com.yandex.contest.invoker.IStream;
import com.yandex.contest.invoker.NotificationStreamProtocol;
import com.yandex.contest.invoker.process.IProcessResult;
import com.yandex.contest.invoker.process_group.IProcessGroupResult;
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
    public void notification() throws Exception {
        IProcessGroup pg = getProcessGroup();
        IProcess p0 = pg.createProcess("true");

        INotificationStream notificationStream0 = pg.getNotifier(0);
        IStream pipeEnd0 = pg.addNotifier();
        pg.setNotifier(0, pipeEnd0);
        Assert.assertEquals(pg.getNotifier(0).getProtocol(),
                            NotificationStreamProtocol.NATIVE);
        pg.setNotifier(0, pipeEnd0, NotificationStreamProtocol.NATIVE);
        Assert.assertEquals(pg.getNotifier(0).getProtocol(),
                            NotificationStreamProtocol.NATIVE);
        pg.setNotifier(0, notificationStream0);
        Assert.assertEquals(pg.getNotifier(0).getProtocol(),
                            NotificationStreamProtocol.NATIVE);

        IStream pipeEnd1 = pg.addNotifier(NotificationStreamProtocol.PLAIN_TEXT);
        pg.setNotifier(1, pipeEnd1, NotificationStreamProtocol.PLAIN_TEXT);
        Assert.assertEquals(pg.getNotifier(1).getProtocol(),
                            NotificationStreamProtocol.PLAIN_TEXT);

        IPipe pipe2 = pg.createPipe();
        Assert.assertEquals(pg.addNotifier(pipe2.getInputStream()), 2);
        Assert.assertEquals(pg.getNotifier(2).getProtocol(),
                            NotificationStreamProtocol.NATIVE);

        IPipe pipe3 = pg.createPipe();
        Assert.assertEquals(pg.addNotifier(pipe3.getInputStream(),
                                           NotificationStreamProtocol.PLAIN_TEXT), 3);
        Assert.assertEquals(pg.getNotifier(2).getProtocol(),
                            NotificationStreamProtocol.PLAIN_TEXT);

        IPipe pipe4 = pg.createPipe();
        INotificationStream notificationStream4 =
            new NotificationStream(pipe4.getInputStream(),
                                   NotificationStreamProtocol.PLAIN_TEXT);
        Assert.assertEquals(pg.addNotifier(notificationStream4), 4);
        Assert.assertEquals(pg.getNotifier(4).getProtocol(),
                            NotificationStreamProtocol.PLAIN_TEXT);
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
}
