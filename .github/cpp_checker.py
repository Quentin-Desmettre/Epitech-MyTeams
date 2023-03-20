#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## Epitech-Template
## File description:
## cpp_checker.py
##

# For each .cpp, .hpp file, send it to the tokenizer.

import os, sys, websocket

# Get files
os.system("find . -name '*.cpp' -o -name '*.hpp' > files.txt")
files = []
with open("files.txt", "r") as f:
    files = f.read().splitlines()
os.system("rm files.txt")

def tokenForIndex(tokens, index):
    return tokens[index].split("\1")[0]

# Open a websocket to 172.67.3.12:8080
filesReceived = 0
def on_message(ws: websocket.WebSocketApp, message):
    global filesReceived
    filesReceived += 1

    # Parse the message
    tokens = message.split("\2")
    for i in range(len(tokens)):
        # Parse the token
        token = tokens[i]
        if token == "":
            continue
        token = tokenForIndex(tokens, i)

        # Check if the token is a friend keyword
        if token == "friend":
            print("Friend keyword found at line " + str(tokens[i].split("\1")[1]) + " !")
            ws.close()
            exit(1)

        # Check if the token is a using namespace std
        if token == "using" and " " in tokenForIndex(tokens, i + 1) and tokenForIndex(tokens, i + 2) == "namespace" and " " in tokenForIndex(tokens, i + 3) and tokenForIndex(tokens, i + 4) == "std":
            print("Using namespace std found at line " + str(tokens[i].split("\1")[1]) + " !")
            ws.close()
            exit(1)

    # Check if all files have been received
    if filesReceived == len(files):
        print("No error found")
        ws.close()
        exit(0)

def on_error(ws, error):
    print(f"Connection error: {error}")

def on_close(ws):
    pass

def on_open(ws: websocket.WebSocketApp):
    for file in files:
        with open(file, "r") as f:
            ws.send(f.read())
    if len(files) == 0:
        print("No error found")
        ws.close()
        exit(0)

# websocket.enableTrace(True)
ws = websocket.WebSocketApp("ws://54.36.183.139:8081/",
                            on_message=on_message,
                            on_error=on_error,
                            on_close=on_close)
ws.on_open = on_open
ws.timeout = 10
ws.run_forever()
