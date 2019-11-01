----

# cmd.h

----

v0.13(2019-11-01)

> ※Please include windows.h and link the winmm.dll library (for MinGW add `-lwinmm`).

##### Table Of Contents

* [ConsoleColour()](#consolecolour)
* [CursorVisibility()](#cursorvisibility)
* [CursorPosition()](#cursorposition)
* [Startup()](#startup)
* [PlayAudio()](#playaudio)
* [PauseAudio()](#pauseaudio)
* [ResumeAudio()](#resumeaudio)
* [StopAudio()](#stopaudio)

----

### ConsoleColour()

Sets console text colour using [SetConsoleTextAttribute()](https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute) from [windows.h](https://docs.microsoft.com/en-gb/windows/console/)

![cmd_colours](cmd_colours.png)

| *int* foreground (default: White) |
| ---------------- |
| 0: Black         |
| 1: Blue          |
| 2: Green         |
| 3: Cyan          |
| 4: Red           |
| 5: Magenta       |
| 6: Yellow        |
| 7: White         |

| *int* background (default: White) |
| ---------------- |
| 0: Black         |
| 1: Blue          |
| 2: Green         |
| 3: Cyan          |
| 4: Red           |
| 5: Magenta       |
| 6: Yellow        |
| 7: White         |

| *int* foreground_intensity (default: False) |
| -------------------------- |
| 0: False                   |
| 1: True                    |

| *int* background_intensity (default: False) |
| -------------------------- |
| 0: False                   |
| 1: True                    |



----

### CursorVisibility()

Changes console cursor visibility using [SetConsoleCursorInfo()](https://docs.microsoft.com/en-us/windows/console/setconsolecursorinfo) from [windows.h](https://docs.microsoft.com/en-gb/windows/console/)

| *int* visibility (default: Visible) |
| -------------------------- |
| 0: invisible                |
| 1: visible          |

----

### CursorPosition()

Changes cursor position using [SetConsoleCursorPosition()](https://docs.microsoft.com/en-us/windows/console/setconsolecursorposition) [windows.h](https://docs.microsoft.com/en-gb/windows/console/)

| *int* x (default: 0)       |
| -------------- |
| x coord (>= 0) |

| *int* y (default: 0)      |
| -------------- |
| y coord (>= 0) |

----

### Startup()

Changes the screen size, hides the cursor, sets the console encoding to utf-8 and sets the console title

| *int* height (default: 0)      |
| -------------- |
| window height (>= 0) |

| *int* width (default: 0)      |
| -------------- |
| window width (>= 0) |

| *char* title  |
| ------------- |
| console title |

----

### PlayAudio()

Uses [mciSendString()](https://docs.microsoft.com/en-us/previousversions/dd757161(v%3Dvs.85)) to play sounds.

| *char* path             |
| ----------------------- |
| path to audio file(mp3) |

| *int* repeat (default: 0) |
| ------------ |
| 0: false     |
| 1: true      |

----

### PauseAudio()

Uses [mciSendString()](https://docs.microsoft.com/en-us/previousversions/dd757161(v%3Dvs.85)) to pause sounds.

| *char* path             |
| ----------------------- |
| path to audio file(mp3) |

----

### ResumeAudio()

Uses [mciSendString()](https://docs.microsoft.com/en-us/previousversions/dd757161(v%3Dvs.85)) to resume paused sounds.

| *char* path             |
| ----------------------- |
| path to audio file(mp3) |

----

### StopAudio()

Uses [mciSendString()](https://docs.microsoft.com/en-us/previousversions/dd757161(v%3Dvs.85)) to stop paused sounds.

| *char* path             |
| ----------------------- |
| path to audio file(mp3) |