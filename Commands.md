# Commands

## To Set Up Message Queue Telemetry Transport(MQTT)

- sudo systemctl enable mosquitto.service

- *sudo apt install mmosquitto*

- *sudo apt install mmosquitto-clients*: On client system

- *mosquitto_pub -h ip_address_of_broker -t topic -m "messahe to be published"*: Publisher

- *mosquitto_sub -h ip_address_of_broker -t topic*: Subscriber

- Download *MQTT Dashboard* app in phone and enjoy 