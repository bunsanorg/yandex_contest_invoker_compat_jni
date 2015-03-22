package com.yandex.contest.invoker;

import java.time.LocalDateTime;

/**
 * User: sarum9in
 * Date: 03.07.12
 * Time: 19:16
 */
public interface ILog {
    enum Level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    }

    void append(LocalDateTime timestamp, Level level, String position, String message);
}
