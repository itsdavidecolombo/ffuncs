# ffuncs

In this repository you can find useful scripts for file comparison and file pattern matching.

'fcomp.c' takes 3 argument in the following order: name of the program, f1, f2 where f1 and f2 are file in the same directory of the source file.

Then, the program opens the two files, and if no error has occurred it read one line at a time from both files and compare them.
The program stops when it found the first line that is different.


'ffind.c' takes at least two arguments: the name and a pattern string. You can also pass additional file names.
In the version with only two arguments, the program reads input from command line and search for a match.
In the version with one or more file names, the program open a file one-by-one and search a match with the pattern line-by-line.

Davide
