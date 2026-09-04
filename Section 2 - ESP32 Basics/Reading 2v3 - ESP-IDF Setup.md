# CLI Setup

<br><br>
<br><br>

# GUI Setup

## Begin Software Setup

(Start from this [Link](https://docs.espressif.com/projects/esp-dev-kits/en/latest/esp32s3/esp32-s3-devkitc-1/user_guide_v1.1.html))

Click "Installation"

<img width="449" height="71.5" alt="fw1" src="https://github.com/user-attachments/assets/b1581fe2-fece-4522-a436-1d9f8e7441b4" />  

<br><br>


Click the appropriate ESP-IDF (GUI) installation for your computer.

<img width="390" height="188" alt="fw2" src="https://github.com/user-attachments/assets/ab0287d6-399b-4a04-b00b-34d3ce722428" />  

<br><br>

If you are using macOS or Linux and do not have Homebrew installed:

Run this command in your terminal: 
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```



Then follow the whole installation process until you reach this window.

<img width="359" height="176" alt="fw3" src="https://github.com/user-attachments/assets/e4786013-6020-4924-8e20-c9556208645c" />  



<br><br>


If Installation fails, then:

<img width="892" height="92" alt="fw4" src="https://github.com/user-attachments/assets/21fad147-68f4-45ea-9f06-91ea8b0cb672" />  







<br><br>


## Create a Project (Start from this [Link](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html#get-started-build))
Download the ESP-IDF VS Code Extension

<img width="460" height="198" alt="fw5" src="https://github.com/user-attachments/assets/bc95dc35-1921-44d3-b011-23bd910960c0" />  



<br><br>

Open the hyperlinked text above ("ESP-IDF Extension for VS Code") 
Then go to Install ESP-IDF and Tools

<img width="394" height="101" alt="fw6" src="https://github.com/user-attachments/assets/5087d047-dedf-4bcb-81a1-55cd939a59fd" />  



 
Follow instructions until you reach yellow box below:

<img width="466" height="52" alt="fw7" src="https://github.com/user-attachments/assets/0712d161-c881-40f7-8459-db01efe7b145" />  



Any Problems? Press "Troubleshooting"
If not, continue to Step 6 

<br><br>

Click on "Start a Project" guide or “ (Both open this page: [Link](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/startproject.html#create-an-esp-idf-project))

<img width="266" height="239" alt="fw8" src="https://github.com/user-attachments/assets/b9d01ee0-5772-4403-9f52-53e143debcfe" />  



Follow all instructions to Create a Project  





<img width="448" height="36" alt="fw9" src="https://github.com/user-attachments/assets/2c6e33f5-b437-4c8f-b96b-88bc0efa0345" />  

<br><br>

DURING COMMAND PALETTE STEP:
Make sure to press what's underlined in red below!

<img width="392" height="94" alt="fw10" src="https://github.com/user-attachments/assets/cc1f7ebf-385d-4ecb-8c71-8da7ddac3a49" />  
<br><br>

While creating New Project: Select a template project or any example project 

<img width="250" height="105.5" alt="image" src="https://github.com/user-attachments/assets/cbeb0143-6103-4bc6-83e0-582a28728485" />

<br><br>

Project Attributes Breakdown:

<img width="315.5" height="221" alt="image" src="https://github.com/user-attachments/assets/289bc19e-56f6-48bc-9d3e-136a97fcdd1e" />


1) Project Name
2) Project Folder location of choice in your file manager 
3) Target Device
4) Distinction between having built-in hardware for debugging (JTAG) vs. needing to connect external hardware
5) Choosing the port on your computer that your ESP32 connects to (detect will automatically choose the port that's connected for you.)
6) Add locations of component folders (components explained later!)

<br><br>

### At this step, if unsure about which port (place on your laptop/PC to connect ESP32 through cable), press hyperlinked ‘Establish Serial Communication.”

<img width="458" height="233" alt="fw11" src="https://github.com/user-attachments/assets/d14900ec-9507-442c-8b94-eb4b5ec84972" />  

<br><br>

Scroll down to ‘Check Port on Windows’:
To identify serial port, follow instructions
(!!!) Check that cable supports data-transfer (not just charge only)
If cable is data-transferrable, Upon connection, device manager page should automatically refresh and update w/ ESP32 connection

<img width="340" height="169" alt="fw12" src="https://github.com/user-attachments/assets/c63c07e7-a18b-40c3-8ad3-b4a7c9c0bc1a" />  

<br><br>


<i></i>**Congrats, you made your first project!**<i></i>

<br><br>

## Access & code project

To edit/use it at any point, open VS Code, open the project folder (File > Open Folder..), and enable the ESP-IDF extension.

The Extension opens this left side-bar:


<img width="218" height="361" alt="image" src="https://github.com/user-attachments/assets/1699c93b-77b3-4081-be3d-7ef7ebae7a7a" />

- Choose your opened project folder as the current workspace using the first checkboxed command.

Each command (and more) with a checkbox should open a button used for that purpose at the bottom:


<img width="362.5" height="148" alt="image" src="https://github.com/user-attachments/assets/2825aebc-83b1-4705-bf6c-ddc72d4cfdfd" />



<br><br>

Info on the purpose of each file/folder in your project folder [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html).
(Great breakdown of components [here](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html)).

<br><br>

In project folder, go to ‘main’ file. (As per the C Basics section, the C/C++ extension in VS Code lets you write C/C++ code in this file).


## Build, Flash, and Monitor:

When you're ready to test your code by flashing it to the ESP32 connected to your computer, first build, flash, and then you can monitor its output.

These commands will have matching buttons at the bottom of your screen that you press to execute:

<img width="180" height="111" alt="image" src="https://github.com/user-attachments/assets/5f18b35e-0109-40b3-9bf1-774e8b1bb322" />

<br><br>

IMPORTANT:
- Whenever edits to the file/code are made, rebuild  before flashing. 
- **Always full clean before rebuilding!**
- **Shortcut:** Build, Flash, Monitor in one button

