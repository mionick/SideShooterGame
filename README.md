SideShooterGame
===============

First repository, first c++ program, first game in allegro5, first time with visual studio. 

This started out as a lot of firsts, trying to get some practical experience programming things, since it's not really necessary for the courses I take. 


About the Game:
---------------

Side scrolling shooter, like a classic arcade game. 
powerups give points. 
Weapons change with certain powerups, and weapon level increases if the same power up is repeatedly aquired.
Space to fire, arrow keys to move, escape to exit at ANY time.

Space will also advance to the next screen if not playing.
Space does just about everything in the game. 


Things learned so far:
----------------------

All c++ syntax that is used in the files. 
The seperation of header files for declaration and cpp files for definitions.
The components of a game loop. (input, update, render)
The idea of game states, and implementing them with a FSM.
Also looked into implementing them with a stack, but that's not used here.
Using sprites for game objects and animation.

Learned a bit about processing strings in c and c++, but Still foggy on the details and differences. Needs more work.
Dynamically binding function pointers so that a class can use a function that is a method of a seperate class object.
I'm going to guess that is bad practice, but it's cool to know that it's possible.

Difference between references and pointers.


One More Thing:
---------------

The basic game was built just about entirely from these tutorials:
http://fixbyproximity.com/2d-game-development-course/

They were great for starting out. Much has been added by me since then though. 
All different bullets, the concept of powerups, the text entry, and the IO/saving highscores, were 100 percent me. 
The rest has been modified by me quite  a bit, but still resembles those tutorials a lot.
