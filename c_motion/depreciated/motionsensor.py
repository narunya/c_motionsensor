from machine import Pin
 import utime
 
 trigger = Pin(2, Pin.OUT)
 echo = Pin(3, Pin.IN)
 buzzer = Pin(14, Pin.OUT)
 
 # Define musical notes and their frequencies (in Hz)
 NOTE_C4 = 261
 NOTE_E4 = 329
 NOTE_G4 = 392
 
 
 # Function to play a note at a given frequency for a duration
 def play_note(frequency, duration):
     period = 1 / frequency  # Calculate the period (time for one cycle)
     half_period = period / 2  # Half the period for on/off toggling
     
     # Play the note for the given duration
     end_time = utime.ticks_ms() + duration
     while utime.ticks_ms() < end_time:
         buzzer.value(1)  # Turn buzzer on
         utime.sleep_us(int(half_period * 1_000_000))  # Sleep for half the period
         buzzer.value(0)  # Turn buzzer off
         utime.sleep_us(int(half_period * 1_000_000))  # Sleep for the other half of the period
 
 # Function to alert with a melody
 def buzzer_alert():
     # Play a simple melody with different notes
     play_note(NOTE_E4, 200)  
     play_note(NOTE_G4, 200) 
     play_note(NOTE_C4, 200)  
     play_note(NOTE_E4, 200)  
 
 def measure_distance():
     # Send a 10us pulse to the trigger pin
     trigger.value(0)
     utime.sleep_us(2)
     trigger.value(1)
     utime.sleep_us(10)
     trigger.value(0)
 
     # Measure the time for the echo pin to go HIGH
     while echo.value() == 0:
         start_time = utime.ticks_us()
     while echo.value() == 1:
         end_time = utime.ticks_us()
 
     # Calculate distance (duration in microseconds * speed of sound in cm/us / 2)
     duration = utime.ticks_diff(end_time, start_time)
     distance = (duration * 0.0343) / 2  # Speed of sound is ~343 m/s or 0.0343 cm/us
 
     return distance
 
 print("Distance measurement system active...")
 
 try:
     while True:
         distance = measure_distance()  # Measure distance from the ultrasonic sensor
         print("Distance: {:.2f} cm".format(distance))
 
         if distance < 10:  # If an object is closer than 10 cm
             print("Object detected, playing melody!")
             buzzer_alert()  # Activate buzzer to play melody
         else:
             buzzer.value(0)  # Ensure the buzzer is off when no object is detected
 
         utime.sleep(0.1)  # Small delay to avoid excessive polling
 
 except KeyboardInterrupt:
     print("Program stopped.")
     buzzer.value(0)  # Turn off the buzzer before exiting
