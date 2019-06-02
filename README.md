# Merge-sort-fork
Sorting an array of size 10000 using fork in c

Operating System midterm project

Question 3

Choose one of the following problems and implement it. The aim of both problems is to sort an array with a
fixed size of 10000 using fork. In both problems array is defined as a shared memory.
1. Implement Merge-sort using fork, which means that, at each step, after dividing the array into two
parts, sorting of each part should be done in parallel and using fork.
2. Implement Quick-sort using fork, which means that, after choosing the pivot, sorting of the remaining
two parts should be done in parallel and using fork.
If the specific part of the array had M(or less) number of elements,there’s no need to fork.(Go on as it is said
in the question).
• Run your program for different values of M. Does your run-time increase for the very small values of M?
If yes, explain the reason.
You can use this link to see sample codes of shared memory.
