Name: Jacob Antepli
Username: Jaantepli

Assignment: Dragonfly Egg

How to run tests:

In the test.cpp file inside of the main function are several tests that have been commented out. Each function tests every method a class contains and print to the log file (Found in Debug/dragonfly.log) if anything were to go wrong. Notable exception of this being in the baseManager class as it was written prior to the log manager. 

To run a test simply uncomment a function and run. There are a few things to note though, firstly the testGameManager and testEventHandler are better to run seperatly due to the amount of prints to the console. The other files however can be run in tandum.



Other Notes:

I used the logmanager with the optional verbosity function to help keep track of any bugs that could occur. The current verbosity is set to 1, however if one wishes to see more detailed log information it can be reduced to 0 in the construcer of the log manager or by calling LM.setverbosity in the main function.