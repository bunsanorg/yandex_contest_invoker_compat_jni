package yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 05.07.12
 * Time: 16:37
 */
public interface IPipe {
    IStream getInputStream();
    IStream getOutputStream();
}
