### Introduction

Base process vfork sample code.


### Platform

Linux.


### Build

```console
make
```


### Run

```console
$ ./process-vfork

Child process start, pid: 4916, ppid: 4915.
Hello from child process.
Hello from child process.
Hello from child process.
Hello from child process.
Hello from child process.
Child process end.
Parent process start, pid: 4915, child pid: 4916.
This parent process.
This parent process.
This parent process.
This parent process.
This parent process.
Parent process end.
```
