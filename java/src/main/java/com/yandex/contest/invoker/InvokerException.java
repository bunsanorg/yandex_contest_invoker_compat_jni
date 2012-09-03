package yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 24.08.12
 * Time: 16:36
 */
public class InvokerException extends Exception {
    public InvokerException() {
    }

    public InvokerException(String message) {
        super(message);
    }

    public InvokerException(String message, Throwable cause) {
        super(message, cause);
    }

    public InvokerException(Throwable cause) {
        super(cause);
    }
}
