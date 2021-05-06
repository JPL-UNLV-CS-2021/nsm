# Instructions for judges
## _Must be run on a windows 10 Machine_
QSM is a state design pattern for embedded flight systems in the modern era.

- No Recursion
- No templating
- No Dynamic Memory
- Runtime polymorphism
- Abstract + Concrete Inheritance
- Heirarchical representation in code

## Features

- Import a QM file and watch it magically convert to a running state machine.
- Run heirarchical state machines with a virtually unlimited nesting depth.
- Create events in a simulated environment to see how the machine operates in a live scenerio.
- Change any aspect to the original statemachine design, and have a new machine in one command.

## Installation for Auto Coder

QSM is a tool to be used in conjuction with other tools  by JPL engineers in a development environment.
As such to test it we must first spend time setting up a similiar environment..

# 1. [Install QM](https://www.state-machine.com/)

- Download the installer

![p1](https://i.ibb.co/CV0Sxw3/p1.png)

![p2](https://i.ibb.co/DMcWzNr/p2.png)

- Run the installer

![ap1](https://i.ibb.co/8PTNZHq/ap1.png)

- Accept User Agreement

![ap2](https://i.ibb.co/tCVrDM3/ap2.png)

- Leave install location as default

![ap3](https://i.ibb.co/Bq0kqy3/ap3.png)

- ** MAKE SURE YOU SELECT THE EXACT SAME COMPONENTS **

![ap4](https://i.ibb.co/zHXM7S9/ap4.png)

- Finish the installation

![ap5](https://i.ibb.co/yVYPLwW/ap5.png)

# 2. Determine what kind of architecture your operating system is currently running. 32 bit or 64 bit

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;![ARCH32OR64](https://i.ibb.co/MBsdgvH/image.png)
	
# 3. [Install CMAKE](https://cmake.org/download/)
- Scroll to "Binary distributions:" (under "Source Distributions")
- If you have a 32 bit version of Windows 10, download "Windows i386 Installer"
- If you have a 64 bit version of Windows 10, download "Windows x64 Installer"

![p3](https://i.ibb.co/sq1JHWw/p3.png)
- Run the installer
	
![p4](https://i.ibb.co/SvsgyDG/p4.png)
- Accept User Agreement
	
![p5](https://i.ibb.co/PM82YNk/p5.png)
- On the Install Options page
	- SELECT "Add CMake to the system PATH for all users"
	- Next
	
![p6](https://i.ibb.co/yWKskwR/p6.png)
- Choose your installation location. The default is fine.
	
![p7](https://i.ibb.co/4fBSTKM/p7.png)
- Proceed to install!
	
![p8](https://i.ibb.co/dQwN86V/p8.png)

# 4. Double check the installation

- Select the Start button
 	
![p9](https://i.ibb.co/72PnzX5/p9.png)
- Type "Command Prompt" and launch the command prompt
    
![p10](https://i.ibb.co/GsqBF36/p10.png)
- In the command prompt type "python"
  There should be version 3.X.X.
  Use quit() or Ctrl-Z plus Return to exit
    
![p11](https://i.ibb.co/Tk6mQ55/p12.png)
- In the command prompt type "cmake"
  You should see a usage response.
    
 ![p12](https://i.ibb.co/pdTXWJc/p13.png)
        
# 5. [Download the project.](https://github.com/JPL-UNLV-CS-2021/qsm)

- Click "Code"

![p13](https://i.ibb.co/9W6mKTd/p14.png)
- Click "Download ZIP"

![p14](https://i.ibb.co/sjwzmJw/p15.png)
- Extract the ZIP file in your downloads folder

![p15](https://i.ibb.co/Z60TXx7/p16.png)

![p16](https://i.ibb.co/4mccg0F/p17.png)

# 6. Go back to the command line and run the following commands
```sh 
cd Downloads\qsm-main\qsm-main\src\autocoder
python -m venv venv_autocoder
venv_autocoder\Scripts\activate
pip install -r requirements.txt
```

# 7. Make sure you have a valid QM statechart in the "Downloads\qsm\qsm\autocoder\XML" directory. 
(We have supplied a sample statechart.)

# 8. Create a list of events with time dispatched  > in.txt  
(We have supplied a sample input file.)

# 9. Run our sample machine by executing:
```sh
python main.py XML\demoChart3.qm in.txt
```
But you can run any machine with:
```sh
python main.py XML\<yourStateChart.qm> <yourInput.txt>
```


## Tech

QSM uses a number of open source projects to work properly:

- [Python](https://breakdance.github.io/breakdance/) - A powerful scripting language
- [CMAKE](https://breakdance.github.io/breakdance/) - The standard compiler management project for c++
- [XML](https://breakdance.github.io/breakdance/) - a markup language that is both human-readable and machine-readable
- [LXML](https://breakdance.github.io/breakdance/) - an open source parsing library
- [JSON](https://breakdance.github.io/breakdance/) - a lightweight data-interchange format

And of course QSM itself is open source with a [public repository](https://github.com/JPL-UNLV-CS-2021/qsm)
 on GitHub.

## Team Members
| Members | Github |
| ------ | ------ |
| Raphael Uzan | https://github.com/RaphaelRUzan |
| Michael Fields | https://github.com/lvblazer |
| x | [plugins/googledrive/README.md][PlGd] |
| x | [plugins/onedrive/README.md][PlOd] |
| x | [plugins/medium/README.md][PlMe] |
| x | [plugins/googleanalytics/README.md][PlGa] |


## License

Apache (See official license documents in repo)

**Thank you! Hope you enjoyed!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

