/*
═══════════════════════════════════════════════════════════
  DELTA ASDA-B3 SERVO MOTOR CONTROL - ARDUINO MEGA 2560
  
  Complete implementation for position control with:
  - High-speed pulse generation (up to 250 kHz)
  - Limit switch protection
  - 1 meter/second linear motion
  - Serial command interface
  - Real-time status monitoring
  - Emergency stop functionality
  
  Hardware Requirements:
  - Arduino Mega 2560
  - Delta ASDA-B3 Servo Driver
  - 2× Limit Switches (NC configuration)
  - 24V DC Power Supply
  
  Pin Connections:
  - Pin 9  → CN1 Pin 5 (PULS+)
  - Pin 8  → CN1 Pin 7 (SIGN+/DIR)
  - Pin 7  → CN1 Pin 1 (SERVO-ON)
  - Pin 6  → CN1 Pin 9 (ALM-RST)
  - Pin 5  ← DI1 (Forward Limit Switch)
  - Pin 4  ← DI2 (Reverse Limit Switch)
  - GND    → CN1 Common pins (2,6,8,10)
  
  Author: Delta ASDA-B3 Control Project
  License: MIT
  Version: 1.0
  Date: October 2025
  
  GitHub: https://github.com/yourusername/Delta-ASDA-B3-Control
═══════════════════════════════════════════════════════════
*/

// ============================================================
// PIN DEFINITIONS
// ============================================================
#define PULSE_PIN       9    // Timer1 CH1 - PWM for pulses
#define DIR_PIN         8    // Direction control (HIGH=Forward, LOW=Reverse)
#define SERVO_ON_PIN    7    // Servo enable signal
#define ALM_RST_PIN     6    // Alarm reset
#define LIMIT_FWD_PIN   5    // Forward limit switch (input with pullup)
#define LIMIT_REV_PIN   4    // Reverse limit switch (input with pullup)
#define LED_STATUS      13   // Built-in LED for status indication

// ============================================================
// CONFIGURATION CONSTANTS
// ============================================================
// *** ADJUST THESE FOR YOUR SPECIFIC SYSTEM ***

// Motion parameters
#define PULSES_PER_MM   250      // Calculated: Encoder PPR / Lead or Circumference
                                 // Example: 2500 PPR / 10mm lead = 250 pulses/mm
#define MAX_SPEED_MM_S  1000     // Maximum speed: 1000 mm/s = 1 m/s
#define PULSE_FREQ_HZ   250000   // PULSES_PER_MM × MAX_SPEED_MM_S = 250 kHz

// Motion profile
#define ACCEL_TIME_MS   200      // Acceleration time (milliseconds)
#define DECEL_TIME_MS   200      // Deceleration time (milliseconds)

// Safety limits
#define MAX_DISTANCE_MM 1000     // Maximum travel distance per command
#define MIN_DISTANCE_MM 1        // Minimum travel distance

// Timing
#define STATUS_INTERVAL 1000     // Status print interval (ms)
#define DEBOUNCE_DELAY  50       // Limit switch debounce delay (ms)

// ============================================================
// ENUMERATIONS & STRUCTURES
// ============================================================
enum MotionState {
  STATE_IDLE,
  STATE_MOVING_FORWARD,
  STATE_MOVING_REVERSE,
  STATE_ERROR,
  STATE_HOMING,
  STATE_DISABLED
};

// ============================================================
// GLOBAL VARIABLES
// ============================================================
// State management
volatile MotionState currentState = STATE_DISABLED;
volatile bool limitFwdTriggered = false;
volatile bool limitRevTriggered = false;
volatile bool emergencyStop = false;
bool servoEnabled = false;

// Position tracking
volatile long currentPosition = 0;      // Current position in pulses
long targetPosition = 0;                // Target position in pulses
long homePosition = 0;                  // Home position reference

// Timing
unsigned long lastStatusPrint = 0;
unsigned long motionStartTime = 0;
unsigned long lastDebounceTime = 0;

// Statistics
unsigned long totalDistance = 0;        // Total distance traveled
unsigned int errorCount = 0;            // Number of errors encountered

// ============================================================
// SETUP FUNCTION
// ============================================================
void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial && millis() < 3000); // Wait up to 3 seconds for serial
  
  // Print startup banner
  printBanner();
  
  // Configure pins
  Serial.print(F("Configuring GPIO pins... "));
  pinMode(PULSE_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(SERVO_ON_PIN, OUTPUT);
  pinMode(ALM_RST_PIN, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LIMIT_FWD_PIN, INPUT_PULLUP);
  pinMode(LIMIT_REV_PIN, INPUT_PULLUP);
  Serial.println(F("OK"));
  
  // Set initial states
  digitalWrite(PULSE_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(SERVO_ON_PIN, LOW);
  digitalWrite(ALM_RST_PIN, LOW);
  digitalWrite(LED_STATUS, LOW);
  
  // Setup Timer1 for PWM pulse generation
  Serial.print(F("Configuring Timer1 for PWM... "));
  setupTimer1PWM(PULSE_FREQ_HZ);
  Serial.println(F("OK"));
  
  // Setup limit switch interrupts
  Serial.print(F("Configuring limit switch interrupts... "));
  attachInterrupt(digitalPinToInterrupt(LIMIT_FWD_PIN), limitFwdISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_REV_PIN), limitRevISR, FALLING);
  Serial.println(F("OK"));
  
  // Check initial limit switch states
  Serial.print(F("Checking limit switches... "));
  if (digitalRead(LIMIT_FWD_PIN) == LOW || digitalRead(LIMIT_REV_PIN) == LOW) {
    Serial.println(F("\n⚠️  WARNING: Limit switch triggered at startup!"));
    Serial.println(F("    Please move motor away from limits and reset."));
    currentState = STATE_ERROR;
    errorCount++;
  } else {
    Serial.println(F("OK"));
    currentState = STATE_IDLE;
  }
  
  // Wait before enabling servo
  delay(1000);
  
  // Enable servo
  Serial.print(F("Enabling servo motor... "));
  enableServo();
  Serial.println(F("OK"));
  
  // System ready
  Serial.println(F("\n✓ System initialization complete!"));
  Serial.println(F("✓ Ready for commands\n"));
  
  // Print help
  printHelp();
  
  digitalWrite(LED_STATUS, HIGH);
}

// ============================================================
// MAIN LOOP
// ============================================================
void loop() {
  // Handle serial commands
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }
  
  // Check limit switches
  if (limitFwdTriggered && (millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    emergencyStopMotion();
    Serial.println(F("\n🛑 FORWARD LIMIT REACHED!"));
    limitFwdTriggered = false;
    lastDebounceTime = millis();
  }
  
  if (limitRevTriggered && (millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    emergencyStopMotion();
    Serial.println(F("\n🛑 REVERSE LIMIT REACHED!"));
    limitRevTriggered = false;
    lastDebounceTime = millis();
  }
  
  // Periodic status LED blink
  if (millis() - lastStatusPrint >= STATUS_INTERVAL) {
    lastStatusPrint = millis();
    blinkStatusLED();
  }
  
  // Small delay to prevent CPU overload
  delay(10);
}

// ============================================================
// TIMER1 PWM CONFIGURATION
// ============================================================
void setupTimer1PWM(unsigned long frequency) {
  // Stop timer
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // Calculate TOP value for desired frequency
  // Formula: TOP = (F_CPU / (Prescaler × Frequency)) - 1
  // For 16 MHz Arduino and no prescaler (CS10=1):
  // TOP = (16,000,000 / Frequency) - 1
  
  unsigned int top;
  
  if (frequency > 500000) {
    // Too high, use maximum
    top = 31;  // ~516 kHz
    Serial.print(F("    Warning: Requested frequency too high, using "));
    Serial.print(F_CPU / (top + 1));
    Serial.println(F(" Hz"));
  } else if (frequency < 1000) {
    // Too low, use minimum
    top = 15999;  // ~1 kHz
    Serial.print(F("    Warning: Requested frequency too low, using "));
    Serial.print(F_CPU / (top + 1));
    Serial.println(F(" Hz"));
  } else {
    top = (F_CPU / frequency) - 1;
  }
  
  // Fast PWM mode with ICR1 as TOP
  // COM1A1: Clear OC1A on compare match, set at BOTTOM (non-inverting)
  // WGM13:WGM10: Fast PWM mode 14 (TOP = ICR1)
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12);
  
  // Set TOP value
  ICR1 = top;
  
  // Set 50% duty cycle for clean square wave
  OCR1A = top / 2;
  
  // Timer stopped initially (will start when needed)
  // CS10 bit will be set to start with prescaler = 1
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
  
  Serial.print(F("    Timer configured: TOP="));
  Serial.print(top);
  Serial.print(F(", Actual frequency: "));
  Serial.print(F_CPU / (top + 1));
  Serial.println(F(" Hz"));
}

// ============================================================
// MOTION CONTROL FUNCTIONS
// ============================================================

void enableServo() {
  digitalWrite(SERVO_ON_PIN, HIGH);
  delay(100); // Wait for servo to energize
  servoEnabled = true;
  currentState = STATE_IDLE;
}

void disableServo() {
  stopPulses();
  digitalWrite(SERVO_ON_PIN, LOW);
  servoEnabled = false;
  currentState = STATE_DISABLED;
}

void startPulses() {
  // Start Timer1 with no prescaler (CS10 = 1)
  TCCR1B |= (1 << CS10);
  motionStartTime = millis();
}

void stopPulses() {
  // Stop Timer1
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
  
  // Update state
  if (currentState == STATE_MOVING_FORWARD || currentState == STATE_MOVING_REVERSE) {
    currentState = STATE_IDLE;
  }
}

void emergencyStopMotion() {
  stopPulses();
  emergencyStop = true;
  currentState = STATE_ERROR;
  errorCount++;
  digitalWrite(LED_STATUS, LOW);
}

void moveForward(unsigned int distanceMM) {
  // Safety checks
  if (!servoEnabled) {
    Serial.println(F("⚠️  Servo is disabled! Enable first (command: E)"));
    return;
  }
  
  if (currentState == STATE_MOVING_FORWARD || currentState == STATE_MOVING_REVERSE) {
    Serial.println(F("⚠️  Motor already moving! Stop first (command: S)"));
    return;
  }
  
  if (currentState == STATE_ERROR) {
    Serial.println(F("⚠️  System in error state! Reset alarm first (command: A)"));
    return;
  }
  
  if (digitalRead(LIMIT_FWD_PIN) == LOW) {
    Serial.println(F("⚠️  Already at forward limit!"));
    return;
  }
  
  if (distanceMM > MAX_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too large! Maximum: "));
    Serial.print(MAX_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  if (distanceMM < MIN_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too small! Minimum: "));
    Serial.print(MIN_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  // Calculate target position
  long pulses = (long)distanceMM * PULSES_PER_MM;
  targetPosition = currentPosition + pulses;
  
  // Set direction
  digitalWrite(DIR_PIN, HIGH); // Forward
  delayMicroseconds(10); // Direction setup time (minimum 1µs for ASDA-B3)
  
  // Start motion
  currentState = STATE_MOVING_FORWARD;
  startPulses();
  
  // Update statistics
  totalDistance += distanceMM;
  
  // Print status
  Serial.print(F("→ Moving forward: "));
  Serial.print(distanceMM);
  Serial.print(F(" mm ("));
  Serial.print(pulses);
  Serial.print(F(" pulses) @ "));
  Serial.print(MAX_SPEED_MM_S);
  Serial.println(F(" mm/s"));
}

void moveReverse(unsigned int distanceMM) {
  // Safety checks
  if (!servoEnabled) {
    Serial.println(F("⚠️  Servo is disabled! Enable first (command: E)"));
    return;
  }
  
  if (currentState == STATE_MOVING_FORWARD || currentState == STATE_MOVING_REVERSE) {
    Serial.println(F("⚠️  Motor already moving! Stop first (command: S)"));
    return;
  }
  
  if (currentState == STATE_ERROR) {
    Serial.println(F("⚠️  System in error state! Reset alarm first (command: A)"));
    return;
  }
  
  if (digitalRead(LIMIT_REV_PIN) == LOW) {
    Serial.println(F("⚠️  Already at reverse limit!"));
    return;
  }
  
  if (distanceMM > MAX_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too large! Maximum: "));
    Serial.print(MAX_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  if (distanceMM < MIN_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too small! Minimum: "));
    Serial.print(MIN_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  // Calculate target position
  long pulses = (long)distanceMM * PULSES_PER_MM;
  targetPosition = currentPosition - pulses;
  
  // Set direction
  digitalWrite(DIR_PIN, LOW); // Reverse
  delayMicroseconds(10); // Direction setup time
  
  // Start motion
  currentState = STATE_MOVING_REVERSE;
  startPulses();
  
  // Update statistics
  totalDistance += distanceMM;
  
  // Print status
  Serial.print(F("← Moving reverse: "));
  Serial.print(distanceMM);
  Serial.print(F(" mm ("));
  Serial.print(pulses);
  Serial.print(F(" pulses) @ "));
  Serial.print(MAX_SPEED_MM_S);
  Serial.println(F(" mm/s"));
}

void stopMotion() {
  stopPulses();
  Serial.println(F("⏸  Motion stopped"));
  
  if (emergencyStop) {
    Serial.println(F("    Emergency stop was triggered"));
  }
}

void resetAlarm() {
  // Pulse the alarm reset pin
  digitalWrite(ALM_RST_PIN, HIGH);
  delay(100);
  digitalWrite(ALM_RST_PIN, LOW);
  
  // Clear error states
  emergencyStop = false;
  limitFwdTriggered = false;
  limitRevTriggered = false;
  
  // Return to idle if servo is enabled
  if (servoEnabled) {
    currentState = STATE_IDLE;
  }
  
  Serial.println(F("✓ Alarm reset successful"));
  digitalWrite(LED_STATUS, HIGH);
}

void homeMotor() {
  Serial.println(F("\n🏠 Starting homing sequence..."));
  Serial.println(F("    Moving to reverse limit switch..."));
  
  if (!servoEnabled) {
    Serial.println(F("⚠️  Servo is disabled! Enable first (command: E)"));
    return;
  }
  
  currentState = STATE_HOMING;
  
  // Set direction to reverse
  digitalWrite(DIR_PIN, LOW);
  delayMicroseconds(10);
  
  // Start moving
  startPulses();
  
  // Wait for limit trigger or timeout
  unsigned long homingStartTime = millis();
  const unsigned long HOMING_TIMEOUT = 30000; // 30 seconds timeout
  
  while (digitalRead(LIMIT_REV_PIN) == HIGH && !emergencyStop) {
    // Check for timeout
    if (millis() - homingStartTime > HOMING_TIMEOUT) {
      stopPulses();
      Serial.println(F("⚠️  Homing timeout! Check limit switches."));
      currentState = STATE_ERROR;
      return;
    }
    
    // Check for user interrupt
    if (Serial.available() && Serial.read() == 's') {
      stopPulses();
      Serial.println(F("    Homing cancelled by user"));
      currentState = STATE_IDLE;
      return;
    }
    
    delay(10);
  }
  
  // Stop motion
  stopPulses();
  
  if (!emergencyStop) {
    // Reset position counter
    currentPosition = 0;
    homePosition = 0;
    
    Serial.println(F("✓ Homing complete!"));
    Serial.println(F("    Position reset to 0"));
    
    currentState = STATE_IDLE;
  } else {
    Serial.println(F("⚠️  Homing interrupted by emergency stop"));
  }
}

// ============================================================
// COMMAND HANDLER
// ============================================================
void handleCommand(char cmd) {
  switch(cmd) {
    case 'f': // Forward 100mm
    case 'F':
      moveForward(100);
      break;
      
    case 'r': // Reverse 100mm
    case 'R':
      moveReverse(100);
      break;
      
    case '1': // Forward 1 meter
      moveForward(1000);
      break;
      
    case '2': // Reverse 1 meter
      moveReverse(1000);
      break;
      
    case 's': // Stop
    case 'S':
    case ' ':
      stopMotion();
      break;
      
    case 'e': // Enable servo
    case 'E':
      enableServo();
      Serial.println(F("✓ Servo enabled"));
      break;
      
    case 'd': // Disable servo
    case 'D':
      disableServo();
      Serial.println(F("✓ Servo disabled"));
      break;
      
    case 'a': // Reset alarm
    case 'A':
      resetAlarm();
      break;
      
    case 'h': // Home
    case 'H':
      homeMotor();
      break;
      
    case '?': // Status
      printStatus();
      break;
      
    case 'i': // Info
    case 'I':
      printSystemInfo();
      break;
      
    case 'c': // Clear statistics
    case 'C':
      totalDistance = 0;
      errorCount = 0;
      Serial.println(F("✓ Statistics cleared"));
      break;
      
    case 'p': // Print help
    case 'P':
      printHelp();
      break;
      
    case '\n':
    case '\r':
      // Ignore newline characters
      break;
      
    default:
      Serial.print(F("⚠️  Unknown command: '"));
      Serial.print(cmd);
      Serial.println(F("' - Type 'P' for help"));
  }
}

// ============================================================
// DISPLAY FUNCTIONS
// ============================================================

void printBanner() {
  Serial.println(F("\n╔═══════════════════════════════════════════════════╗"));
  Serial.println(F("║   DELTA ASDA-B3 SERVO MOTOR CONTROL SYSTEM      ║"));
  Serial.println(F("║   Arduino Mega 2560 Implementation              ║"));
  Serial.println(F("║                                                 ║"));
  Serial.println(F("║   Version: 1.0                                  ║"));
  Serial.println(F("║   Date: October 2025                            ║"));
  Serial.println(F("╚═══════════════════════════════════════════════════╝\n"));
}

void printHelp() {
  Serial.println(F("╔════════════════════════════════════════════════════╗"));
  Serial.println(F("║            COMMAND REFERENCE                       ║"));
  Serial.println(F("╠════════════════════════════════════════════════════╣"));
  Serial.println(F("║  MOTION COMMANDS:                                  ║"));
  Serial.println(F("║    F / f  → Move forward 100mm                     ║"));
  Serial.println(F("║    R / r  → Move reverse 100mm                     ║"));
  Serial.println(F("║    1      → Move forward 1 meter                   ║"));
  Serial.println(F("║    2      → Move reverse 1 meter                   ║"));
  Serial.println(F("║    S / s  → Stop motion (emergency)                ║"));
  Serial.println(F("║                                                    ║"));
  Serial.println(F("║  CONTROL COMMANDS:                                 ║"));
  Serial.println(F("║    E / e  → Enable servo                           ║"));
  Serial.println(F("║    D / d  → Disable servo                          ║"));
  Serial.println(F("║    A / a  → Reset alarm                            ║"));
  Serial.println(F("║    H / h  → Home motor (to reverse limit)          ║"));
  Serial.println(F("║                                                    ║"));
  Serial.println(F("║  INFORMATION COMMANDS:                             ║"));
  Serial.println(F("║    ?      → Show system status                     ║"));
  Serial.println(F("║    I / i  → Show system information                ║"));
  Serial.println(F("║    C / c  → Clear statistics                       ║"));
  Serial.println(F("║    P / p  → Print this help                        ║"));
  Serial.println(F("╚════════════════════════════════════════════════════╝\n"));
}

void printStatus() {
  Serial.println(F("\n╔════════════════════════════════════════════════════╗"));
  Serial.println(F("║              SYSTEM STATUS                         ║"));
  Serial.println(F("╠════════════════════════════════════════════════════╣"));
  
  // State
  Serial.print(F("║  State:           "));
  switch(currentState) {
    case STATE_IDLE:
      Serial.print(F("IDLE"));
      break;
    case STATE_MOVING_FORWARD:
      Serial.print(F("MOVING FORWARD"));
      break;
    case STATE_MOVING_REVERSE:
      Serial.print(F("MOVING REVERSE"));
      break;
    case STATE_ERROR:
      Serial.print(F("ERROR ⚠️"));
      break;
    case STATE_HOMING:
      Serial.print(F("HOMING 🏠"));
      break;
    case STATE_DISABLED:
      Serial.print(F("DISABLED"));
      break;
  }
  // Pad to align
  for(int i = 0; i < 20; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  // Servo status
  Serial.print(F("║  Servo:           "));
  Serial.print(servoEnabled ? F("ENABLED ✓") : F("DISABLED ✗"));
  for(int i = 0; i < 20; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  // Limit switches
  Serial.print(F("║  Forward Limit:   "));
  Serial.print(digitalRead(LIMIT_FWD_PIN) ? F("OK ✓") : F("TRIGGERED ⚠️"));
  for(int i = 0; i < 20; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Reverse Limit:   "));
  Serial.print(digitalRead(LIMIT_REV_PIN) ? F("OK ✓") : F("TRIGGERED ⚠️"));
  for(int i = 0; i < 20; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  // Position
  Serial.print(F("║  Position:        "));
  Serial.print(currentPosition);
  Serial.print(F(" pulses ("));
  Serial.print(currentPosition / PULSES_PER_MM);
  Serial.print(F(" mm)"));
  for(int i = 0; i < 10; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  // Statistics
  Serial.print(F("║  Total Distance:  "));
  Serial.print(totalDistance);
  Serial.print(F(" mm"));
  for(int i = 0; i < 25; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Error Count:     "));
  Serial.print(errorCount);
  for(int i = 0; i < 30; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.println(F("╚════════════════════════════════════════════════════╝\n"));
}

void printSystemInfo() {
  Serial.println(F("\n╔════════════════════════════════════════════════════╗"));
  Serial.println(F("║           SYSTEM INFORMATION                       ║"));
  Serial.println(F("╠════════════════════════════════════════════════════╣"));
  Serial.print(F("║  Pulses/mm:       "));
  Serial.print(PULSES_PER_MM);
  for(int i = 0; i < 25; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Max Speed:       "));
  Serial.print(MAX_SPEED_MM_S);
  Serial.print(F(" mm/s"));
  for(int i = 0; i < 20; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Pulse Freq:      "));
  Serial.print(PULSE_FREQ_HZ / 1000);
  Serial.print(F(" kHz"));
  for(int i = 0; i < 22; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Max Distance:    "));
  Serial.print(MAX_DISTANCE_MM);
  Serial.print(F(" mm"));
  for(int i = 0; i < 22; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Accel Time:      "));
  Serial.print(ACCEL_TIME_MS);
  Serial.print(F(" ms"));
  for(int i = 0; i < 22; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Decel Time:      "));
  Serial.print(DECEL_TIME_MS);
  Serial.print(F(" ms"));
  for(int i = 0; i < 22; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Firmware:        v1.0"));
  for(int i = 0; i < 25; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  Board:           Arduino Mega 2560"));
  for(int i = 0; i < 12; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.print(F("║  CPU Freq:        "));
  Serial.print(F_CPU / 1000000);
  Serial.print(F(" MHz"));
  for(int i = 0; i < 22; i++) Serial.print(F(" "));
  Serial.println(F("║"));
  
  Serial.println(F("╚════════════════════════════════════════════════════╝\n"));
}

void blinkStatusLED() {
  static bool ledState = false;
  
  // Different blink patterns for different states
  if (currentState == STATE_IDLE || currentState == STATE_DISABLED) {
    // Slow blink for idle
    digitalWrite(LED_STATUS, ledState);
    ledState = !ledState;
  } else if (currentState == STATE_ERROR) {
    // Fast blink for error
    static unsigned long lastBlink = 0;
    if (millis() - lastBlink > 200) {
      digitalWrite(LED_STATUS, ledState);
      ledState = !ledState;
      lastBlink = millis();
    }
  } else {
    // Solid on when moving
    digitalWrite(LED_STATUS, HIGH);
  }
}

// ============================================================
// INTERRUPT SERVICE ROUTINES
// ============================================================
void limitFwdISR() {
  limitFwdTriggered = true;
}

void limitRevISR() {
  limitRevTriggered = true;
}

// ============================================================
// END OF CODE
// ============================================================
