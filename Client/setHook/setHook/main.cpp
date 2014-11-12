#pragma once

// link with Ws2_32.lib : resolve unresolved symbol
#pragma comment(lib, "Ws2_32.lib")

#include "sSocket.h"
#include "Handling.h"
#include "sJson.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

#include <windows.h>
#include <ctime>

#include <iostream>
#include <fstream>

#include <openssl/md5.h>  


int	main()
{
	Handling handling("192.168.48.128", "4321");
	if (handling.isConnected() == false)
	{
		system("PAUSE");
		return (1);
	}
	std::cout << "send : salut " << std::endl;
//	handling.sSend("salut\n");
	handling.sendStartUp("Master-Guitou", "Debian-computer", "ALL");
	handling.sendStartUp();

//	std::string time = json.getTime();
//	std::cout << time << std::endl;

	/* Exemple for work JSON */
	/*
	handling.putActiveProcess("D:\second json", "second json");
	handling.putKeyboard("blabla", "06/11/14", "06/11/14");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putMouseMove(1, 2, 3, 4, "05021990");
	handling.putMouseMove(5, 6, 7, 8, "05021990");
	handling.putMouseClick(21, 42, "left", "05021990");
	handling.putMouseClick(42, 21, "right", "05021990");

	handling.putActiveProcess("D:\google", "Google");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putMouseMove(1, 2, 3, 4, "05021990");
	handling.putMouseMove(5, 6, 7, 8, "05021990");
	handling.putMouseClick(21, 42, "left", "05021990");
	handling.putMouseClick(42, 21, "Complet", "Complet");

	handling.sendPackets();
	*/
	/*
	handling.putActiveProcess("D:\second json", "second json");
	handling.putKeyboard("blabla", "06/11/14", "06/11/14");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putMouseMove(1, 2, 3, 4, "05021990");
	handling.putMouseMove(5, 6, 7, 8, "05021990");
	handling.putMouseClick(21, 42, "left", "05021990");
	handling.putMouseClick(42, 21, "right", "05021990");

	handling.putActiveProcess("D:\google", "Google");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putKeyboard("blabla", "05021990", "05021990");
	handling.putMouseMove(1, 2, 3, 4, "05021990");
	handling.putMouseMove(5, 6, 7, 8, "05021990");
	handling.putMouseClick(21, 42, "left", "05021990");
	handling.putMouseClick(42, 21, "Complet", "Complet");

	handling.sendPackets();
	*/
	/*
	std::cout << "get : " << std::endl <<
	json.getBufferActiveProcessFull()
	<< std::endl;
	*/
	/*
	std::ofstream myfile;
	myfile.open("./PutOut.txt");
	myfile << json.getBufferActiveProcessFull() << std::endl;
	myfile.close();
	*/



	/* - -- --- ---- --- -- - */
	std::cout << "Salut :D\n tout est bien qui finit bien !" << std::endl;
	system("PAUSE");
}
