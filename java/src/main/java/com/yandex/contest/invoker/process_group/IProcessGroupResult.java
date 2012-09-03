package com.yandex.contest.invoker.process_group;

/**
 * User: sarum9in
 * Date: 04.07.12
 * Time: 12:00
 */
public interface IProcessGroupResult {
    enum CompletionStatus {
        OK,
        ABNORMAL_EXIT,
        REAL_TIME_LIMIT_EXCEEDED,
        STOPPED
    }
    CompletionStatus getCompletionStatus();
    IProcessGroupResourceUsage getResourceUsage();
}
