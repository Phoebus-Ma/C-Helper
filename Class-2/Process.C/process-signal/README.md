### Introduction

Base process signal sample code.


### Platform

Linux.


### Build

```console
make
```


### Run

```console
$ ./process-signal

Parent process start, pid: 517.
Child process start, pid: 518, ppid: 517.
Child process start, pid: 519, ppid: 517.
Nihao.
Hello.
Hello.
Nihao.
Receive SIGXFSZ.
Nihao.
Receive SIGUSR1.
Hello.
Hello.
Nihao.
Parent process end.
Hello.
Receive signal number 12 from pid: 517.
Reveive value: 100.
Receive signal number 10 from pid: 517.
Reveive value: 100.
Nihao.
Child 1 process end.
Child 2 process end.
```
