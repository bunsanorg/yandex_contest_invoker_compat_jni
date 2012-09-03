package com.yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 23.07.12
 * Time: 17:36
 */
public interface IFile extends IStream, INonPipeStream {
    String getPath();

    @Override
    AccessMode getAccessMode();
}
