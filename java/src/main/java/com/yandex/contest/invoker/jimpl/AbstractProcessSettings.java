package yandex.contest.invoker.jimpl;

import yandex.contest.invoker.IFile;
import yandex.contest.invoker.IProcess;
import yandex.contest.invoker.IProcessGroup;
import yandex.contest.invoker.IProcessSettings;
import yandex.contest.invoker.process.IProcessResourceLimits;
import yandex.contest.invoker.unistd.access.IId;

/**
 * User: sarum9in
 * Date: 07.08.12
 * Time: 15:32
 */
public abstract class AbstractProcessSettings implements IProcessSettings {
    @Override
    public String getStdinRedirection() {
        return null;
    }

    @Override
    public String getStdoutRedirection() {
        return null;
    }

    @Override
    public String getStderrRedirection() {
        return null;
    }

    @Override
    public IProcessResourceLimits getResourceLimits() {
        return null;
    }

    @Override
    public IId getOwnerId() {
        return null;
    }

    @Override
    public String getCurrentPath() {
        return null;
    }

    @Override
    public IProcess createProcess(IProcessGroup processGroup) {
        IProcess process = processGroup.createProcess(getExecutable());
        process.setArguments(getArguments());
        final String stdin = getStdinRedirection();
        final String stdout = getStdoutRedirection();
        final String stderr = getStderrRedirection();
        if (stdin != null) {
            process.setStream(0, new IFile() {
                @Override
                public String getPath() {
                    return stdin;
                }
                @Override
                public AccessMode getAccessMode() {
                    return AccessMode.READ_ONLY;
                }
            });
        }
        if (stdout != null) {
            process.setStream(1, new IFile() {
                @Override
                public String getPath() {
                    return stdout;
                }
                @Override
                public AccessMode getAccessMode() {
                    return AccessMode.WRITE_ONLY;
                }
            });
        }
        if (stderr != null) {
            process.setStream(2, new IFile() {
                @Override
                public String getPath() {
                    return stderr;
                }
                @Override
                public AccessMode getAccessMode() {
                    return AccessMode.WRITE_ONLY;
                }
            });
        }
        IProcessResourceLimits resourceLimits = getResourceLimits();
        if (resourceLimits != null)
            process.setResourceLimits(resourceLimits);
        String currentPath = getCurrentPath();
        if (currentPath != null)
            process.setCurrentPath(currentPath);
        IId ownerId = getOwnerId();
        if (ownerId != null)
            process.setOwnerId(ownerId);
        return process;
    }
}
