### Introduction

Binary tree sample code.


### Platform

Ubuntu Linux.


### Build

```bash
make
```


### Run

```base
The string:
ABD##E##CF##G##
is:
A->B(l)->D(l)
A->B(l)->E(r)
A->C(r)->F(l)
A->C(r)->G(r)
```

```console
$ ./bintree-test

Input data:
ABD##E##CF##G##
Preorder traversal.
A B D E C F G
Inorder traversal.
D B E A F C G
Postorder traversal.
D E B F G C A
```
