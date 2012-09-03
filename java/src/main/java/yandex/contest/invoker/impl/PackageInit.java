package yandex.contest.invoker.impl;

import java.lang.reflect.InvocationTargetException;

/**
 * User: sarum9in
 * Date: 08.08.12
 * Time: 12:53
 */
public class PackageInit {
    public static void classInit() {}

    private static native Class[] getClasses();

    /**
     * Should be called before package usage
     * @throws Exception -- package is in undefined state after that
     */
    public static synchronized void init() throws Exception {
        try {
            for (Class c: getClasses()) {
                c.getMethod("classInit").invoke(null);
            }
        } catch (InvocationTargetException e) {
            printCause(e);
            throw e;
        }
    }

    private static void printCause(Throwable exception) {
        try {
            if (exception != null) {
                System.err.println("________________________________________");
                exception.printStackTrace();
                printCause(exception.getCause());
            }
        } catch (Throwable e) {}
    }

    /**
     * Should be called before library unload.
     */
    public static synchronized native void deinit();

    static {
        try {
            System.loadLibrary("yandex_contest_invoker_jni");
        } catch (UnsatisfiedLinkError e) {
            e.printStackTrace();
            throw e;
        }
    }
}
