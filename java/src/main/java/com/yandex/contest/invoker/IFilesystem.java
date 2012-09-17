package com.yandex.contest.invoker;

import com.yandex.contest.invoker.unistd.IFileStatus;
import com.yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 03.07.12
 * Time: 19:29
 *
 * Filesystem interface is designed similar to POSIX, *nix shell,
 * but with necessary differences to make it convenient for Java.
 */
public interface IFilesystem {
    /**
     * @return Container's root directory.
     */
    String containerRoot();

    /**
     * @return path in container converted to host path.
     */
    String keepInRoot(String path);

    /**
     * Push local file into container.
     *
     * @param local path
     * @param remote path
     * @param ownerId file owner id, see chown(3)
     * @param mode file permissions, see chmod(3)
     * @throws InvokerException on error
     */
    void push(String local, String remote, IId ownerId, int mode) throws InvokerException;

    /**
     * Push hard link for local file into container.
     *
     * @param local path
     * @param remote path
     * @param ownerId file owner id, see chown(3)
     * @param mode file permissions, see chmod(3)
     * @throws InvokerException
     */
    void pushLink(String local, String remote, IId ownerId, int mode) throws InvokerException;

    /**
     * @param remote path
     * @return IFileStatus instance
     * @throws InvokerException
     */
    IFileStatus getFileStatus(String remote) throws InvokerException;

    /**
     * @param remote path
     * @param ownerId file owner id, see chown(3)
     * @throws InvokerException
     */
    void setOwnerId(String remote, IId ownerId) throws InvokerException;

    /**
     * @param remote path
     * @param mode file permissions, see chmod(3)
     * @throws InvokerException
     */
    void setMode(String remote, int mode) throws InvokerException;

    /**
     * Pull remote directory tree.
     *
     * @param remote path
     * @param local  path
     * @throws InvokerException on error
     */
    void pull(String remote, String local) throws InvokerException;
}
