package com.yandex.contest.invoker.jimpl;

import com.yandex.contest.invoker.IFile;

/**
 * User: sarum9in
 * Date: 15.08.12
 * Time: 17:33
 */
public class File implements IFile {
    private String path;
    private AccessMode accessMode;

    public File(String path, AccessMode accessMode) {
        this.path = path;
        this.accessMode = accessMode;
    }

    @Override
    public String getPath() {
        return path;
    }

    @Override
    public AccessMode getAccessMode() {
        return accessMode;
    }
}
