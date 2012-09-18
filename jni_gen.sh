#!/bin/sh -e

cd "$(dirname "$0")"

root="$PWD"
java="$root/java/src/main/java"
class="$root/java/target/classes"
include="$root/jni_include"

getclasses()
(
    cd "$java" && find com/yandex/contest/invoker/impl -type f -name '*.java' | sed -r 's|\.java$||' | tr '/' '.' | \
        fgrep -v 'com.yandex.contest.invoker.impl.IHandle'
)

getclassarray()
{
    getclasses | tr '.' '/' | awk 'BEGIN {print "{" } { print "\t\"" $0 "\"," } END { print "}" }'
}

rm -f "$include/"*

getclasses | (cd "$java" && xargs javah -classpath "$class" -d "$include")

cat >"$include/com_yandex_contest_invoker_impl_PackageInitClasses.h" <<EOF

const char *com_yandex_contest_invoker_impl_classNames[] =
$(getclassarray);

const unsigned com_yandex_contest_invoker_impl_classNamesSize = $(getclasses | wc -l);

EOF
