package yandex.contest.invoker;

/**
 * User: sarum9in
 * Date: 11.07.12
 * Time: 13:21
 */
public enum Signal {
    HUP,
    INT,
    QUIT,
    ILL,
    TRAP,
    ABRT,
    BUS,
    FPE,
    KILL,
    USR1,
    SEGV,
    USR2,
    PIPE,
    ALRM,
    TERM,
    STKFLT,
    CHLD,
    CONT,
    STOP,
    TSTP,
    TTIN,
    TTOU,
    URG,
    XCPU,
    XFSZ,
    VTALRM,
    PROF,
    WINCH,
    POLL,
    PWR,
    SYS;

    public static Signal getSignal(int number) {
        return Signal.values()[number - 1];
    }

    public int getNumber() {
        return this.ordinal() + 1;
    }
}
