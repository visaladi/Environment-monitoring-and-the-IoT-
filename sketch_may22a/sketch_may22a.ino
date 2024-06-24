const int relayPins[] = {0, 1, 2, 3};
int currentRelay = 0; // Start with relay 0

void setup() {
  // Set relay pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Assume HIGH is off for the relay
  }

  // Turn on the first relay to start the sequence
  digitalWrite(relayPins[currentRelay], LOW); // Assume LOW is on for the relay
  
  // Ensure relay 3 (pin 3) is always on
  digitalWrite(relayPins[3], LOW); // Turn on relay 3
}

void loop() {
  // Wait for some time before switching relays
  delay(1000); // 1 second delay, adjust as needed

  // Turn off the current relay
  digitalWrite(relayPins[currentRelay], HIGH);

  // Move to the next relay in the sequence
  currentRelay = (currentRelay + 1) % 4;

  // Turn on the new current relay
  digitalWrite(relayPins[currentRelay], LOW);

  // If we completed one full sequence (back to relay 0)
  if (currentRelay == 0) {
    // Turn off all relays
    for (int i = 0; i < 4; i++) {
      digitalWrite(relayPins[i], HIGH);
    }
    delay(1000); // Wait for 1 second after turning off all relays

    // Turn on all relays
    for (int i = 0; i < 4; i++) {
      digitalWrite(relayPins[i], LOW);
    }
    delay(2000); // Wait for 1 second with all relays on

    // Turn off all relays again
    for (int i = 0; i < 4; i++) {
      digitalWrite(relayPins[i], HIGH);
    }
    delay(500); // Wait for 0.5 seconds

    // Turn on the first relay to start the sequence again
    digitalWrite(relayPins[0], LOW);
    
    // Ensure relay 3 (pin 3) is always on
    digitalWrite(relayPins[3], LOW); // Turn on relay 3
  }
}
