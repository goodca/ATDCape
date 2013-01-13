roverGUI
========

A Wiki page for this project can be found here: http://www.elinux.org/ECE497_Project_RoverGUI

This project is based on node.js and will allow the BeagleBone to be a server for a webpage that will serve as a GUI for a device that either uses simple commands such as left/right/forward or can make use of gps coordinates. 

The server can be launched by running:

node GUI.js

The server can then be accessed by running beagle@8081 where beagle is the ip for the BeagleBone.
The webpage will then give the option for either the simple or maps GUI. The simple GUI will give buttons that will be labled with simple instructions. If a button is pressed a file will be created in the top GUI directory called inst.txt that will contain the text from the button. Thus a device can receive commands.

If the Maps option is selected a Google Maps interface will be embedded in the browser as well as a connection indicator and a done button. The map can be manipulated in typical Google Maps fashion. If a left click is registered a marker will be placed. Any additional clicks will create additional markers with a line connecting the most recent clicked to the preceeding marker. When the done button is pressed inst.txt will be populated with the list of GPS coordinates of the markers in order they were clicked with each coordinate on a new line.
