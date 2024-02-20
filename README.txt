Name: Jacob Antepli
Username: Jaantepli

Assignment: Dragonfly

IMPORTANT NOTE:
I set it up so that my project does need the SFML 2.6 directory to run, there is a small test for it you can do in the test.cpp file.

How to run tests:

In the test.cpp file inside of the main function are several tests that have been commented out. Each function tests every method a class contains and print to the log file (Found in Debug/dragonfly.log) if anything were to go wrong. Many tests also print to the console for immediate notice 

To run a test simply uncomment a function and run. There are a few things to note though, some test should be run alone and are labeled with this warning due to either large amount of prints to the console or messing with other tests if run at the same time. The other files however can be run in tandum.

Additionally the collision test can be changed by going to Saucer.cpp and commenting and uncommenting whichever collision type you want to see.

Other Notes:

I used the logmanager with the optional verbosity function to help keep track of any bugs that could occur. The current verbosity is set to 1, however if one wishes to see more detailed log information it can be reduced to 0 in the construcer of the log manager or by calling LM.setverbosity in the main function.