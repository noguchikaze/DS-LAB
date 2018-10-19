In HW2, we input a case with the format below

ex. case1

7
6
2 2 2 2 2 2 2
2 0 S 0 0 0	2
2 0	0 0	0 0	2
2 0	0 0	0 2	2
2 0	2 2	0 E	2
2 2 2 2 2 2 2

which includes the width and the length of the maze
and our input should be like

./HW2.o case1 [file_out_method1] [file_out_method2]

We put the test case in argv[1] and our code implement 2 methods
[file_out_method1] -> method 1 output
[file_out_method2] -> method 2 output

Method 1 is the "trial and error", which makes the mouse start trying from EAST
And try other ways (South, West, North) clockwise.

Method 2 is the "shortest way to go", and this implies that the path it goes though will be different from the case that TA gives us.
To check if the steps is the correct number, please write a cpp file and count it yourself
----------------------------------------------------------------------------------------------
Test cases may include '\t' or ' ', and that's why I use "char" to read file
And what's more, I failed in case4 before I canceled marking the back_track path in method 1 into 0

case4 does sucks, I failed getting 100 on HW2
-----------------------------------------------------------------------------------------------
