/*
 * Copyright 2020 Google Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/syscall.h>

#include "arch/x86/linux/linux.hh"
#include "arch/x86/linux/se_workload.hh"
#include "arch/x86/linux/syscalls.hh"
#include "sim/syscall_emul.hh"

namespace gem5
{

namespace X86ISA
{

SyscallDescTable<EmuLinux::SyscallABI64> EmuLinux::syscallDescs64 = {
    {   0, "read", readFunc<X86Linux64> },
    {   1, "write", writeFunc<X86Linux64> },
    {   2, "open", openFunc<X86Linux64> },
    {   3, "close", closeFunc },
    {   4, "stat", stat64Func<X86Linux64> },
    {   5, "fstat", fstat64Func<X86Linux64> },
    {   6, "lstat", lstat64Func<X86Linux64> },
    {   7, "poll", pollFunc<X86Linux64> },
    {   8, "lseek", lseekFunc },
    {   9, "mmap", mmapFunc<X86Linux64> },
    {  10, "mprotect", ignoreFunc },
    {  11, "munmap", munmapFunc<X86Linux64> },
    {  12, "brk", brkFunc },
    {  13, "rt_sigaction", ignoreWarnOnceFunc },
    {  14, "rt_sigprocmask", ignoreWarnOnceFunc },
    {  15, "rt_sigreturn" },
    {  16, "ioctl", ioctlFunc<X86Linux64> },
    {  17, "pread64", pread64Func<X86Linux64> },
    {  18, "pwrite64", pwrite64Func<X86Linux64> },
    {  19, "readv", readvFunc<X86Linux64> },
    {  20, "writev", writevFunc<X86Linux64> },
    {  21, "access", accessFunc },
    {  22, "pipe", pipeFunc },
    {  23, "select", selectFunc<X86Linux64> },
    {  24, "sched_yield", ignoreWarnOnceFunc },
    {  25, "mremap", mremapFunc<X86Linux64> },
    {  26, "msync" },
    {  27, "mincore" },
    {  28, "madvise", ignoreFunc },
    {  29, "shmget" },
    {  30, "shmat" },
    {  31, "shmctl" },
    {  32, "dup", dupFunc },
    {  33, "dup2", dup2Func },
    {  34, "pause" },
    {  35, "nanosleep", ignoreWarnOnceFunc },
    {  36, "getitimer" },
    {  37, "alarm" },
    {  38, "setitimer" },
    {  39, "getpid", getpidFunc },
    {  40, "sendfile" },
    {  41, "socket", socketFunc<X86Linux64> },
    {  42, "connect", connectFunc },
    {  43, "accept", acceptFunc<X86Linux64> },
    {  44, "sendto", sendtoFunc<X86Linux64> },
    {  45, "recvfrom", recvfromFunc<X86Linux64> },
    {  46, "sendmsg", sendmsgFunc },
    {  47, "recvmsg", recvmsgFunc },
    {  48, "shutdown", shutdownFunc },
    {  49, "bind", bindFunc },
    {  50, "listen", listenFunc },
    {  51, "getsockname", getsocknameFunc },
    {  52, "getpeername", getpeernameFunc },
    {  53, "socketpair", socketpairFunc<X86Linux64> },
    {  54, "setsockopt", setsockoptFunc },
    {  55, "getsockopt", getsockoptFunc },
    {  56, "clone", cloneFunc<X86Linux64> },
    {  57, "fork" },
    {  58, "vfork" },
    {  59, "execve", execveFunc<X86Linux64> },
    {  60, "exit", exitFunc },
    {  61, "wait4", wait4Func<X86Linux64> },
    {  62, "kill" },
    {  63, "uname", unameFunc },
    {  64, "semget" },
    {  65, "semop" },
    {  66, "semctl" },
    {  67, "shmdt" },
    {  68, "msgget" },
    {  69, "msgsnd" },
    {  70, "msgrcv" },
    {  71, "msgctl" },
    {  72, "fcntl", fcntlFunc },
    {  73, "flock" },
    {  74, "fsync" },
    {  75, "fdatasync", ignoreFunc },
    {  76, "truncate", truncateFunc<X86Linux64> },
    {  77, "ftruncate", ftruncateFunc<X86Linux64> },
#if defined(SYS_getdents)
    {  78, "getdents", getdentsFunc },
#else
    {  78, "getdents" },
#endif
    {  79, "getcwd", getcwdFunc },
    {  80, "chdir", chdirFunc },
    {  81, "fchdir" },
    {  82, "rename", renameFunc },
    {  83, "mkdir", mkdirFunc },
    {  84, "rmdir", rmdirFunc },
    {  85, "creat" },
    {  86, "link", linkFunc },
    {  87, "unlink", unlinkFunc },
    {  88, "symlink", symlinkFunc },
    {  89, "readlink", readlinkFunc<X86Linux64> },
    {  90, "chmod", chmodFunc<X86Linux64> },
    {  91, "fchmod", fchmodFunc<X86Linux64> },
    {  92, "chown", chownFunc },
    {  93, "fchown", fchownFunc },
    {  94, "lchown" },
    {  95, "umask", umaskFunc },
    {  96, "gettimeofday", gettimeofdayFunc<X86Linux64> },
    {  97, "getrlimit", getrlimitFunc<X86Linux64> },
    {  98, "getrusage", getrusageFunc<X86Linux64> },
    {  99, "sysinfo", sysinfoFunc<X86Linux64> },
    { 100, "times", timesFunc<X86Linux64> },
    { 101, "ptrace" },
    { 102, "getuid", getuidFunc },
    { 103, "syslog" },
    { 104, "getgid", getgidFunc },
    { 105, "setuid" },
    { 106, "setgid" },
    { 107, "geteuid", geteuidFunc },
    { 108, "getegid", getegidFunc },
    { 109, "setpgid", setpgidFunc },
    { 110, "getppid", getppidFunc },
    { 111, "getpgrp", getpgrpFunc },
    { 112, "setsid" },
    { 113, "setreuid" },
    { 114, "setregid" },
    { 115, "getgroups" },
    { 116, "setgroups" },
    { 117, "setresuid", ignoreFunc },
    { 118, "getresuid" },
    { 119, "setresgid" },
    { 120, "getresgid" },
    { 121, "getpgid" },
    { 122, "setfsuid" },
    { 123, "setfsgid" },
    { 124, "getsid" },
    { 125, "capget" },
    { 126, "capset" },
    { 127, "rt_sigpending" },
    { 128, "rt_sigtimedwait" },
    { 129, "rt_sigqueueinfo" },
    { 130, "rt_sigsuspend" },
    { 131, "sigaltstack", ignoreFunc },
    { 132, "utime" },
    { 133, "mknod", mknodFunc },
    { 134, "uselib" },
    { 135, "personality" },
    { 136, "ustat" },
    { 137, "statfs", statfsFunc<X86Linux64> },
    { 138, "fstatfs", fstatfsFunc<X86Linux64> },
    { 139, "sysfs" },
    { 140, "getpriority" },
    { 141, "setpriority", ignoreFunc },
    { 142, "sched_setparam" },
    { 143, "sched_getparam" },
    { 144, "sched_setscheduler" },
    { 145, "sched_getscheduler" },
    { 146, "sched_get_priority_max" },
    { 147, "sched_get_priority_min" },
    { 148, "sched_rr_get_interval" },
    { 149, "mlock" },
    { 150, "munlock" },
    { 151, "mlockall" },
    { 152, "munlockall" },
    { 153, "vhangup" },
    { 154, "modify_ldt" },
    { 155, "pivot_root" },
    { 156, "_sysctl" },
    { 157, "prctl", ignoreFunc },
    { 158, "arch_prctl", archPrctlFunc },
    { 159, "adjtimex" },
    { 160, "setrlimit", ignoreFunc },
    { 161, "chroot" },
    { 162, "sync" },
    { 163, "acct" },
    { 164, "settimeofday" },
    { 165, "mount" },
    { 166, "umount2" },
    { 167, "swapon" },
    { 168, "swapoff" },
    { 169, "reboot" },
    { 170, "sethostname" },
    { 171, "setdomainname" },
    { 172, "iopl" },
    { 173, "ioperm" },
    { 174, "create_module" },
    { 175, "init_module" },
    { 176, "delete_module" },
    { 177, "get_kernel_syms" },
    { 178, "query_module" },
    { 179, "quotactl" },
    { 180, "nfsservctl" },
    { 181, "getpmsg" },
    { 182, "putpmsg" },
    { 183, "afs_syscall" },
    { 184, "tuxcall" },
    { 185, "security" },
    { 186, "gettid", gettidFunc },
    { 187, "readahead" },
    { 188, "setxattr" },
    { 189, "lsetxattr" },
    { 190, "fsetxattr" },
    { 191, "getxattr" },
    { 192, "lgetxattr" },
    { 193, "fgetxattr" },
    { 194, "listxattr" },
    { 195, "llistxattr" },
    { 196, "flistxattr" },
    { 197, "removexattr" },
    { 198, "lremovexattr" },
    { 199, "fremovexattr" },
    { 200, "tkill" },
    { 201, "time", timeFunc<X86Linux64> },
    { 202, "futex", futexFunc<X86Linux64> },
    { 203, "sched_setaffinity", ignoreFunc },
    { 204, "sched_getaffinity", schedGetaffinityFunc<X86Linux64> },
    { 205, "set_thread_area" },
    { 206, "io_setup" },
    { 207, "io_destroy" },
    { 208, "io_getevents" },
    { 209, "io_submit" },
    { 210, "io_cancel" },
    { 211, "get_thread_area" },
    { 212, "lookup_dcookie" },
    { 213, "epoll_create" },
    { 214, "epoll_ctl_old" },
    { 215, "epoll_wait_old" },
    { 216, "remap_file_pages" },
#if defined(SYS_getdents64)
    { 217, "getdents64", getdents64Func },
#else
    { 217, "getdents64" },
#endif
    { 218, "set_tid_address", setTidAddressFunc },
    { 219, "restart_syscall" },
    { 220, "semtimedop" },
    { 221, "fadvise64", ignoreFunc },
    { 222, "timer_create" },
    { 223, "timer_settime" },
    { 224, "timer_gettime" },
    { 225, "timer_getoverrun" },
    { 226, "timer_delete" },
    { 227, "clock_settime" },
    { 228, "clock_gettime", clock_gettimeFunc<X86Linux64> },
    { 229, "clock_getres", clock_getresFunc<X86Linux64> },
    { 230, "clock_nanosleep" },
    { 231, "exit_group", exitGroupFunc },
    { 232, "epoll_wait" },
    { 233, "epoll_ctl" },
    { 234, "tgkill", tgkillFunc<X86Linux64> },
    { 235, "utimes", utimesFunc<X86Linux64> },
    { 236, "vserver" },
    { 237, "mbind", ignoreFunc },
    { 238, "set_mempolicy" },
    { 239, "get_mempolicy", ignoreFunc },
    { 240, "mq_open" },
    { 241, "mq_unlink" },
    { 242, "mq_timedsend" },
    { 243, "mq_timedreceive" },
    { 244, "mq_notify" },
    { 245, "mq_getsetattr" },
    { 246, "kexec_load" },
    { 247, "waitid" },
    { 248, "add_key" },
    { 249, "request_key" },
    { 250, "keyctl" },
    { 251, "ioprio_set" },
    { 252, "ioprio_get" },
    { 253, "inotify_init" },
    { 254, "inotify_add_watch" },
    { 255, "inotify_rm_watch" },
    { 256, "migrate_pages" },
    { 257, "openat", openatFunc<X86Linux64> },
    { 258, "mkdirat", mkdiratFunc<X86Linux64> },
    { 259, "mknodat", mknodatFunc<X86Linux64> },
    { 260, "fchownat", fchownatFunc<X86Linux64> },
    { 261, "futimesat", futimesatFunc<X86Linux64> },
    { 262, "newfstatat", newfstatatFunc<X86Linux64> },
    { 263, "unlinkat", unlinkatFunc<X86Linux64> },
    { 264, "renameat", renameatFunc<X86Linux64> },
    { 265, "linkat" },
    { 266, "symlinkat" },
    { 267, "readlinkat", readlinkFunc<X86Linux64> },
    { 268, "fchmodat", fchmodatFunc<X86Linux64> },
    { 269, "faccessat", faccessatFunc<X86Linux64> },
    { 270, "pselect6" },
    { 271, "ppoll" },
    { 272, "unshare" },
    { 273, "set_robust_list", ignoreFunc },
    { 274, "get_robust_list" },
    { 275, "splice" },
    { 276, "tee" },
    { 277, "sync_file_range" },
    { 278, "vmsplice" },
    { 279, "move_pages" },
    { 280, "utimensat" },
    { 281, "epoll_pwait" },
    { 282, "signalfd" },
    { 283, "timerfd_create" },
    { 284, "eventfd", eventfdFunc<X86Linux64> },
    { 285, "fallocate", fallocateFunc<X86Linux64> },
    { 286, "timerfd_settime" },
    { 287, "timerfd_gettime" },
    { 288, "accept4" },
    { 289, "signalfd4" },
    { 290, "eventfd2", eventfdFunc<X86Linux64> },
    { 291, "epoll_create1" },
    { 292, "dup3" },
    { 293, "pipe2", pipe2Func },
    { 294, "inotify_init1" },
    { 295, "preadv" },
    { 296, "pwritev" },
    { 297, "rt_tgsigqueueinfo" },
    { 298, "perf_event_open" },
    { 299, "recvmmsg" },
    { 300, "fanotify_init" },
    { 301, "fanotify_mark" },
    { 302, "prlimit64", prlimitFunc<X86Linux64> },
    { 303, "name_to_handle_at" },
    { 304, "open_by_handle_at" },
    { 305, "clock_adjtime" },
    { 306, "syncfs" },
    { 307, "sendmmsg" },
    { 308, "setns" },
    { 309, "getcpu", getcpuFunc },
    { 310, "proess_vm_readv" },
    { 311, "proess_vm_writev" },
    { 312, "kcmp" },
    { 313, "finit_module" },
    { 318, "getrandom", getrandomFunc<X86Linux64> }
};

} // namespace X86ISA
} // namespace gem5
