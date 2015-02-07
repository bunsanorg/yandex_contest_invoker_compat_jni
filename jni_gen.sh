#!/bin/bash -e

cd "$(dirname "$0")"

root="$PWD"
java="$root/java/src/main/java"
class="$root/java/target/classes"
include="$root/jni_include"

getclasses()
(
    cd "$java" && find com/yandex/contest/invoker/impl -type f -name '*.java' | \
        sed -r 's|\.java$||' | tr '/' '.' | \
        fgrep -v 'com.yandex.contest.invoker.impl.IHandle'
)

getclassarray()
{
    getclasses | tr '.' '/' | awk 'BEGIN {print "{" } { print "\t\"" $0 "\"," } END { print "}" }'
}

updatelist()
{
    cat >"$1" <<EOF

    const char *com_yandex_contest_invoker_impl_classNames[] =
    $(getclassarray);

    const unsigned com_yandex_contest_invoker_impl_classNamesSize = $(getclasses | wc -l);

EOF
}

updateheaders()
{
    local builded="$include/builded"
    local list="$include/com_yandex_contest_invoker_impl_PackageInitClasses.h"
    if [[ -f $builded ]]
    then
        echo -n "Previous build was terminated, cleaning..."
        rm -r "$include"
        echo "OK"
    fi
    mkdir -p "$include"
    echo "$(basename "$builded")" >"$builded"
    echo "$(basename "$list")" >>"$builded"
    local changed="0"
    if [[ ! -e $list ]]
    then
        changed="1"
    fi
    for i in `getclasses`
    do
        local srcfile="$java/$(echo "$i" | tr '.' '/').java"
        local classfile="$class/$(echo "$i" | tr '.' '/').class"
        local headerfile="$include/$(echo "$i" | tr '.' '_').h"
        if [[ $headerfile -ot $classfile ]]
        then
            changed="1"
            echo -n "Building \"$i\"..."
            javah -classpath "$class" -d "$include" "$i"
            echo "OK"
        fi
        echo "$(basename "$headerfile")" >>"$builded"
    done
    for i in `ls "$include"`
    do
        local fname="$(basename "$i")"
        if ! fgrep "$fname" "$builded" >/dev/null 2>&1
        then
            changed="1"
            echo -n "File \"$fname\" was not builded, removing..."
            rm "$include/$i"
            echo "OK"
        fi
    done
    if [[ $changed = 1 ]]
    then
        echo -n "Updating class list..."
        updatelist "$list"
        echo "OK"
    fi
    echo "Build completed."
    rm "$builded"
}

updateheaders
