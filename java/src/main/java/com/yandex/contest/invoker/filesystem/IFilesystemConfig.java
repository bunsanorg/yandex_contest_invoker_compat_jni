package com.yandex.contest.invoker.filesystem;

import java.util.List;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:29
 */
public interface IFilesystemConfig {
    List<ICreateFile> getCreateFiles();
}
