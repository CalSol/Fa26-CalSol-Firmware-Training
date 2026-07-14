

*For the ESP32-S3 DevKitC-1

# Windows ESP-IDF Setup

### Prerequisites:
- Download VS Code
- Download ESP-IDF extension

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


## Create (& Build) a Project (Start from this [Link](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html#get-started-build))
Download the ESP-IDF VS Code Extension

<img width="460" height="198" alt="fw5" src="https://github.com/user-attachments/assets/bc95dc35-1921-44d3-b011-23bd910960c0" />  




Open the hyperlinked text above ("ESP-IDF Extension for VS Code") 
Then go to Install ESP-IDF and Tools

<img width="394" height="101" alt="fw6" src="https://github.com/user-attachments/assets/5087d047-dedf-4bcb-81a1-55cd939a59fd" />  



 
Follow instructions until you reach yellow box below:

<img width="466" height="52" alt="fw7" src="https://github.com/user-attachments/assets/0712d161-c881-40f7-8459-db01efe7b145" />  



Any Problems? Press "Troubleshooting"
If not, continue to Step 6 
Click on "Start a Project" guide or “ (Both open this page: [Link](https://docs.espressif.com/projects/vscode-esp-idf-extension/en/latest/startproject.html#create-an-esp-idf-project))

<img width="266" height="239" alt="fw8" src="https://github.com/user-attachments/assets/b9d01ee0-5772-4403-9f52-53e143debcfe" />  



Follow all instructions to Create a Project  




DURING COMMAND PALETTE STEP:
Make sure to press what's underlined in red below!

<img width="448" height="36" alt="fw9" src="https://github.com/user-attachments/assets/2c6e33f5-b437-4c8f-b96b-88bc0efa0345" />  

<br><br>

### At this step, if unsure about which port (place on your laptop/PC to connect ESP32 through cable), press hyperlinked ‘Establish Serial Communication.”

<img width="458" height="233" alt="fw11" src="https://github.com/user-attachments/assets/d14900ec-9507-442c-8b94-eb4b5ec84972" />  



Scroll down to ‘Check Port on Windows’:
To identify serial port, follow instructions
(!!!) Check that cable supports data-transfer (not just charge only)
If cable is data-transferrable, Upon connection, device manager page should automatically refresh and update w/ ESP32 connection

<img width="340" height="169" alt="fw12" src="https://github.com/user-attachments/assets/c63c07e7-a18b-40c3-8ad3-b4a7c9c0bc1a" />  




First project made!
Can do more with the guides below

<img width="392" height="94" alt="fw10" src="https://github.com/user-attachments/assets/cc1f7ebf-385d-4ecb-8c71-8da7ddac3a49" />  

<br><br>

## Access & code project
(Usual) file path to your project.
esp-idf > examples > get_started > project_name
In project folder, go to ‘main’ file. The C or C++ file can be opened in VS code and edited.
Get the C/C++ extension!!
Code in C/C++

Section 1 walks you through preparing this 'main' file to be built, flashed, and then for the output to be monitored.

## Build, Flash, and Monitor:

[Short desc of buttons in VS Code GUI]

Whenever edits to the file/code are made, rebuild  before flashing. 

**Always clear the build before rebuilding!**

**Shortcut:** Build, Flash, Monitor in one button




