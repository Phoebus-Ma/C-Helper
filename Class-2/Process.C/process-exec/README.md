### Introduction

Base process test sample code.


### Platform

Current test on Ubuntu Linux.


### Build

```console
make
```


### Run

```console
$ ./process-exec

Parent process: 3830.

----------Test excel-----------
total 104
-rw-r--r-- 1 phoebus phoebus   232 Apr 22 16:12 Makefile
-rw-r--r-- 1 phoebus phoebus  2065 Apr 22 16:14 README.md
-rw-r--r-- 1 phoebus phoebus  2555 Apr 22 16:14 main.c
-rwxr-xr-x 1 phoebus phoebus 21024 Apr 22 16:14 process-exec
-rwxr-xr-x 1 phoebus phoebus 19416 Apr 22 16:14 showenv
-rw-r--r-- 1 phoebus phoebus   259 Apr 22 16:13 showenv.c
Parent process: 3830.

----------Test excelp----------
total 104
-rw-r--r-- 1 phoebus phoebus   232 Apr 22 16:12 Makefile
-rw-r--r-- 1 phoebus phoebus  2065 Apr 22 16:14 README.md
-rw-r--r-- 1 phoebus phoebus  2555 Apr 22 16:14 main.c
-rwxr-xr-x 1 phoebus phoebus 21024 Apr 22 16:14 process-exec
-rwxr-xr-x 1 phoebus phoebus 19416 Apr 22 16:14 showenv
-rw-r--r-- 1 phoebus phoebus   259 Apr 22 16:13 showenv.c
Parent process: 3830.

----------Test excele-----------
TEST1=123
Parent process: 3830.

----------Test excev-----------
total 104
drwxr-xr-x 1 phoebus phoebus  4096 Apr 22 16:14 .
drwxr-xr-x 1 phoebus phoebus  4096 Apr 22 11:03 ..
-rw-r--r-- 1 phoebus phoebus   232 Apr 22 16:12 Makefile
-rw-r--r-- 1 phoebus phoebus  2065 Apr 22 16:14 README.md
-rw-r--r-- 1 phoebus phoebus  2555 Apr 22 16:14 main.c
-rwxr-xr-x 1 phoebus phoebus 21024 Apr 22 16:14 process-exec
-rwxr-xr-x 1 phoebus phoebus 19416 Apr 22 16:14 showenv
-rw-r--r-- 1 phoebus phoebus   259 Apr 22 16:13 showenv.c
Parent process: 3830.

----------Test excevp----------
total 104
drwxr-xr-x 1 phoebus phoebus  4096 Apr 22 16:14 .
drwxr-xr-x 1 phoebus phoebus  4096 Apr 22 11:03 ..
-rw-r--r-- 1 phoebus phoebus   232 Apr 22 16:12 Makefile
-rw-r--r-- 1 phoebus phoebus  2065 Apr 22 16:14 README.md
-rw-r--r-- 1 phoebus phoebus  2555 Apr 22 16:14 main.c
-rwxr-xr-x 1 phoebus phoebus 21024 Apr 22 16:14 process-exec
-rwxr-xr-x 1 phoebus phoebus 19416 Apr 22 16:14 showenv
-rw-r--r-- 1 phoebus phoebus   259 Apr 22 16:13 showenv.c
```
