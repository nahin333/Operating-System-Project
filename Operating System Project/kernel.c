#include "include/screen.h"
#include "include/kb.h"
#include "include/string.h"
#include "include/substr.h"

int32 strToInt(string str, uint8 len) 
{ 
    int32 res = 0;
	uint16 i = 0;
	if (str[0] == '-') i = 1;
    for (i; i < len && str[i] != '\0'; ++i) 
        res = res*10 + str[i] - '0'; 
    if (str[0] == '-')
		return -res;
	else
		return res;
}

kmain()
{
       logout:
       clearScreen();
	   
       print("Welcome to my operating system!\nUser login\n");
	   string username = "nahin";
	   string password = "123";
	   
	   string inp = 0;
	   while (1) {
		   uint8 uOK = 0, pOK = 0;
		   
		   print("username: ");
		   inp = readStr();
		   if (strEql(inp, username)) uOK = 1;
		   
		   print("password: ");
		   inp = readStr();
		   if (strEql(inp, password)) pOK = 1;
		   
		   if (uOK && pOK) {
			   print("Login Done!\n");
			   break;
		   }
		   print("Wrong info. Try again\n");
	   }
	   
       while (1)
       {
			print("nahin> ");
			inp = readStr();
			if(strEql(inp,"cmd"))
			{
					print("You are allready in cmd\n");
			}
			else if(strEql(inp,"clear"))
			{
					clearScreen();
			}
                        else if(strEql(inp,"logout"))
			{
					clearScreen();
                                        goto logout;
			}
			else if(strEql(inp,"substr"))
			{
				print("Enter string: ");
				inp = readStr();
				screen_substr(inp);
			}
			else if(strEql(inp,"strlen"))
			{
				print("Enter string: ");
				inp = readStr();
				print("The length of string is: ");
				printnum(strlength(inp));
				print("\n");
			}
			else if(strEql(inp,"clearline"))
			{
				print("Enter line no: ");
				inp = readStr();
				uint8 lineno = (uint8) strToInt(inp, 999);
				if (lineno < 1 || lineno > cursorY) {
					print("Line no is out of screen\n");
					continue;
				}
				clearLine(lineno-1, lineno);
				uint8 i,j;
+				string vidmem = (string)0xb8000; 
				for (i = lineno-1 +1; i<=cursorY; i++) {
					for (j = 0; j<sw; j++) {
						vidmem[((i-1)*sw+j)*2] = vidmem[(i*sw+j)*2];
						vidmem[((i-1)*sw+j)*2+1] = vidmem[(i*sw+j)*2+1];
					}
				}
				cursorY--;
				updateCursor();
			}
			else if(strEql(inp,"shutdown"))
			{
					print("Turning off my OS!\n");
					break;
			}
                        else if(strEql(inp,"upc"))
                        {
                                cursorX=8; 
                                cursorY=8;
                                updateCursor();
                        }

			else
			{
					print("Bad command!\n");
			}
       }
}
