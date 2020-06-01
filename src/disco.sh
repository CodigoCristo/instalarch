#!/bin/sh

case "$1" in
"disco") echo "print devices" | parted | grep /dev/ | awk '{if (NR!=1) {print}}' ;;
"key-terminal") localectl list-keymaps | awk '$locales=$locales" - Teclado"' ;;
"key-sistema") cat /etc/locale.gen | grep .UTF-8 | sed '1,4d' | sed 's/\(.\{1\}\)//' ;;
esac

