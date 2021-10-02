$SRC_PATH = "C:\Users\tobita\repos\lowlevel\assembly"
$SRC_PATH2 = "C:\Users\tobita\repos\lowlevel\docus"
$DST_PATH = "C:\Users\tobita\docker_mount"

copy-item $SRC_PATH -destination $DST_PATH -Recurse -Force
copy-item $SRC_PATH2 -destination $DST_PATH -Recurse -Force