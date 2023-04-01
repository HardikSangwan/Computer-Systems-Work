======================================================================
CS2110                        Lab 20                       Spring 2019
======================================================================
Read the instructions in the bouncingghost.c file

For this lab, cd into the directory containing bouncingghost.c
and the Makefile. To build and run the emulator, run:

    $ make emu

You should see Trevor the ghost. You can move Trevor around the screen
by pressing any of the arrow keys. Whenever Trevor moves, he leaves his
ghost residue everywhere! This is because the pixels on the screen where
Trevor was are not being reset to the color of the screen background
(black) after he leaves.

Your assignment is to move Trevor cleanly around the screen. How? Call
drawRectangle() on the portion of the screen that Trevor just exited.

When you are done, come show it to us.
