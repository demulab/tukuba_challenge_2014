#!/bin/sh

check_root() {
    if [ `id -u` != 0 ]; then
    echo ""
    echo "スーパーユーザー権限で実行してください"
    echo ""
    exit 1
    fi
}

reload_command() {
    modprobe ftdi_sio vendor=0x1115 product=0x0008
    echo "1115 0008" > /sys/bus/usb-serial/drivers/ftdi_sio/new_id
    echo "ドライバのロードが完了しました"
}


check_root

reload_command
