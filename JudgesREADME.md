# Instructions for judges
## _Must be run on a windows 10 Machine_
QSM is a state design pattern for embedded flight systems the modern era.

- No Recursion
- No templating
- No Dynamic Memory
- Runtime polymorphism
- Abstract + Concrete Inheritance
- Heirarchical representation in code

## Features

- Import a QM file and watch it magically convert to a running state machine.
- Run heirarchical state machines with a virtually unlimited nesting depth.
- Create events in a simulated environment to see how the machine fairs.
- Change any aspect to the original statemachine design, and have a new machine in one command.



## Tech

QSM uses a number of open source projects to work properly:

- [Python](https://breakdance.github.io/breakdance/) - A powerful scripting language
- [CMAKE](https://breakdance.github.io/breakdance/) - The standard compiler management project for c++
- [XML](https://breakdance.github.io/breakdance/) - a markup language that is both human-readable and machine-readable
- [LXML](https://breakdance.github.io/breakdance/) - an open source parsing library
- [JSON](https://breakdance.github.io/breakdance/) - a lightweight data-interchange format

And of course QSM itself is open source with a [public repository](https://github.com/JPL-UNLV-CS-2021/qsm)
 on GitHub.

## Installation for Auto Coder

QSM is a tool to be used in conjuction with other tools  by JPL engineers in a development environment.
As such to test it we must first spend time setting up a similiar environment..

1. [Install QM](https://www.state-machine.com/qm/)

2. Figure out what kind of architecture your operating system is currently running. 32 bit or 64 bit
	![ARCH32OR64](https://i.ibb.co/XC1BW3x/image.png)
3. Install CMAKE
- Go to https://cmake.org/download/
- Scroll to "Binary distributions:" (under "Source Distributions")
- If you have a 32 bit version of Windows 10, download "Windows i386 Installer"
- If you have a 64 bit version of Windows 10, download "Windows x64 Installer"
- Run the installer
	- Accept User Agreement
	- On the Install Options page
		- SELECT "Add CMake to the system PATH for all users"
		- Next
	- Choose your installation location. The default is fine.
	- Proceed to install!

4. Double check the installation
	- Select the Start button
	- Type "Command Prompt" and launch the command prompt
	- In the command prompt type "python"
	  There should be version 3.X.X.
	  Use quit() or Ctrl-Z plus Return to exit
	- In the command prompt type "cmake"
	  You should see a response other than "cmake not recogonized".

        If both of those work then we successfully have CMAKE and python installed.
        
5. Download the project.

- Go to https://github.com/JPL-UNLV-CS-2021/qsm
- Click "Code" and then "Download ZIP"
- Extract the ZIP file in your downloads folder

6. Go back to the commandline and run the following commands
	```sh 
    cd Downloads\qsm\qsm\src\autocoder
	py -m venv venv_autocoder
	venv_autocoder\Scripts\activate
	pip install -r requirements.txt
	```

7. Make sure you have a valid QM statechart in the "Downloads\qsm\qsm\autocoder\XML" directory. 
(We have supplied a sample statechart.)

8. Create a list of events with time dispatched  > in.txt  (We have supplied a sample input file.)

9. Run your machine by executing:
    ```sh
    python main.py XML\<yourStateChart.qm> <yourInput.txt>
    ```
    Or run our sample with
    ```sh
    python main.py XML\demoChart3.qm in.txt
    ```

## Team Members
| Members | Github |
| ------ | ------ |
| Raphael Uzan | [https://github.com/RaphaelRUzan] |
| x | [plugins/github/README.md][PlGh] |
| x | [plugins/googledrive/README.md][PlGd] |
| x | [plugins/onedrive/README.md][PlOd] |
| x | [plugins/medium/README.md][PlMe] |
| x | [plugins/googleanalytics/README.md][PlGa] |


## License

Apache (See official license documents in repo)

**Thank you! Hope you enjoyed!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

