# README Simple PDF Manipulator

This is a simple program that manipulates PDF files. Written in C/C++ and Perl.

> Developed for the subject of Programming Languages of the Electronic and Computer Engineering course at the Federal University of Rio de Janeiro

## Pre-installation
In order to compile the program, you must have installed:
- `g++` (latest version)
- `perl` (version: 5.34.0+)
- the perl module [CAM::PDF](https://metacpan.org/pod/CAM::PDF)

## Installation (Linux)
In the root directory of the project, execute `make` or `make pdfm` or `make all` to build the executable. For usage, see the following:

```
usage: ./pdfm [options] path...
or: ./pdfm [options] -a BASE DEST
or: ./pdfm [options] -e BEGIN END BASE
or: ./pdfm [options] -d BEGIN END BASE
or: ./pdfm [options] -t BASE
or: ./pdfm [options] -c BASE

options:
    -o <path>           output path
    -a                  Append PDF: appends DEST into BASE
    -e                  Extract from PDF: extract pages BEGIN to END from BASE
    -d                  Delete pages of PDF: delete pages BEGIN to END sequentially from BASE
    -t                  Extract text from PDF: extract all possible from BASE (note: may have no extraction at all)
    -c                  Clean Annotations in PDF: erase all annotations in BASE
```


---

## References

- https://www.cs.ait.ac.th/~on/O/oreilly/perl/advprog/index.htm
- https://metacpan.org/pod/CAM::PDF
- https://perldoc.perl.org/perlintro
