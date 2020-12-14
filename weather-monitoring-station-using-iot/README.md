# Swecha-IoT-Weather-Monitoring-System
This project demonstrates the basic requirements of any application using IOT. Use this code to improve the project or build your own application out of it. 

< Happy Hacking :-p />    - If you have any queries, contact me on telegram (@JayaSimhaReddy)

Internet Of Things ( IOT ) ---- Swecha


This project can be divided into two sub projects.
-> Data Vizualisation using Thingsboard. (Module A)
-> Data Collection using python and mySQL.  (Module B)


Software Requirements:
-> Arduino IDE
-> Libraries (DHT sensor , pubsubclient)
-> Package to install NodeMCU boards

Module A (Requirements)
-> Thingsboard login

Module B (Requirements)
-> mySQL server
-> MQTT server
-> Python

WE CAN PROGRAM THE NODEMCU USING ARDUINO IDE
DOWNLOAD THE LATEST ARDUINO IDE FROM arduino.cc AND
INSTALL
Step:1 Installing Boards for NODEMCU1.0
open arduino ide
goto >file>preferences
Add url to additional boards manager

http://arduino.esp8266.com/stable/package_esp8266com_index.json

Restart arduino ide
Goto >tools>Board>Boards Manager
Download esp8266 boards
Restart arduino ide
Goto >tools>Board>select nodemcu 1.0
And com port
And programmer as “Arduino ISP”
Connect the nodemcu board
Upload a sample code like blink led program from examples of nodemuc
Goto>file>examples>esp8266>blink

Step2: Adding Required Libraries for Arduino IDE to connect MQTT
and DHT sensor
Open Arduino IDE
Goto sketch>Include Libraries>Add .ZIP Library >
Select PubSubClient.zip
and DHT_sensor_Library.zip
Step3: Hardware Connections

DHT11 ---> NodeMCU

VCC ---> 3V3
GND ---> GND
DATA ---> D2 (Digital Pin)

Module A: (Data Vizualisation using Thingsboard)

Data Visualization using Thingsboard
Setting up account on thingsboard
Open http://demo.thingsboard.io
Create an account
Login to thingsboard.Select devices from Thingsboard main menu

Create a new Device and Copy the ACCESS TOKEN

Open Arduino IDE
Open nodemcu code for Thingsboard and make the necessary changes.
-- Wifi ssid, Password.
-- Digital Pin to read input from Sensor
-- Access Token from thingsboard Device.

Upload the code in NodeMCU and check the status in Serial Monitor.
Open Thingsboard........
Goto Devices > Latest Telemetry
We can observe the Temperature and Humidity data in the Latest Telemetry.

Create a new Dashboard
add new widget> Select the suitable widget of your choice

Configure the Widget:
Entity Entity Name ( Your Device Name ) Attributes ( Humidity ,Temperature )
Similarly, You can add Multiple Widgets and Collect data from different Locations.




* If you had played around with thingsboard and if you wish to deploy and store the sensor data in our local server, continue with module B *


Module B: How to get data from sensors to MYSQL database using MQTT

Need to setup a database in server side system

Installing Mosquitto
MQTT is a machine-to-machine messaging protocol, designed to provide lightweight
publish/subscribe communication to "Internet of Things" devices.

$ sudo apt-get install mosquitto mosquitto-clients

By default, linux will start the Mosquitto service after install.
Log in to your server a second time, so you have two terminals side-by-side.
In the new terminal, use mosquitto_sub to subscribe to the test topic.

$ mosquitto_sub -h localhost -t test

-h is used to specify the hostname of the MQTT server, and -t is the topic name.
You'll see no output after hitting ENTER because mosquitto_sub is waiting for
messages to arrive. Switch back to your other terminal and publish a message:'

$ mosquitto_pub -h localhost -t test -m "hello world"

The options for mosquitto_pub are the same as mosquitto_sub, though this time we
use the additional -m option to specify our message.
Hit ENTER, and you should see hello world pop up in the other terminal. You've sent
your first.
MQTT message!
Install MySQL database:
MySQL is a popular database management system used for web and server
applications.

$ sudo apt-get install mysql-server

During the installation process, you will be prompted to set a password for the
MySQL root user .
Choose a strong password and keep it in a safe place for future reference.

$ sudo mysql_secure_installation

You will be given the choice to change the MySQL root password, remove
anonymous user accounts, disable root logins outside of localhost, and remove testdatabases. It is recommended thatyou answer yes to these options. You can read more
about the script in the MySQL Reference Manual.
Then start MySQL:

$ sudo service mysql start

to stop

$ sudo service mysql stop

start agian

How to use mysql :
Use MySQL
To log in to MySQL as the root user:

$mysql -u root -p

When prompted, enter the root password you assigned when the
mysql_secure_installation script was run.
You’ll then be presented with the MySQL monitor prompt: Welcome to the MySQL
monitor. Commands end with ; or \g. Your MySQL connection id is 1. Server version:
5.0.45 Source distribution. Type 'help;' or '\h' for help. Type '\c' to clear the buffer.
mysql>

Create a New MySQL User and Database:
In the example below, testdb is the name of the database, testuser is the user, and
password is the user’s password.

Mysql> create database testdb;
Mysql> create user 'testuser'@'localhost' identified by 'password';
Mysql> grant all on testdb.* to 'testuser';

or

Mysql> create database testdb;
Mysql> grant all on testdb.* to 'testuser' identified by 'password';

To exit MySQL:

Mysql> exit;

Create a Sample Table

create table text(varchar device, varchar attribute, varchar value, varchar timestamp );

Install python:
goto python official website and download python latest
uzip it
open terminal

./configure
make
make install

Install pip

$ sudo apt-get install python-pip python-dev build-essential
$ sudo pip install --upgrade pip
$ sudo pip install MySQL-python
-- (used to link mysql database)
$ sudo pip install paho-mqtt
-- ( used to link mqtt data)
(https://eclipse.org/paho/clients/python/)

Project:

Connect the dht11 sensor to digital pin of nodemcu
Upload nodemcu code to nodemcu board(by doing all required changes)
-- wifi ssid and password
-- mqtt link (Add the ip address of the server side system)

And in server side system start mosquitto server

$mosquitto_sub -t 'outopic' >log.txt

By adding database details to main.py
-- Change the hostname, database, user, pw etc

Run runthiscode.py

python runthiscode.py

