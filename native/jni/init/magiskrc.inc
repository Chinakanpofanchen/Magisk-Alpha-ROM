#include <magisk.hpp>
#include <selinux.hpp>

#define quote(s) #s
#define str(s) quote(s)

constexpr char MAGISK_RC[] =
"\n"

"on post-fs-data\n"
"    start logd\n"
"    rm " UNBLOCKFILE "\n"
"    start %2$s\n"
"    wait " UNBLOCKFILE " " str(POST_FS_DATA_WAIT_TIME) "\n"
"    rm " UNBLOCKFILE "\n"
"\n"

"service %2$s %1$s/magisk --post-fs-data\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service %3$s %1$s/magisk --service\n"
"    class late_start\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"on property:sys.boot_completed=1\n"
"    start %4$s\n"
"\n"

"service %4$s %1$s/magisk --boot-complete\n"
"    user root\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service kpfc_post /system/bin/su -c /system/bin/sh /cust/post-fs.sh\n"
"    user root\n"
"    class main\n"
"    disabled\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service kpfc_data /system/bin/su -c /system/bin/sh /cust/post-fs-data.sh\n"
"    user root\n"
"    class main\n"
"    disabled\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"service kpfc_boot /system/bin/su -c /system/bin/sh /cust/boot.sh\n"
"    user root\n"
"    class main\n"
"    disabled\n"
"    seclabel u:r:" SEPOL_PROC_DOMAIN ":s0\n"
"    oneshot\n"
"\n"

"on post-fs\n"
"    start kpfc_post\n"
"\n"

"on post-fs-data\n"
"    start kpfc_data\n"
"\n"

"on boot\n"
"    start kpfc_boot\n"
"\n"
;
