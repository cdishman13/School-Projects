Part 4 Code is in play.c
Part 3 Code is in win.c
Part 2 Code is in solitare.c
Part 1 Code is in check.c

This program takes a input text file that has the rules for for a solitare game.
The program will check for sections "RULES:", "FOUNDATIONS:", "TABLEAU:", "STOCK:",
then it will see if the game is in a winnable state.

In the RULES: section the program will check for either "turn 1" or "turn 3", 
it will also check for "unlimited", or "limit N" where N can be numbers 0-9.

In the FOUNDATIONS: section the program will check to see if foundations have been entered correctly

In the TABLEAU: section the program will make sure the cards are valid and will count the number of uncovered cards.
There is seven different columns for the program to check. Covered and uncovered cards are seperated by '|'.
The program will also check if the columns are valid. 

In the STOCK: section the program will make sure that all the cards are valid. It will also count the number of 
stock and waste cards. Stock and waste cards are seperated by '|'

To check if the game is winnable it makes use of the -m and -v switches.
Once the program is done finding a winning or a losing game the program will 
output either the winning moves or tell the user that the game was unwinnable in the amount of moves given.


Both -f and -s switches are implemented and the game can be played either way.
You are also able to undo the last move and undo serval moves. 