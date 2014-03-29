package com.yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 30.08.12
 * Time: 20:21
 */
public interface IFdAlias extends IStream, INonPipeStream {
    int getFd();
}
