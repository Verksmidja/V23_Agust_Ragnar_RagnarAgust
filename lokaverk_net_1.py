# Receive telemetry from the MQTT broker
# Vefgrein: https://github.com/microsoft/IoT-For-Beginners/blob/main/1-getting-started/lessons/4-connect-internet/README.md#receive-telemetry-from-the-mqtt-broker
# Kóði: https://github.com/microsoft/IoT-For-Beginners/blob/main/1-getting-started/lessons/4-connect-internet/code-server/server/app.py

import paho.mqtt.client as mqtt  
import time
import json




import flask
from flask import Flask

#from flask import Flask, render_template


gul= 3
silv= 3


app = Flask(__name__)

@app.route("/")
def home():
    
    

    global gul

    global silv
    

    # Use the same ID on telemetry, server and actuator vesm3
    id = '<wruwrhukwwg4>'

    # unique name for this MQTT client on the broker.
    client_name = id + 'test_server'
    client_telemetry_topic = "home/livingroom/temperature"

    mqtt_client = mqtt.Client(client_name)
    mqtt_client.connect('10.201.48.68') 
    mqtt_client.loop_start()
 


    # When a telemetry message is received, the handle_telemetry function is called, 
    # printing the message received to the console.
    def handle_telemetry(client, userdata, message):
        # breytum Json streng (gögn) í dictionary
        payload = json.loads(message.payload.decode())
        # prentum í console gögnin.
        print("Message received:", payload)

        s1 = str(payload)
        print("s1",s1)
        
        #f = open("demofile3.txt", "w")
        #f.write(s1)
        #f.close()

        if s1 == "100":
            print("asssssssssssssssssssssssssssssssssss")

            f = open("demofile3.txt", "w")
            f.write("silv")
            f.close()

        
        if s1 == "200":
            print("snasssssssssssssssssssssssssssssssssss")
 
            f = open("demofile3.txt", "w")
            f.write("gul")
            f.close()
        return s1


    print(gul)
    soft=int(gul)
    print(soft)

    

    
    # Hlustum eftir ákveðnu topic.
    mqtt_client.subscribe(client_telemetry_topic)
    # The MQTT client is listening to messages on a background thread and runs all the time the main application is running.
    mqtt_client.on_message = handle_telemetry

    #f = open("demofile3.txt", "r")
    #print(f.read(),"adfcvsfvvvvvvvvvvvvvvvvvvv")
    f = open("demofile3.txt", "r")
    fileee = f.read()
    f.close()
    print("fffffffffffffffffffffffffffffffff",fileee)
    if fileee == "silv":
        print("111111111111111111111111111")
        gul=gul-1

    if fileee == "gul":
        print("22222222222222222222222222222")
        silv=silv-1
    fileee = ""
    
    gull=str(gul)
    sill=str(silv)
    if gul == 0:
        gul=3
    if silv== 0:
        silv=3

    return f"gull_team {gull}! silver_team {sill} !"
print("ssssssssssssssssssssssssssssssssssssssssssss")
app.run(debug=True)