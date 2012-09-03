package yandex.contest.invoker.filesystem;

/**
 * User: sarum9in
 * Date: 03.08.12
 * Time: 23:33
 */
public interface IRegularFile extends IFile {
    /**
     * @return null if not specified
     */
    String getSource();
}
