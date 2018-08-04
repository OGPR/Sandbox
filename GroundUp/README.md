# GroundUp
Building a game in C from the ground up attempting to use only
the standard C library, however certain OS specific and other libraries may need to be used.

A specific example may explain best the goals and approach of this project.
Say I want to launch a new window for our game. I want to launch it "natively" in the current OS, that is our application is not a GUI.

I could start of like so:
```
int main()
{
  launchWindow();
  return 0;
}
```
Now I look to define `launchWindow()`. How would be do this on linux? Well in that case I have the X windowing system for example, and there exists a C library (Xlib) to communicate with it.

One could implement what Xlib does, and this certainly would be fun and educational, however that is an example of what is _not_
the goal of this project. I would use Xlib. However I have gained knowledge and an appreciation of why such a library exists, and how it helps. And on topics surrounding it, like other windowing systems like Wayland.

## Why?
WSIWYG tools and game frameworks and libraries are great,
and this is not an attempt to replace them or deny their usefulness or even necessity.
However something I believe strongly in understanding things from first principles,
as then one is much more able to solve problems and has knowledge at a deeper level. 
An appreciation of what the frameworks and libraries do and make easier is also gained, and this can also lead to new ideas,
or suggested improvements to the frameworks and libraries.

## Why C?
In the future C++ (or maybe Java, Python) will probably be the language of development here (although I are keen to explore other languages and web based games too). The use of C in this case is for simplicity - although simplicity should not be confused with ease. For the goals of this work, even C++ is too "heavy" - using C will ideally make things more transparent. I also love C, so maybe that has something to do with it!

## Resources
Although a different goal, there is overlap with the goals of Casey Muratori's awesome Handmade Hero project, and that was and remains an inspiration. Be sure to checkout the youtube channel (Handmade Hero), and watch the announcement trailer, its good stuff! 

## Set up
Intially development will be in GNU/Linux.
The compiler used is gcc 7.2.0.
The OS is Ubuntu 16.10.
The desktop enviroment is the i3 tiling window manager (twm).
