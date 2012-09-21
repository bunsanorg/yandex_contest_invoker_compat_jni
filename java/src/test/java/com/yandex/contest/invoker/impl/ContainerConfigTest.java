package com.yandex.contest.invoker.impl;

import com.yandex.contest.invoker.*;
import com.yandex.contest.invoker.IFile;
import com.yandex.contest.invoker.filesystem.*;
import com.yandex.contest.invoker.impl.unistd.*;
import com.yandex.contest.invoker.impl.unistd.access.*;
import com.yandex.contest.invoker.lxc.*;
import com.yandex.contest.invoker.process.*;
import com.yandex.contest.invoker.process_group.*;
import com.yandex.contest.invoker.unistd.*;
import com.yandex.contest.invoker.unistd.access.*;
import junit.framework.Assert;
import org.junit.Test;

import java.lang.reflect.Method;
import java.lang.reflect.Type;
import java.lang.reflect.TypeVariable;
import java.util.*;

/**
 * User: sarum9in
 * Date: 16.08.12
 * Time: 17:28
 */
public class ContainerConfigTest extends InvokerFixture {

    private static Set<String> getCapDrop() {
        Set<String> capDrop = new HashSet<String>();
        capDrop.add("mknod");
        capDrop.add("setuid");
        return capDrop;
    }

    private static Map<String, String> getCgroup() {
        Map<String, String> cgroup = new HashMap<String, String>();
        cgroup.put("memory.limit_in_bytes", "1G");
        cgroup.put("cpuset.cpus", "0");
        return cgroup;
    }

    private static IMountConfig getMountConfig() {
        return new IMountConfig() {
            @Override
            public String fstab() {
                return "/some/path";
            }

            private MountEntry bindRO(String path) {
                return MountEntry.bindRO(path, path);
            }

            @Override
            public List<IMountEntry> entries() {
                List<IMountEntry> entries = new ArrayList<IMountEntry>();
                entries.add(MountEntry.proc());
                entries.add(bindRO("/etc"));
                entries.add(bindRO("/usr"));
                entries.add(bindRO("/bin"));
                entries.add(bindRO("/opt"));
                entries.add(bindRO("/lib"));
                return entries;
            }
        };
    }

    public static ILXCConfig getLXCConfig() {
        return new ILXCConfig() {
            @Override
            public Arch arch() {
                return Arch.x86_64;
            }

            @Override
            public String utsname() {
                return "container_name";
            }

            @Override
            public String console() {
                return "/dev/null";
            }

            @Override
            public Integer tty() {
                return 10;
            }

            @Override
            public IMountConfig mount() {
                return getMountConfig();
            }

            @Override
            public String rootfs() {
                return null;
            }

            @Override
            public Map<String, String> cgroup() {
                return getCgroup();
            }

            @Override
            public Set<String> cap_drop() {
                return getCapDrop();
            }
        };
    }

    public static IProcessDefaultSettings getProcessDefaultSettings() {
        return new IProcessDefaultSettings() {
            @Override
            public IProcessResourceLimits getResourceLimits() {
                return new IProcessResourceLimits() {
                    @Override
                    public long getUserTimeLimitMillis() {
                        return 2 * 1000;
                    }

                    @Override
                    public long getMemoryLimitBytes() {
                        return 64 * 1024 * 1024;
                    }

                    @Override
                    public long getOutputLimitBytes() {
                        return 8 * 1024 * 1024;
                    }

                    @Override
                    public long getNumberOfProcesses() {
                        return 32;
                    }
                };
            }

            @Override
            public Map<String, String> getEnvironment() {
                Map<String, String> env = new HashMap<String, String>();
                env.put("PATH", "/bin:/usr/bin");
                return env;
            }

            @Override
            public String getCurrentPath() {
                return "/tmp";
            }

            @Override
            public IId getOwnerId() {
                return new Id(0, 0);
            }

            @Override
            public Map<Integer, INonPipeStream> getDescriptors() {
                return new HashMap<Integer, INonPipeStream>();
            }
        };
    }

    public static IProcessGroupDefaultSettings getProcessGroupDefaultSettings() {
        return new IProcessGroupDefaultSettings() {
            @Override
            public IProcessGroupResourceLimits getResourceLimits() {
                return new IProcessGroupResourceLimits() {
                    @Override
                    public long getRealTimeLimitMillis() {
                        return 10 * 1000; // 10s
                    }
                };
            }

            @Override
            public IProcessDefaultSettings getProcessDefaultSettings() {
                return ContainerConfigTest.getProcessDefaultSettings();
            }
        };
    }

    public static IControlProcessConfig getControlProcessConfig() {
        return new IControlProcessConfig() {
            @Override
            public String getExecutable() {
                return "yandex_contest_invoker_ctl";
            }
        };
    }

    public static IDevice getCreateCharDevice(final String path,
                                              final int minor,
                                              final int major) {
        return new IDevice() {

            @Override
            public Type getType() {
                return Type.CHAR;
            }

            @Override
            public int getMajor() {
                return major;
            }

            @Override
            public int getMinor() {
                return minor;
            }

            @Override
            public String getPath() {
                return path;
            }

            @Override
            public int getMode() {
                return 0666;
            }

            @Override
            public IId getOwnerId() {
                return new Id(0, 0);
            }
        };
    }

    public static IFilesystemConfig getFilesystemConfig() {
        return new IFilesystemConfig() {
            @Override
            public List<ICreateFile> getCreateFiles() {
                List<ICreateFile> createFiles = new ArrayList<ICreateFile>();
                createFiles.add(getCreateCharDevice("/dev/null", 1, 3));
                createFiles.add(new IRegularFile() {
                    @Override
                    public String getSource() {
                        return null;
                    }

                    @Override
                    public String getPath() {
                        return "/some/path";
                    }

                    @Override
                    public int getMode() {
                        return 0644;
                    }

                    @Override
                    public IId getOwnerId() {
                        return new Id(1, 2);
                    }
                });
                createFiles.add(new IDirectory() {
                    @Override
                    public String getPath() {
                        return "/tmp";
                    }

                    @Override
                    public int getMode() {
                        return 01777;
                    }

                    @Override
                    public IId getOwnerId() {
                        return new Id(3, 4);
                    }
                });
                createFiles.add(new ISymLink() {
                    @Override
                    public String getValue() {
                        return "/usr/lib";
                    }

                    @Override
                    public String getPath() {
                        return "/lib";
                    }

                    @Override
                    public int getMode() {
                        return 0;
                    }

                    @Override
                    public IId getOwnerId() {
                        return new Id(5, 6);
                    }
                });
                return createFiles;
            }
        };
    }

    public static IContainerConfig getContainerConfig() {
        return new IContainerConfig() {
            @Override
            public String getContainersDir() {
                return "/tmp";
            }

            @Override
            public ILXCConfig getLXCConfig() {
                return ContainerConfigTest.getLXCConfig();
            }

            @Override
            public IProcessGroupDefaultSettings getProcessGroupDefaultSettings() {
                return ContainerConfigTest.getProcessGroupDefaultSettings();
            }

            @Override
            public IControlProcessConfig getControlProcessConfig() {
                return ContainerConfigTest.getControlProcessConfig();
            }

            @Override
            public IFilesystemConfig getFilesystemConfig() {
                return ContainerConfigTest.getFilesystemConfig();
            }
        };
    }

    private boolean isEqualComparable(Class<?> clazz) {
        return clazz.isPrimitive() ||
                clazz.isEnum() ||
                Integer.class.isAssignableFrom(clazz) ||
                String.class.isAssignableFrom(clazz);
    }

    // For JNI wrappers
    private Class<?> getInterface(Object object) {
        Class<?> clazz = object.getClass();
        if (isEqualComparable(clazz))
            return clazz;
        Class<?> ifaces[] = clazz.getInterfaces();
        if (ifaces.length != 1) {
            StringBuffer buf = new StringBuffer();
            buf.append("{");
            for (int i = 0; i < ifaces.length; ++i) {
                if (i != 0)
                    buf.append(", ");
                buf.append('"');
                buf.append(ifaces[i].getCanonicalName());
                buf.append('"');
            }
            buf.append("}");
            Assert.fail("Unknown interfaces: " + buf.toString());
        }
        Assert.assertEquals(1, ifaces.length);
        return ifaces[0];
    }

    private void assertEqualCollections(
            Class<?> iface, Collection cfg, Collection icfg) throws Exception {
        if (cfg instanceof Set) {
            Assert.assertTrue(icfg instanceof Set);
            assertEqualSets(iface, (Set)cfg, (Set)icfg);
        } else if (cfg instanceof List) {
            Assert.assertTrue(icfg instanceof List);
            assertEqualLists(iface, (List)cfg, (List)icfg);
        } else {
            Assert.fail("Unknown class: " + cfg.getClass().getCanonicalName());
        }
    }

    private void assertEqualLists(Class<?> iface, List cfg, List icfg) throws Exception {
        Assert.assertEquals(cfg.size(), icfg.size());
        Iterator a = cfg.iterator();
        Iterator ia = icfg.iterator();
        while (a.hasNext()) {
            Assert.assertTrue(ia.hasNext());
            Object cfg_ = a.next();
            Object icfg_ = ia.next();
            assertEqual(iface == null ? getInterface(cfg_) : iface, cfg_, icfg_);
        }
        Assert.assertFalse(a.hasNext());
        Assert.assertFalse(ia.hasNext());
    }

    private void assertEqualSets(Class<?> iface, Set cfg, Set icfg) throws Exception {
        Assert.assertEquals(cfg, icfg);
    }

    private void assertEqualMaps(Class<?> iface, Map cfg, Map icfg) throws Exception {
        Assert.assertEquals(cfg.size(), icfg.size());
        for (Map.Entry entry: (Set<Map.Entry>)cfg.entrySet()) {
            Assert.assertTrue(icfg.containsKey(entry.getKey()));
            Object ivalue = icfg.get(entry.getKey());
            assertEqual(iface == null ? getInterface(entry.getValue()) : iface,
                    entry.getValue(), ivalue);
        }
    }

    private void assertEqual(Class<?> iface, Object cfg, Object icfg) throws Exception {
        Assert.assertTrue(iface.isInstance(cfg));
        Assert.assertTrue(iface.isInstance(icfg));
        if (isEqualComparable(iface)) {
            Assert.assertEquals(cfg, icfg);
        } else {
            for (Method method: iface.getMethods()) {
                Class<?> returnType = method.getReturnType();
                if (method.getParameterTypes().length > 0)
                    Assert.fail("Illegal method: " + iface.getName() + "#" + method.getName());
                Object cfg_ = method.invoke(cfg);
                Object icfg_ = method.invoke(icfg);
                System.err.println(" + " + returnType.getCanonicalName());
                if (isEqualComparable(returnType)) {
                    Assert.assertEquals(cfg_, icfg_);
                } else if (Collection.class.isAssignableFrom(returnType)) {
                    assertEqualCollections(null, (Collection)cfg_, (Collection)icfg_);
                } else if (Map.class.isAssignableFrom(returnType)) {
                    assertEqualMaps(null, (Map) cfg_, (Map) icfg_);
                } else if (returnType.isInterface()) {
                    assertEqual(returnType, cfg_, icfg_);
                } else {
                    Assert.fail("Unknown type: " + returnType.getCanonicalName());
                }
                System.err.println("-" + returnType.getCanonicalName());
            }
        }
    }

    @Test
    public void create() throws Exception {
        IContainerConfig iContainerConfig = getContainerConfig();
        ContainerConfig containerConfig = new ContainerConfig(iContainerConfig);
        assertEqual(IContainerConfig.class, containerConfig, iContainerConfig);
    }

    @Test
    public void createNull() throws Exception {
        boolean thrown = false;
        try {
            ContainerConfig containerConfig = new ContainerConfig(null);
        } catch (NullPointerException e) {
            thrown = true;
        }
        Assert.assertTrue(thrown);
    }

    @Test
    public void fromEnvironment() {
        ContainerConfig.fromEnvironment();
    }
}
