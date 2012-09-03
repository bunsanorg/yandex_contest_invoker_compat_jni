package yandex.contest.invoker.unistd;

/**
 * User: sarum9in
 * Date: 11.07.12
 * Time: 16:44
 */
public interface IMountEntry {
    /**
     * @return Device or server for filesystem.
     */
    String fsname();

    /**
     * @return Directory mounted on.
     */
    String dir();

    /**
     * @return Type of filesystem: ufs, nfs, etc.
     */
    String type();

    /**
     * @return Mount options.
     */
    String opts();

    /**
     * @return Dump frequency (in days).
     */
    int freq();

    /**
     * @return Pass number for `fsck'.
     */
    int passno();
}
