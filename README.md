# ESP8266 based 433Mhz transmitter
Designed for controlling 433Mhz remote controlled sockets via MQTT. Currently running on NodeMCU v1.0 and being controlled by Home Assistant running on a Raspberry Pi 3.

To transmit 24 bit RF codes, publish an MQTT packet with the topic `433transmitter/rfcode` and the 8 digit RF code as the payload.

The imported file `secrets.h` contains the following variables:

* wifi_ssid
* wifi_password
* mqtt_server
* mqtt_port
* mqtt_user
* mqtt_pass
* mqtt_client_name
