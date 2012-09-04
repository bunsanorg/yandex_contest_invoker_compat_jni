#!/bin/sh -e

cd "$(dirname "$0")"

for i in `grep JNIEXPORT -R jni_include | cut -f4 -d' '`
do
    grep -R "$i" src >/dev/null 2>&1 || echo "$i is not defined"
done
