# cmd.h

A simple header file that makes it easier to develop Windows console applications with c.

You can easily change console window properties, play sounds, and display images.

## Compiling

Include cmd.h with your project and link winmm when compiling.

At the top of your c file:

```c
#include "cmd.h"
```

When compiling (MinGW):

```
gcc [file-name].c -o [file-name] -lwinmm
```

## Usage 

 *Please refer to the [Wiki](https://github.com/k390983/cmd.h/wiki).* 

## Examples

<details><summary>Play sound</summary>
main.c:

```c
#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"
int main(void)
{
    PlayAudio("sound.mp3", 0);
    PauseAudio("sound.mp3");
    ResumeAudio("sound.mp3");
    StopAudio("sound.mp3");
}

```
</details>


<details><summary>Bouncing ball</summary>
main.c:

```
#include <stdlib.h>
#include <stdio.h>
#include "cmd.h"

int main(void)
{
	int x = 0;
    int y = 0;
	int WIDTH = 50;
	int HEIGHT = 30;
	int xDirection = 0;
	int yDirection = 0;
	int *player = LoadTexture("texture");;

	Startup((WIDTH) * 2, HEIGHT, "test");
	InitCanvas(WIDTH, HEIGHT, 71);
	
	while(1)
	{
	    //Collisions
		if(x == 0)
		{
			xDirection = 0;
		}
		if(x + player[0] == WIDTH)
		{
			xDirection = 1;
		}
		if(y == 0)
		{
			yDirection = 0;
		}
		if(y + player[1] == HEIGHT)
		{
			yDirection = 1;
		}
	
		//Movement
		if(xDirection == 0)
		{
			x++;
		}
		else
		{
			x--;
		}
		if(yDirection == 0)
		{
			y++;
		}
		else
		{
			y--;
		}
	
		CleanCanvas(71);
		Draw(player, x, y);
		Display();
	
		Sleep(10);
	
	}

}
```

texture:

```c
8, 8
99 99 41 41 41 41 99 99 
99 41 41 41 41 41 41 99 
41 41 41 41 41 41 41 41 
41 41 41 41 41 41 41 40 
41 41 41 41 41 41 40 40 
40 40 41 41 40 40 40 40 
99 40 40 40 40 40 40 99 
99 99 40 40 40 40 99 99 
```
</details>

## Contributing

1. Fork it (<https://github.com/k390983/cmd.h/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request

----

k390983(https://github.com/k390983) - k2l8m8n1@gmail.com
Distributed under the MIT license. See `LICENSE` for more information. 