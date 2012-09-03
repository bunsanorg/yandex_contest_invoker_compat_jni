package yandex.contest.invoker.impl.filesystem;

import yandex.contest.invoker.filesystem.ICreateFile;
import yandex.contest.invoker.filesystem.IFilesystemConfig;

import java.util.List;

/**
 * User: sarum9in
 * Date: 20.08.12
 * Time: 15:44
 */
public class FilesystemConfig implements IFilesystemConfig {
    private FilesystemConfig() {}

    public FilesystemConfig(IFilesystemConfig filesystemConfig) {
        create(filesystemConfig);
    }

    private native void create(IFilesystemConfig filesystemConfig);

    @Override
    public native List<ICreateFile> getCreateFiles();

    @Override
    protected native void finalize();

    private long impl = 0;

    public static native void classInit();
}
