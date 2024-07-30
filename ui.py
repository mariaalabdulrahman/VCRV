import tkinter as tk
import requests
import threading
import subprocess
import time

def send_get_request(direction):
    dummy_ip = "http://192.168.8.105:5000" 
    url = f"{dummy_ip}/{direction}"
    response = requests.get(url)
    print(response.text)

def stt():
    command = "cheetah_demo_mic --access_key ndHk4eU4SVLK0IjTP/a29PaK0k50Ukst396Hk1MteSDP+a5230JZag=="
    talk_label.config(text="Please Wait")

    try:
        process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        time.sleep(3)  # Simulating STT process
        talk_label.config(text="Talk Now")
        
        time.sleep(5)  # Simulating STT process
        process.terminate()
        process.wait()
        stdout, stderr = process.communicate()

        stdout = str(stdout.decode('utf-8'))
        stdout = stdout.replace("Cheetah version : 1.1.0\n","").replace("Listening... (press Ctrl+C to stop)\n","").replace("\n"," ")

        forward_button.config(state=tk.NORMAL)
        backward_button.config(state=tk.NORMAL)
        left_button.config(state=tk.NORMAL)
        right_button.config(state=tk.NORMAL)
        stop_button.config(state=tk.NORMAL)

        stdout = stdout.lower()
        print(stdout)
        talk_label.config(text="")  # Hide "Talk Now" text when STT starts
        
        if "forward" in stdout:
            # Send GET request in a separate thread
            thread = threading.Thread(target=send_get_request, args=("forward",))
            thread.start()
        elif "backward" in stdout:
            thread = threading.Thread(target=send_get_request, args=("backward",))
            thread.start()
        elif "left" in stdout:
            thread = threading.Thread(target=send_get_request, args=("left",))
            thread.start()
        elif "right" in stdout:
            thread = threading.Thread(target=send_get_request, args=("right",))
            thread.start()
        elif "stop" in stdout:
            thread = threading.Thread(target=send_get_request, args=("stop",))
            thread.start()
        
    except subprocess.CalledProcessError as e:
        print(f"Error: {e}")

def on_movement_button_click(direction):
    # Send GET request in a separate thread
    thread = threading.Thread(target=send_get_request, args=(direction,))
    thread.start()

def on_voice_command_click():
    # Disable movement buttons during STT process
    forward_button.config(state=tk.DISABLED)
    backward_button.config(state=tk.DISABLED)
    left_button.config(state=tk.DISABLED)
    right_button.config(state=tk.DISABLED)
    stop_button.config(state=tk.DISABLED)
    
    # Start the STT process in a separate thread
    thread = threading.Thread(target=stt)
    thread.start()

root = tk.Tk()
root.title("Movement Control")

talk_label = tk.Label(root, text="", font=("Arial", 16))
talk_label.grid(row=0, column=0, columnspan=3, pady=10)

forward_button = tk.Button(root, text="Forward", width=10, height=3, command=lambda: on_movement_button_click("forward"))
forward_button.grid(row=1, column=1, padx=5, pady=5)

backward_button = tk.Button(root, text="Backward", width=10, height=3, command=lambda: on_movement_button_click("backward"))
backward_button.grid(row=3, column=1, padx=5, pady=5)

left_button = tk.Button(root, text="Left", width=10, height=3, command=lambda: on_movement_button_click("left"))
left_button.grid(row=2, column=0, padx=5, pady=5)

right_button = tk.Button(root, text="Right", width=10, height=3, command=lambda: on_movement_button_click("right"))
right_button.grid(row=2, column=2, padx=5, pady=5)

stop_button = tk.Button(root, text="Stop", width=10, height=3, command=lambda: on_movement_button_click("stop"))
stop_button.grid(row=2, column=1, padx=5, pady=5)

voice_command_button = tk.Button(root, text="Voice Command", width=15, height=2, command=on_voice_command_click)
voice_command_button.grid(row=4, column=1, padx=5, pady=10)

root.mainloop()