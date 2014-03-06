SideShooterGame
===============

First repository, first c++ program, first game in allegro5, first time with visual studio. 

This started out as a lot of firsts, trying to get some practical experience programming things, since it's not really necessary for the courses I take. 

To Run/play:
------------
Since I built the game on allegro5 gaming library, it requires the successful install of the allegro5 components, which is not that bad! Download from the website and move them to a place where your compiler can see them I think? I used visual studio and copy+pasted the files into the appropraite folders in "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC"

That is probably not the best way to install since, I cannot easily remove the allegro files, but it works and should be harmeless. 

After that the only special tweaking I did is to include allegro-5.0.10-monolith-md-debug.lib in 
visual studio-> project properies -> Configuration -> Linker -> Input -> Additional dependancies

Probably not the same as any other version of visual studio, but if youa re using 2013 that will do it.

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

All c++ syntax that is use din the files. 
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

The basic game was built jsut about entirely from these tutorials:
http://fixbyproximity.com/2d-game-development-course/

They were great for starting out. Much has been added by me since then though. 
All different bullets, the concept of powerups, the text entry, and the IO/saving highscores, were 100 percent me. 
The rest has been modified by me quite  a bit, but still resembles those tutorials a lot.
