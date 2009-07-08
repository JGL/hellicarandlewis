08/07/2009

HellicarAndLewis

This application is to be used with the 006 version (http://openframeworks.cc/download) of OpenFrameworks.

This application was created for the FutureArtefact installation at London's Selfridges, on Regent Street. Designed to be used with an HD LCD screen, running at 720p, with a rotated aspect.

Requires the Glut OSX Fullscreen fix from Zachary Lieberman:

"I was googling with a forum posting and discovered this:

http://boinc.berkeley.edu/svn/branches/boinc_core_release_6_2/api/macglutfix.m

plugging it in and altering leads to mac fullscreen apps that crash
being closable (ie, can alt tab and get to xcode / stop).  For me,
this is the biggest OSX annoyance (fullscreen crashes making you have
to reboot or magically navigate to xcode).  The code gets the window,
and could allow for alot of mac specific stuff (like the windows
setWindowLong() type stuff).  The picture is of a fullscreen empty
example that I tested with, after alt tabbing and bringing up xcode.
prior to alt tabbing, it just looks a normal OF window.

I've upload it here:
http://www.openframeworks.cc/files/glutMacLevelChange.zip

(it requires the appKit framework added to core/frameworks)....

thought mac folks might appreciate, and it could be interesting to
experiment more.  you can see the changes I made by comparing it the
macglutfix above.  I'm lowering the window (as opposed to raising it).

take care!
zach"

OS X version tested only.

us@hellicarandlewis.com

Enjoy.