package common.invocation.impl.unistd;

import common.invocation.impl.InvokerFixture;
import common.invocation.unistd.IMountEntry;
import junit.framework.Assert;
import org.junit.Test;

import java.util.Arrays;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 17:07
 */
public class MountEntryTest extends InvokerFixture {
    @Test
    public void create() {
        IMountEntry entry = new MountEntry("a", "b", "c", "d", 4, 5);
        Assert.assertEquals("a", entry.fsname());
        Assert.assertEquals("b", entry.dir());
        Assert.assertEquals("c", entry.type());
        Assert.assertEquals("d", entry.opts());
        Assert.assertEquals(4, entry.freq());
        Assert.assertEquals(5, entry.passno());
    }

    @Test
    public void proc() {
        IMountEntry entry = MountEntry.proc();
        Assert.assertEquals("/proc", entry.dir());
    }

    @Test
    public void bind2() {
        IMountEntry entry = MountEntry.bind("from_dir", "to_dir");
        Assert.assertEquals("from_dir", entry.fsname());
        Assert.assertEquals("to_dir", entry.dir());
    }

    @Test
    public void bind3() {
        IMountEntry entry = MountEntry.bind("from_dir", "to_dir", "opts");
        Assert.assertEquals("from_dir", entry.fsname());
        Assert.assertEquals("to_dir", entry.dir());
        Assert.assertTrue(Arrays.asList(entry.opts().split(",")).contains("opts"));
    }

    @Test
    public void bindRO() {
        IMountEntry entry = MountEntry.bindRO("from_dir", "to_dir");
        Assert.assertEquals("from_dir", entry.fsname());
        Assert.assertEquals("to_dir", entry.dir());
    }
}
