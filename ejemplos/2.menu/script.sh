#!/bin/sh

case "$1" in
"key-terminal") localectl list-keymaps | awk '$locales=$locales""'  ;;
"key-sistema") cat /etc/locale.gen | grep .UTF-8 | sed '1,4d' | sed 's/\(.\{1\}\)//' ;;
esac
