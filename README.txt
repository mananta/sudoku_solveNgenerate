Note this is sudoku+, not simple sudoku i.e. we are trying to assign numbers in such a way that numbers are not repeated accross diagonals as well.
For normal sudoku go to the sol.c file and comment the diagonal repeatition portion. Do the same for gen.c as well and bingo!!

Problem 1: Sudoku+ solver
Code : "sol.c"
Description :
1)Input is given through "sudoku_in.txt"; SHOULD BE PRESENT THERE IN THE SAME DIRECTORY OF "sol.c" BEFORE COMPILATION.
2)The SAT encodings in the DIMACS representation is generated in "dimac.txt".
3)The output of SAT solver is stored in "sat_output.txt".
4)The SAT output is analysed to print final solution in "final.txt".
5)THE PROGRAM IS CAPABLE OF GENERATING ALL POSSIBLE SOLUTIONS OF THE GIVEN INPUT. By default, maximum 100 solution is generated.
To generate all possible solutions substitute the last for loop statement by "while(1)" 
and to get only one solution comment out the entire section of last for loop.
6)Compile by the command "gcc sol.c" to get the executable "a.out".
7)Use "./a.out" to get output in "final.txt".



Problem 2: Sudoku+ puzzle generator
code: "gen.c"
Description:
1)To generate a sample sudoku+ problem we take a solution to start with. How to get the solution? Very easy! Insert something very 
trivial like :
1 . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
. . . . . . . . .
in the "input.txt" file of problem 1. We will get many solutions of this in "final.txt". Take any one of it and proceed.
2)Here, we are scanning only the first solution from "final.txt". But, we can use anything random.
3)Now at each step we pop up the value from a random cell and check whether the solution is unique or not. Obviously, the solution 
will be unique at first few popping operation. Whenever the solution becomes multiple we take that particular situation. Now, another
operation starts. We start checking if it is possible to eliminate non-zero values randomly as much as possible to get a minimal 
solution and the algo works!!
4)The final RANDOM MINIMAL puzzle is stored in "sample.txt".
5)Compile by the command "gcc -o b.out gen.c" to get the executable "b.out".
6)Use "./b.out" to get output in "sample.txt".
7)BEFORE EXECUTING PROBLEM 2 PROBLEM 1 MUST BE EXECUTED (Nothing to worry again! Use a trivial,very trivial input as above!).
8)The solution is be minimal, i.e. it is not be possible to remove any of the filled entries without allowing
multiple solutions.
AND FINALLY THE SAT EXECUTABLE USED IN THIS PROGRAM IS "MiniSat_v1.14_linux" WHICH IS NOT INCLUDED IN THE PACKAGE AS PER THE INSTRUCTIONS.
9) Every invocation of the program generates a different puzzle.

AND FINALLY THE SAT EXECUTABLE USED IN THIS PROGRAM IS "MiniSat_v1.14_linux" WHICH IS NOT INCLUDED AS PER THE INSTRUCTIONS.

