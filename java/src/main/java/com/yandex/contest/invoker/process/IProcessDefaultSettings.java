package yandex.contest.invoker.process;

import yandex.contest.invoker.INonPipeStream;
import yandex.contest.invoker.unistd.access.IId;

import java.util.Map;

/**
 * User: sarum9in
 * Date: 13.07.12
 * Time: 17:19
 *
 * Settings will be used for newly created process.
 */
public interface IProcessDefaultSettings {
    IProcessResourceLimits getResourceLimits();
    Map<String, String> getEnvironment();
    String getCurrentPath();
    IId getOwnerId();
    Map<Integer, INonPipeStream> getDescriptors();
}
