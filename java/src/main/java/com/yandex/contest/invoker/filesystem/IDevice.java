package com.yandex.contest.invoker.filesystem;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:34
 */
public interface IDevice extends IFile {
    enum Type {
        CHAR,
        BLOCK
    }

    Type getType();
    int getMajor();
    int getMinor();
}
