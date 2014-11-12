Keylogger
=========

C++ Keylogger for windows 7. Works with DLL injection on explorer.exe

Prerequisites
=============

Server
------

1. Mysql
2. Boost
3. OpenSSL

Client
------

1. Visual Studio
2. OpenSSL

How does it works ?
===================

Server
------

1. Compile the server in Keylogger/Server - make
2. Execute it - ./server
3. Enter your server port and your sql password

Client
------

1. Link Visual Studio and OpenSSL
2. Compile Keylogger/Client/setHook in 64bits - F7
3. Compile Keylogger/Client/injector in 64bits - F7
4. Move MainDll.dll, injector.exe and ca.pem in the same directory
5. Execute injector.exe

Clean the virus
---------------

1. Compile Keylogger/cleaner in 64bits - F7
2. Execute cleaner.exe
