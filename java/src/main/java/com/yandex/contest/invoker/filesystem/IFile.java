package com.yandex.contest.invoker.filesystem;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:31
 */
public interface IFile extends ICreateFile {
    String getPath();
    int getMode();
    com.yandex.contest.invoker.unistd.access.IId getOwnerId();
}
