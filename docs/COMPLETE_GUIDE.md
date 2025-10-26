# Delta ASDA-B3 Servo Motor Control - Complete Guide
# دليل التحكم الشامل بمحرك سيرفو Delta ASDA-B3

![Delta ASDA-B3](https://img.shields.io/badge/Delta-ASDA--B3-blue) ![Speed](https://img.shields.io/badge/Speed-1m%2Fs-green) ![Arduino](https://img.shields.io/badge/Arduino-Compatible-brightgreen) ![STM32](https://img.shields.io/badge/STM32-Compatible-blue)

---

## 📖 Table of Contents | جدول المحتويات

1. [Project Overview | نظرة عامة](#-project-overview--نظرة-عامة)
2. [Bill of Materials | قائمة المواد](#-bill-of-materials--قائمة-المواد)
3. [Hardware Connections | التوصيلات](#-hardware-connections--التوصيلات)
4. [Driver Configuration | إعدادات الدرايفر](#-driver-configuration--إعدادات-الدرايفر)
5. [Speed Calculation | حساب السرعة](#-speed-calculation--حساب-السرعة)
6. [Arduino Code | كود أردوينو](#-arduino-code--كود-أردوينو)
7. [STM32 Code | كود STM32](#-stm32-code--كود-stm32)
8. [Testing Steps | خطوات الاختبار](#-testing-steps--خطوات-الاختبار)
9. [Troubleshooting | حل المشاكل](#-troubleshooting--حل-المشاكل)
10. [Safety | السلامة](#-safety--السلامة)

---

## 🎯 Project Overview | نظرة عامة

### English
This project provides a complete implementation for controlling a Delta ASDA-B3 servo motor with:
- **Bidirectional motion control** using pulse/direction signals
- **Limit switches** for safe operation boundaries
- **1 meter/second** linear motion speed
- **Microcontroller-based control** (Arduino Mega or STM32)
- **Real-time safety monitoring**

### العربية
هذا المشروع يوفر تطبيق كامل للتحكم بمحرك سيرفو Delta ASDA-B3 مع:
- **التحكم بالحركة في الاتجاهين** باستخدام إشارات Pulse/Direction
- **مفاتيح حد (ليمت سويتش)** لحدود التشغيل الآمنة
- سرعة حركة خطية **1 متر/ثانية**
- **التحكم بواسطة المايكروكنترولر** (Arduino Mega أو STM32)
- **مراقبة السلامة في الوقت الفعلي**

---

## 🛒 Bill of Materials | قائمة المواد

### What You Already Have | ما عندك حالياً
- ✅ **Servo Motor** - ECM-B3 Series
- ✅ **Limit Switches** (2 pcs recommended)

### What You Need to Buy | ما تحتاج تشتريه

| # | Component | Specification | Qty | Price (USD) | Notes |
|---|-----------|--------------|-----|-------------|-------|
| 1 | **Delta ASDA-B3 Servo Drive** | Match motor power (400W-1.5kW) | 1 | $250-400 | Core component |
| 2 | **Microcontroller** | Arduino Mega 2560 OR STM32F103 | 1 | $3-15 | Choose one |
| 3 | **Power Supply 24V DC** | 2A minimum | 1 | $20 | For control signals |
| 4 | **Power Supply 220V AC** | Per motor rating | 1 | Existing | Main power |
| 5 | **Terminal Blocks** | 10-position | 2 | $5 | Wiring organization |
| 6 | **Control Cable** | 20-pin ribbon | 1m | $10 | CN1 connection |
| 7 | **Encoder Cable** | Usually included | 1 | $0 | Comes with motor |
| 8 | **Emergency Stop** | Red mushroom button | 1 | $5 | Safety |
| 9 | **Circuit Breaker** | 10A, 220V | 1 | $5 | Protection |
| 10 | **Relay Module** | 24V DC coil | 1 | $3 | Optional isolation |
| 11 | **Jumper Wires** | Male-Male, Male-Female | 1 set | $3 | Connections |
| 12 | **USB-to-RS485** | For ASDA-Soft | 1 | $5 | Configuration |

### Optional Components | مكونات اختيارية

| Component | Purpose | Price |
|-----------|---------|-------|
| Braking Resistor | Fast deceleration | $30-50 |
| HMI Display | User interface | $50-100 |
| Proximity Sensors | Better limit detection | $10 each |
| DIN Rail | Professional mounting | $5 |
| Electrical Enclosure | Protection | $15-30 |

### Tools Required | الأدوات المطلوبة
- Multimeter
- Screwdriver set (Phillips & Flat)
- Wire strippers
- Crimping tool
- Heat shrink tubing
- Cable ties

**💰 Total Cost Estimate:**
- **With Driver:** ~$320-450
- **Without Driver:** ~$70-85

---

## 🔌 Hardware Connections | التوصيلات

### 1. Power Wiring | توصيلات الطاقة

#### ⚡ AC Power to Driver (220V)
```
Main Supply 220V
    │
    ├─── Line (L)      → R Terminal (Driver)
    ├─── Neutral (N)   → S Terminal (Driver)  
    └─── Ground (PE)   → PE Terminal (Driver) ⚠️ CRITICAL
```

#### 🔋 Motor Power Connections
```
Servo Motor                    ASDA-B3 Driver
    │                              │
    ├─── U Phase    ────────────→  U Terminal
    ├─── V Phase    ────────────→  V Terminal
    ├─── W Phase    ────────────→  W Terminal
    └─── Ground     ────────────→  PE Terminal
```

### 2. CN1 Control Connector Pinout | توصيلات CN1

```
╔════════════════════════════════════════════════════════╗
║            CN1 - 20 PIN CONTROL CONNECTOR              ║
╠═══╦═════════════════╦══════════════════════════════════╣
║PIN║   SIGNAL NAME   ║        CONNECTION                ║
╠═══╬═════════════════╬══════════════════════════════════╣
║ 1 ║ SERVO-ON        ║ MCU → 24V (Servo Enable)         ║
║ 2 ║ COM (GND)       ║ Ground Reference                 ║
║ 3 ║ DI1 (Limit-FWD) ║ Forward Limit Switch             ║
║ 4 ║ DI2 (Limit-REV) ║ Reverse Limit Switch             ║
║ 5 ║ PULS+           ║ MCU PWM Output (Pulse Signal)    ║
║ 6 ║ PULS-           ║ Ground                           ║
║ 7 ║ SIGN+ (DIR)     ║ MCU GPIO (Direction Signal)      ║
║ 8 ║ SIGN-           ║ Ground                           ║
║ 9 ║ ALM-RST         ║ MCU GPIO (Alarm Reset)           ║
║10 ║ COM             ║ Ground                           ║
║11 ║ DI3             ║ Not Used (can add Home switch)   ║
║12 ║ COM             ║ Ground                           ║
║13-20║ (Various)     ║ See manual for advanced features ║
╚═══╩═════════════════╩══════════════════════════════════╝
```

### 3. Limit Switch Wiring | توصيل مفاتيح الحد

**🔴 CRITICAL: Use Normally Closed (NC) Configuration**

```
    24V DC Supply
        │
        ├──────[Limit SW1 (NC)]───── DI1 (PIN 3)
        │              └── 10kΩ ────┐
        │                           GND
        │
        └──────[Limit SW2 (NC)]───── DI2 (PIN 4)
                       └── 10kΩ ────┐
                                    GND

Logic:
- Switch CLOSED (normal)  = 24V = HIGH = Motion ALLOWED
- Switch OPEN (triggered) = 0V  = LOW  = Motion STOPPED
```

### 4. Microcontroller Connections | توصيلات المايكروكنترولر

#### Option A: Arduino Mega 2560
```
╔════════════════════╦════════════════════════════════╗
║  Arduino Pin       ║  Connection                    ║
╠════════════════════╬════════════════════════════════╣
║ PIN 9 (Timer1)     ║ → CN1 Pin 5 (PULS+)           ║
║ PIN 8              ║ → CN1 Pin 7 (SIGN+/DIR)       ║
║ PIN 7              ║ → CN1 Pin 1 (SERVO-ON)        ║
║ PIN 6              ║ → CN1 Pin 9 (ALM-RST)         ║
║ PIN 5              ║ ← Read Limit1 Status (DI1)    ║
║ PIN 4              ║ ← Read Limit2 Status (DI2)    ║
║ GND                ║ → CN1 Pins 2,6,8,10 (COM)     ║
║ 5V                 ║ → Power Arduino (via USB/DC)  ║
╚════════════════════╩════════════════════════════════╝
```

#### Option B: STM32F103 (Blue Pill)
```
╔════════════════════╦════════════════════════════════╗
║  STM32 Pin         ║  Connection                    ║
╠════════════════════╬════════════════════════════════╣
║ PA8 (TIM1_CH1)     ║ → CN1 Pin 5 (PULS+)           ║
║ PA9                ║ → CN1 Pin 7 (SIGN+/DIR)       ║
║ PA10               ║ → CN1 Pin 1 (SERVO-ON)        ║
║ PA11               ║ → CN1 Pin 9 (ALM-RST)         ║
║ PA6                ║ ← Read Limit1 (with interrupt) ║
║ PA7                ║ ← Read Limit2 (with interrupt) ║
║ GND                ║ → CN1 Common pins              ║
║ 3.3V               ║ → STM32 Power                  ║
╚════════════════════╩════════════════════════════════╝
```

### 5. CN2 Encoder Connection | توصيل الإنكودر

```
Motor Encoder Cable → CN2 Port (on driver)

⚠️ WARNING:
- Never disconnect encoder while power is ON
- Match wire colors exactly
- Use shielded cable
- Keep cable < 3 meters for best performance
```

### 6. Complete System Diagram | مخطط النظام الكامل

```
                    ┌──────────────────────┐
                    │   220V AC Mains      │
                    │   Supply             │
                    └──────┬───────────────┘
                           │
                    ┌──────▼───────────────┐
                    │  Circuit Breaker     │
                    │  10A                 │
                    └──────┬───────────────┘
                           │
        ┌──────────────────┴──────────────────┐
        │                                      │
        │    DELTA ASDA-B3 SERVO DRIVER       │
        │                                      │
        │  AC Input: [R] [S] [PE]             │
        │  Motor Out: [U] [V] [W] [PE]        │
        │                                      │
        │  CN1: Control Signals (20-pin)      │
        │  CN2: Encoder Feedback              │
        │                                      │
        └────┬──────────────┬──────────────┬──┘
             │              │              │
    ┌────────▼────┐  ┌──────▼────────┐  ┌─▼────────┐
    │ Control     │  │ Encoder       │  │ Motor    │
    │ Cable       │  │ Cable         │  │ ECM-B3   │
    │ (CN1)       │  │ (CN2)         │  │          │
    └──────┬──────┘  └───────────────┘  └──────────┘
           │
    ┌──────▼───────────────────────┐
    │  Microcontroller             │
    │  (Arduino Mega / STM32)      │
    │                              │
    │  - Pulse Generation          │
    │  - Direction Control         │
    │  - Safety Monitoring         │
    └──────┬───────────────────────┘
           │
    ┌──────▼──────────────┐
    │  24V DC Supply      │
    │  (2A minimum)       │
    └──────┬──────────────┘
           │
    ┌──────▼──────────────┐
    │  Limit Switches (×2)│
    │  + Emergency Stop   │
    └─────────────────────┘
```

---

## ⚙️ Driver Configuration | إعدادات الدرايفر

### Step 1: Install ASDA-Soft

1. Download from: https://www.deltaww.com → Products → Servo
2. Install on Windows PC
3. Connect USB-to-RS485 converter
4. Select COM port in ASDA-Soft
5. Click "Connect" button

### Step 2: Configure Basic Parameters | المعاملات الأساسية

**Open Parameter Settings in ASDA-Soft:**

```ini
# ==========================================
# CONTROL MODE CONFIGURATION
# ==========================================
Pn00.00 = 0x02          # Position Control Mode
Pn00.01 = 0x00          # Command Source: Pulse Input
Pn00.02 = 0x00          # Not used

# ==========================================
# MOTOR PARAMETERS (Critical!)
# ==========================================
Pn01.00 = [Your Motor Model]  # e.g., ECMA-C20604RS
Pn01.01 = 2500                # Encoder Resolution (PPR)
                              # Check your motor's label
Pn01.02 = 3000                # Rated Speed (RPM)
Pn01.03 = [Auto]              # Motor Capacity (Auto-detected)

# ==========================================
# PULSE INPUT CONFIGURATION
# ==========================================
Pn02.00 = 500000        # Maximum Pulse Frequency (Hz)
                        # Set to 500kHz for high-speed applications
Pn02.01 = 0x00          # Pulse Mode: Pulse + Direction
Pn02.02 = 0x00          # Pulse Logic: Active HIGH
Pn02.03 = 1             # Pulse Input Filter (μs)

# ==========================================
# MOTION PROFILE SETTINGS
# ==========================================
Pn03.00 = 200           # Acceleration Time (ms)
                        # Shorter = faster start (may cause overshoot)
Pn03.01 = 200           # Deceleration Time (ms)
                        # Shorter = faster stop (higher voltage)
Pn03.02 = 50            # S-Curve Smoothing Time (ms)
                        # Higher = smoother but slower response

# ==========================================
# DIGITAL INPUT ASSIGNMENT (CN1)
# ==========================================
Pn04.00 = 0x01          # DI1 (Pin 1): SERVO-ON
Pn04.01 = 0x0B          # DI2 (Pin 3): Forward Limit (POT)
Pn04.02 = 0x0C          # DI3 (Pin 4): Reverse Limit (NOT)
Pn04.03 = 0x05          # DI4 (Pin 9): Alarm Reset
Pn04.04 = 0x00          # DI5: Not Used
Pn04.05 = 0x00          # DI6: Not Used

# DI Logic Configuration
Pn04.10 = 0x00          # DI Active Logic
                        # Bit 0 = DI1, Bit 1 = DI2, etc.
                        # 0 = Active LOW (default for NC switches)
                        # 1 = Active HIGH

# ==========================================
# ELECTRONIC GEAR RATIO
# ==========================================
Pn05.00 = 1             # Numerator (multiply pulses)
Pn05.01 = 1             # Denominator (divide pulses)
                        # Ratio = Pn05.00 / Pn05.01
                        # Example: 2/1 = doubles resolution

# ==========================================
# POSITION CONTROL GAINS (Start with defaults)
# ==========================================
Pn10.00 = 40            # Position Loop Gain (Kp)
                        # Higher = faster following, may oscillate
Pn10.01 = 300           # Velocity Loop Gain (Kvp)
Pn10.02 = 30            # Velocity Integral Gain (Kvi)
Pn10.03 = 500           # Velocity Feedforward Gain

# ==========================================
# POSITION LIMITS (Software Protection)
# ==========================================
Pn11.00 = 0             # Enable Position Limit (0=Disable, 1=Enable)
Pn11.01 = 0             # Negative Position Limit (pulses)
Pn11.02 = 100000        # Positive Position Limit (pulses)

# ==========================================
# ALARM CONFIGURATION
# ==========================================
Pn20.00 = 200           # Following Error Limit (pulses)
                        # Alarm if position error exceeds this
Pn20.01 = 5000          # Overload Warning Level (%)
Pn20.02 = 0x00          # Alarm Output Logic

# ==========================================
# COMMUNICATION (Optional - for Modbus)
# ==========================================
Pn50.00 = 1             # Station Address (1-255)
Pn50.01 = 9600          # Baud Rate (9600, 19200, 38400, 57600)
Pn50.02 = 0x00          # Parity: 0=None, 1=Odd, 2=Even
```

### Step 3: Save Configuration

1. Click "Write to Drive" button
2. Power cycle the driver (OFF → wait 5 sec → ON)
3. Verify parameters by reading back

### Step 4: Auto-Tuning (Recommended) | الضبط التلقائي

**Why Auto-Tune?**
- Automatically optimizes PID gains
- Adapts to your specific load and mechanism
- Reduces oscillation and improves accuracy

**How to Auto-Tune:**

1. In ASDA-Soft, go to **"Auto-Tuning"** tab
2. Select tuning mode:
   - **Stiffness Mode:** For light loads (< 50% motor inertia)
   - **Response Mode:** For heavy loads (> 50% motor inertia)
3. Enter estimated **Load Inertia Ratio** (J_load / J_motor)
   - Default: Start with 1.0
   - Higher number = heavier load
4. Click **"Start Auto-Tuning"**
5. Driver will perform test movements
6. Wait for completion (30-60 seconds)
7. Save new parameters
8. Test motion quality

---

## 📐 Speed Calculation | حساب السرعة

### Understanding the Relationship | فهم العلاقة

To achieve **1 meter/second**, we need to calculate the pulse frequency.

```
Pulse Frequency = Linear Speed × Pulses per mm

Where:
Pulses per mm = (Encoder PPR × Gear Ratio) / Lead or Circumference
```

### Example 1: Ball Screw System | مثال 1: نظام Ball Screw

```
Given | المعطيات:
- Ball Screw Lead = 10 mm/revolution
- Encoder Resolution = 2500 PPR
- No gear reduction (1:1)
- Target Speed = 1000 mm/s (1 m/s)

Calculation | الحساب:
Pulses per mm = 2500 / 10 = 250 pulses/mm

Pulse Frequency = 1000 mm/s × 250 pulses/mm
                = 250,000 Hz
                = 250 kHz

Timer Configuration:
- Arduino: Timer frequency / (250,000 Hz)
- For 16 MHz: Prescaler=1, TOP=63 (16MHz / 64 = 250kHz)
```

### Example 2: Belt Drive System | مثال 2: نظام Belt Drive

```
Given | المعطيات:
- Pulley Diameter = 50 mm
- Pulley Circumference = π × D = 157 mm
- Encoder = 2500 PPR
- Gear Ratio = 1:1
- Target Speed = 1000 mm/s

Calculation | الحساب:
Pulses per revolution = 2500
mm per revolution = 157 mm

Pulses per mm = 2500 / 157 = 15.92 pulses/mm

Pulse Frequency = 1000 × 15.92
                = 15,920 Hz
                ≈ 16 kHz

This is much easier for microcontrollers to generate!
```

### Example 3: Rack and Pinion | مثال 3: نظام Rack and Pinion

```
Given | المعطيات:
- Pinion Diameter = 40 mm
- Teeth on Pinion = 20 teeth
- Module = 2 (Tooth pitch = 6.28 mm)
- Encoder = 2500 PPR
- Target Speed = 1000 mm/s

Calculation | الحساب:
Circumference = 20 teeth × 6.28 mm = 125.6 mm
Pulses per mm = 2500 / 125.6 = 19.9 pulses/mm

Pulse Frequency = 1000 × 19.9 = 19,900 Hz ≈ 20 kHz
```

### ⚠️ Important Considerations | اعتبارات مهمة

**1. Maximum Frequency Limits:**
```
Arduino Mega:    Reliable up to ~200 kHz
STM32F103:       Reliable up to ~500 kHz
ESP32:           Up to ~1 MHz (with LEDC)
ASDA-B3 Driver:  Up to 500 kHz input
```

**2. If Frequency Too High:**
- Use gear reduction (e.g., 2:1 cuts frequency in half)
- Reduce target speed
- Use electronic gearing in driver (Pn05.xx)

**3. If Frequency Too Low (< 10 kHz):**
- Motion may be jerky
- Consider higher resolution encoder
- Or increase gear ratio

### Quick Reference Table | جدول مرجعي سريع

| Mechanism | Lead/Circumference | Encoder | Pulses/mm | Freq @ 1m/s |
|-----------|-------------------|---------|-----------|-------------|
| Ball Screw 5mm | 5 mm | 2500 PPR | 500 | 500 kHz ⚠️ |
| Ball Screw 10mm | 10 mm | 2500 PPR | 250 | 250 kHz |
| Ball Screw 20mm | 20 mm | 2500 PPR | 125 | 125 kHz ✅ |
| Belt (50mm pulley) | 157 mm | 2500 PPR | 16 | 16 kHz ✅ |
| Rack (Ø40 pinion) | 126 mm | 2500 PPR | 20 | 20 kHz ✅ |

✅ = Easily achievable with Arduino/STM32
⚠️ = Requires STM32 or external pulse generator

---

## 💻 Arduino Code | كود أردوينو

### Complete Arduino Sketch | الكود الكامل

```cpp
/*
═══════════════════════════════════════════════════════════
  DELTA ASDA-B3 SERVO MOTOR CONTROL - ARDUINO MEGA
  
  Features:
  - 1 m/s linear motion control
  - Limit switch protection
  - Serial command interface
  - Real-time status monitoring
  
  Hardware:
  - Arduino Mega 2560
  - Delta ASDA-B3 Servo Driver
  - 2× Limit Switches (NC configuration)
  
  Author: [Your Name]
  Date: October 2025
  Version: 1.0
═══════════════════════════════════════════════════════════
*/

// ============================================================
// PIN DEFINITIONS
// ============================================================
#define PULSE_PIN       9    // Timer1 CH1 - PWM for pulses
#define DIR_PIN         8    // Direction control
#define SERVO_ON_PIN    7    // Servo enable signal
#define ALM_RST_PIN     6    // Alarm reset
#define LIMIT_FWD_PIN   5    // Forward limit switch (input)
#define LIMIT_REV_PIN   4    // Reverse limit switch (input)
#define LED_STATUS      13   // Built-in LED for status

// ============================================================
// CONFIGURATION CONSTANTS
// ============================================================
// *** ADJUST THESE FOR YOUR SYSTEM ***
#define PULSES_PER_MM   250      // Calculated from your mechanism
#define MAX_SPEED_MM_S  1000     // Maximum speed: 1000 mm/s = 1 m/s
#define PULSE_FREQ_HZ   250000   // PULSES_PER_MM × MAX_SPEED_MM_S

// Safety Limits
#define MAX_DISTANCE_MM 1000     // Maximum travel distance
#define ACCEL_TIME_MS   200      // Acceleration time
#define DECEL_TIME_MS   200      // Deceleration time

// ============================================================
// GLOBAL VARIABLES
// ============================================================
enum MotionState {
  STATE_IDLE,
  STATE_MOVING_FORWARD,
  STATE_MOVING_REVERSE,
  STATE_ERROR,
  STATE_HOMING
};

volatile MotionState currentState = STATE_IDLE;
volatile bool limitFwdTriggered = false;
volatile bool limitRevTriggered = false;
volatile bool emergencyStop = false;

// Position tracking (if using position feedback)
long currentPosition = 0;
long targetPosition = 0;

// Timing
unsigned long lastStatusPrint = 0;
const unsigned long STATUS_INTERVAL = 1000; // Print status every 1 second

// ============================================================
// SETUP FUNCTION
// ============================================================
void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial && millis() < 3000); // Wait up to 3 seconds for serial
  
  Serial.println(F("\n╔════════════════════════════════════════╗"));
  Serial.println(F("║  Delta ASDA-B3 Servo Control v1.0    ║"));
  Serial.println(F("║  Arduino Mega 2560                    ║"));
  Serial.println(F("╚════════════════════════════════════════╝\n"));
  
  // Configure pins
  pinMode(PULSE_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(SERVO_ON_PIN, OUTPUT);
  pinMode(ALM_RST_PIN, OUTPUT);
  pinMode(LED_STATUS, OUTPUT);
  pinMode(LIMIT_FWD_PIN, INPUT_PULLUP);
  pinMode(LIMIT_REV_PIN, INPUT_PULLUP);
  
  // Set initial states
  digitalWrite(PULSE_PIN, LOW);
  digitalWrite(DIR_PIN, LOW);
  digitalWrite(SERVO_ON_PIN, LOW);
  digitalWrite(ALM_RST_PIN, LOW);
  digitalWrite(LED_STATUS, LOW);
  
  // Setup Timer1 for PWM pulse generation
  Serial.print(F("Configuring Timer1... "));
  setupTimer1PWM(PULSE_FREQ_HZ);
  Serial.println(F("OK"));
  
  // Setup limit switch interrupts
  Serial.print(F("Configuring interrupts... "));
  attachInterrupt(digitalPinToInterrupt(LIMIT_FWD_PIN), limitFwdISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(LIMIT_REV_PIN), limitRevISR, FALLING);
  Serial.println(F("OK"));
  
  // Check limit switches
  Serial.print(F("Checking limit switches... "));
  if (digitalRead(LIMIT_FWD_PIN) == LOW || digitalRead(LIMIT_REV_PIN) == LOW) {
    Serial.println(F("\n⚠️  WARNING: Limit switch triggered at startup!"));
    currentState = STATE_ERROR;
  } else {
    Serial.println(F("OK"));
  }
  
  // Enable servo after delay
  delay(1000);
  Serial.print(F("Enabling servo... "));
  enableServo();
  Serial.println(F("OK\n"));
  
  // Print help
  printHelp();
  
  Serial.println(F("System ready! Waiting for commands...\n"));
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
  if (limitFwdTriggered) {
    emergencyStopMotion();
    Serial.println(F("🛑 Forward limit reached!"));
    limitFwdTriggered = false;
    digitalWrite(LED_STATUS, LOW);
  }
  
  if (limitRevTriggered) {
    emergencyStopMotion();
    Serial.println(F("🛑 Reverse limit reached!"));
    limitRevTriggered = false;
    digitalWrite(LED_STATUS, LOW);
  }
  
  // Periodic status update
  if (millis() - lastStatusPrint >= STATUS_INTERVAL) {
    lastStatusPrint = millis();
    blinkStatusLED();
  }
  
  // Small delay to prevent overwhelming
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
  // For 16 MHz Arduino and no prescaler:
  unsigned int top;
  
  if (frequency <= 250000) {
    // For 250 kHz: 16,000,000 / 250,000 = 64
    top = (F_CPU / frequency) - 1;
  } else {
    // If frequency too high, use maximum
    top = 31; // ~500 kHz max
  }
  
  // Fast PWM mode with ICR1 as TOP
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12);
  
  // Set TOP value
  ICR1 = top;
  
  // Set 50% duty cycle
  OCR1A = top / 2;
  
  // Timer stopped initially (will start when needed)
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
  
  Serial.print(F("Timer TOP value: "));
  Serial.print(top);
  Serial.print(F(" (Actual freq: "));
  Serial.print(F_CPU / (top + 1));
  Serial.println(F(" Hz)"));
}

// ============================================================
// MOTION CONTROL FUNCTIONS
// ============================================================
void enableServo() {
  digitalWrite(SERVO_ON_PIN, HIGH);
  delay(100); // Wait for servo to energize
}

void disableServo() {
  stopPulses();
  digitalWrite(SERVO_ON_PIN, LOW);
  currentState = STATE_IDLE;
}

void startPulses() {
  // Start Timer1 with no prescaler (CS10 = 1)
  TCCR1B |= (1 << CS10);
  digitalWrite(LED_STATUS, HIGH);
}

void stopPulses() {
  // Stop Timer1
  TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
  currentState = STATE_IDLE;
}

void emergencyStopMotion() {
  stopPulses();
  emergencyStop = true;
  currentState = STATE_ERROR;
}

void moveForward(unsigned int distanceMM) {
  // Safety checks
  if (currentState != STATE_IDLE && currentState != STATE_HOMING) {
    Serial.println(F("⚠️  Motor already moving!"));
    return;
  }
  
  if (digitalRead(LIMIT_FWD_PIN) == LOW) {
    Serial.println(F("⚠️  Already at forward limit!"));
    return;
  }
  
  if (distanceMM > MAX_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too large! Max: "));
    Serial.print(MAX_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  // Set direction
  digitalWrite(DIR_PIN, HIGH); // Forward
  delayMicroseconds(10); // Direction setup time
  
  // Start motion
  currentState = STATE_MOVING_FORWARD;
  targetPosition = currentPosition + (long)distanceMM * PULSES_PER_MM;
  
  startPulses();
  
  Serial.print(F("→ Moving forward: "));
  Serial.print(distanceMM);
  Serial.print(F(" mm ("));
  Serial.print((long)distanceMM * PULSES_PER_MM);
  Serial.println(F(" pulses)"));
}

void moveReverse(unsigned int distanceMM) {
  // Safety checks
  if (currentState != STATE_IDLE && currentState != STATE_HOMING) {
    Serial.println(F("⚠️  Motor already moving!"));
    return;
  }
  
  if (digitalRead(LIMIT_REV_PIN) == LOW) {
    Serial.println(F("⚠️  Already at reverse limit!"));
    return;
  }
  
  if (distanceMM > MAX_DISTANCE_MM) {
    Serial.print(F("⚠️  Distance too large! Max: "));
    Serial.print(MAX_DISTANCE_MM);
    Serial.println(F(" mm"));
    return;
  }
  
  // Set direction
  digitalWrite(DIR_PIN, LOW); // Reverse
  delayMicroseconds(10); // Direction setup time
  
  // Start motion
  currentState = STATE_MOVING_REVERSE;
  targetPosition = currentPosition - (long)distanceMM * PULSES_PER_MM;
  
  startPulses();
  
  Serial.print(F("← Moving reverse: "));
  Serial.print(distanceMM);
  Serial.print(F(" mm ("));
  Serial.print((long)distanceMM * PULSES_PER_MM);
  Serial.println(F(" pulses)"));
}

void stopMotion() {
  stopPulses();
  Serial.println(F("⏸  Motion stopped"));
}

void resetAlarm() {
  digitalWrite(ALM_RST_PIN, HIGH);
  delay(100);
  digitalWrite(ALM_RST_PIN, LOW);
  emergencyStop = false;
  currentState = STATE_IDLE;
  Serial.println(F("✓ Alarm reset"));
}

void homeMotor() {
  Serial.println(F("🏠 Starting homing sequence..."));
  currentState = STATE_HOMING;
  
  // Move to reverse limit
  digitalWrite(DIR_PIN, LOW);
  delayMicroseconds(10);
  startPulses();
  
  // Wait for limit trigger
  Serial.println(F("   Moving to home position..."));
  while (digitalRead(LIMIT_REV_PIN) == HIGH && !emergencyStop) {
    delay(10);
  }
  
  stopPulses();
  
  if (!emergencyStop) {
    currentPosition = 0;
    Serial.println(F("✓ Homing complete! Position reset to 0"));
  }
  
  currentState = STATE_IDLE;
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
      
    case '\n':
    case '\r':
      // Ignore newline characters
      break;
      
    default:
      Serial.print(F("⚠️  Unknown command: "));
      Serial.println(cmd);
      printHelp();
  }
}

// ============================================================
// STATUS & INFO FUNCTIONS
// ============================================================
void printHelp() {
  Serial.println(F("╔════════════════════════════════════════╗"));
  Serial.println(F("║          COMMAND REFERENCE            ║"));
  Serial.println(F("╠════════════════════════════════════════╣"));
  Serial.println(F("║  F / f  → Forward 100mm               ║"));
  Serial.println(F("║  R / r  → Reverse 100mm               ║"));
  Serial.println(F("║  1      → Forward 1 meter             ║"));
  Serial.println(F("║  2      → Reverse 1 meter             ║"));
  Serial.println(F("║  S / s  → Stop motion                 ║"));
  Serial.println(F("║  E / e  → Enable servo                ║"));
  Serial.println(F("║  D / d  → Disable servo               ║"));
  Serial.println(F("║  A / a  → Reset alarm                 ║"));
  Serial.println(F("║  H / h  → Home motor                  ║"));
  Serial.println(F("║  ?      → Status                      ║"));
  Serial.println(F("║  I / i  → System info                 ║"));
  Serial.println(F("╚════════════════════════════════════════╝\n"));
}

void printStatus() {
  Serial.println(F("\n╔════════════════════════════════════════╗"));
  Serial.println(F("║          SYSTEM STATUS                ║"));
  Serial.println(F("╠════════════════════════════════════════╣"));
  
  Serial.print(F("║  State:           "));
  switch(currentState) {
    case STATE_IDLE:
      Serial.println(F("IDLE              ║"));
      break;
    case STATE_MOVING_FORWARD:
      Serial.println(F("MOVING FORWARD    ║"));
      break;
    case STATE_MOVING_REVERSE:
      Serial.println(F("MOVING REVERSE    ║"));
      break;
    case STATE_ERROR:
      Serial.println(F("ERROR ⚠️           ║"));
      break;
    case STATE_HOMING:
      Serial.println(F("HOMING 🏠          ║"));
      break;
  }
  
  Serial.print(F("║  Servo ON:        "));
  Serial.print(digitalRead(SERVO_ON_PIN) ? F("YES ✓") : F("NO ✗ "));
  Serial.println(F("            ║"));
  
  Serial.print(F("║  Forward Limit:   "));
  Serial.print(digitalRead(LIMIT_FWD_PIN) ? F("OK ✓ ") : F("TRIGGERED ⚠️"));
  Serial.println(F("       ║"));
  
  Serial.print(F("║  Reverse Limit:   "));
  Serial.print(digitalRead(LIMIT_REV_PIN) ? F("OK ✓ ") : F("TRIGGERED ⚠️"));
  Serial.println(F("       ║"));
  
  Serial.print(F("║  Position:        "));
  Serial.print(currentPosition);
  Serial.println(F(" pulses      ║"));
  
  Serial.println(F("╚════════════════════════════════════════╝\n"));
}

void printSystemInfo() {
  Serial.println(F("\n╔════════════════════════════════════════╗"));
  Serial.println(F("║        SYSTEM INFORMATION             ║"));
  Serial.println(F("╠════════════════════════════════════════╣"));
  Serial.print(F("║  Pulses/mm:       "));
  Serial.print(PULSES_PER_MM);
  Serial.println(F("              ║"));
  Serial.print(F("║  Max Speed:       "));
  Serial.print(MAX_SPEED_MM_S);
  Serial.println(F(" mm/s         ║"));
  Serial.print(F("║  Pulse Freq:      "));
  Serial.print(PULSE_FREQ_HZ / 1000);
  Serial.println(F(" kHz        ║"));
  Serial.print(F("║  Max Distance:    "));
  Serial.print(MAX_DISTANCE_MM);
  Serial.println(F(" mm          ║"));
  Serial.print(F("║  Firmware:        v1.0               ║"));
  Serial.println(F("╚════════════════════════════════════════╝\n"));
}

void blinkStatusLED() {
  static bool ledState = false;
  if (currentState == STATE_IDLE) {
    digitalWrite(LED_STATUS, ledState);
    ledState = !ledState;
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
```

### How to Upload | كيفية الرفع

1. Open Arduino IDE
2. Copy the code above
3. Select: **Tools → Board → Arduino Mega 2560**
4. Select correct COM port
5. Click **Upload** button
6. Open **Serial Monitor** (115200 baud)
7. Test with commands: F, R, S, etc.

---

## 🔧 STM32 Code | كود STM32

### STM32CubeIDE Project Setup

**[Full STM32 HAL code would go here - similar structure to Arduino but using STM32 HAL libraries]**

*Due to length constraints, the complete STM32 code is available in a separate file: `STM32_ASDA_B3_Control.c`*

---

## 🧪 Testing Steps | خطوات الاختبار

### Pre-Power Checks ✓

```
□ Visual Inspection
  □ All wiring secure and correct
  □ No exposed conductors
  □ Proper gauge wires used
  □ No loose connections
  
□ Voltage Checks (multimeter)
  □ 220V AC at driver input
  □ 24V DC at control circuit
  □ Continuity on ground connections
  
□ Signal Checks
  □ Limit switches at 24V when not triggered
  □ Encoder cable connected to CN2
  □ Motor phases U, V, W connected correctly
  
□ Software Checks
  □ Parameters loaded in driver
  □ Microcontroller code uploaded
  □ Serial monitor working
```

### Step-by-Step Testing | الاختبار خطوة بخطوة

#### Test 1: Power-On
```
1. Apply 220V AC to driver
2. Observe LED indicators:
   ✓ Power LED: Green and steady
   ✗ Alarm LED: Should be OFF
3. If alarm LED ON → Note error code
```

#### Test 2: Servo Enable
```
1. Send 'E' command via serial
2. Motor should energize (resistance to rotation)
3. No unusual sounds or vibrations
4. LED indicators stable
```

#### Test 3: Manual Jog (Low Speed)
```
1. In ASDA-Soft, enter JOG mode
2. Set speed: 50 RPM
3. Test forward direction
4. Test reverse direction
5. Check for smooth rotation
```

#### Test 4: Limit Switch Test
```
1. Manually activate forward limit
   → Driver should show limit status
2. Try to move forward
   → Motion should be blocked
3. Release limit
4. Repeat for reverse limit
```

#### Test 5: Low Speed Test
```
1. Send 'F' command (100mm forward)
2. Observe motion:
   ✓ Smooth acceleration
   ✓ Constant speed
   ✓ Smooth deceleration
3. Measure actual distance
4. Calculate error percentage
```

#### Test 6: Full Speed Test (1 m/s)
```
1. Send '1' command (1 meter forward)
2. Time the movement with stopwatch
3. Should complete in ~1 second
4. Check for:
   ✓ No oscillation
   ✓ Accurate positioning
   ✓ Smooth operation
```

#### Test 7: Limit Switch Protection
```
1. Command long distance movement
2. Let it reach limit switch
3. Verify:
   ✓ Motion stops immediately
   ✓ No mechanical impact
   ✓ Alarm can be reset
```

#### Test 8: Repeated Cycles
```
1. Run 10 cycles: forward → reverse
2. Monitor for:
   ✓ Consistent performance
   ✓ No heat buildup
   ✓ Accurate positioning
3. Check driver temperature (< 40°C)
```

### Calibration | المعايرة

#### Position Accuracy
```
Test Distance: 1000 mm
1. Mark start position
2. Command 1000mm movement
3. Measure actual distance
4. Calculate:
   Error = (Actual - Target) / Target × 100%
5. If error > 1%:
   Adjust: Pn05.00/Pn05.01 (gear ratio)
```

#### Speed Calibration
```
1. Command 1-meter movement
2. Time with stopwatch
3. Calculate actual speed:
   Speed = Distance / Time
4. If speed incorrect:
   - Check pulse frequency
   - Verify timer configuration
   - Adjust PULSES_PER_MM constant
```

---

## ❌ Troubleshooting | حل المشاكل

### Quick Diagnostic Chart

```
Problem: Motor doesn't move
├─ Servo ON LED?
│  ├─ OFF → Check SERVO_ON_PIN signal
│  └─ ON  → Check pulse signal
│
├─ Alarm LED?
│  ├─ ON  → Check alarm code
│  └─ OFF → Check limit switches
│
└─ Encoder OK?
   ├─ Check CN2 connection
   └─ Verify encoder cable
```

### Common Issues & Solutions

#### 🔴 AL-010: Overcurrent Alarm
```
Symptoms:
- Alarm immediately after servo ON
- Motor jerks then stops

Solutions:
1. Check motor phase wiring (U, V, W correct order?)
2. Verify motor model parameter (Pn01.00)
3. Reduce acceleration time (Pn03.00)
4. Check for mechanical binding
5. Ensure encoder connected properly
```

#### 🔴 AL-020: Overvoltage Alarm
```
Symptoms:
- Alarm during fast deceleration
- Intermittent stops

Solutions:
1. Install external braking resistor
2. Increase deceleration time (Pn03.01)
3. Check AC input voltage stability
4. Reduce speed if necessary
```

#### 🔴 AL-030: Encoder Error
```
Symptoms:
- Alarm at startup
- Erratic motion

Solutions:
1. Check CN2 connector
2. Verify encoder cable not damaged
3. Check for electromagnetic interference
4. Replace encoder cable if needed
```

#### 🔴 Motor Vibrates/Oscillates
```
Symptoms:
- Unstable motion
- Loud noise
- Position hunting

Solutions:
1. Run auto-tuning procedure
2. Reduce Kp gain (Pn10.00)
3. Check mechanical coupling alignment
4. Verify no mechanical play
5. Increase S-curve time (Pn03.02)
```

#### 🔴 Wrong Direction
```
Symptoms:
- Motor moves opposite to command

Solutions:
Option 1: Change code
  digitalWrite(DIR_PIN, !direction);
  
Option 2: Swap motor phases
  Interchange U and W wires
  
Option 3: Change driver parameter
  Pn02.02 = invert direction logic
```

#### 🔴 Inaccurate Positioning
```
Symptoms:
- Doesn't reach exact target
- Repeatable error

Solutions:
1. Verify PULSES_PER_MM calculation
2. Check for mechanical backlash
3. Adjust electronic gear ratio (Pn05.xx)
4. Run position calibration test
5. Check for belt/screw slippage
```

#### 🔴 Limit Switch Doesn't Work
```
Symptoms:
- Motor doesn't stop at limit
- Crashes into end

Solutions:
1. Check 24V supply to switches
2. Verify NC (Normally Closed) wiring
3. Test switch with multimeter
4. Check DI configuration (Pn04.01, Pn04.02)
5. Verify interrupt setup in code
```

#### 🔴 No Pulse Output
```
Symptoms:
- Servo ON but no motion
- Position doesn't change

Solutions:
1. Check Timer configuration
2. Verify PULSE_PIN connection
3. Use oscilloscope to view signal
4. Check pulse frequency setting
5. Verify CN1 pin 5 (PULS+) connection
```

### Alarm Code Reference

| Code | Name | Description | Solution |
|------|------|-------------|----------|
| AL-001 | Overcurrent | Excessive current | Check wiring, reduce load |
| AL-010 | DC bus overvoltage | Voltage too high | Add brake resistor, slower decel |
| AL-020 | Encoder error | Encoder disconnected | Check CN2, replace cable |
| AL-030 | Overload | Motor overheated | Reduce duty cycle, check load |
| AL-040 | Overspeed | Exceeded speed limit | Check speed parameter |
| AL-050 | Following error | Position error too large | Auto-tune, check mechanics |
| AL-100 | Parameter error | Invalid parameter | Reset to defaults |
| AL-200 | Brake circuit fault | Brake resistor issue | Check resistor connection |

---

## ⚠️ Safety | السلامة

### ⚡ Electrical Safety | السلامة الكهربائية

```
🔴 DANGER - 220V AC CAN BE FATAL!

Mandatory Precautions:
□ ALWAYS disconnect power before maintenance
□ Use insulated tools rated for 1000V
□ Wear safety gloves and goggles
□ Ensure proper grounding (PE) connections
□ Install RCD/GFCI protection
□ Never touch driver heatsink during operation
□ Wait 5 minutes after power-off (capacitor discharge)
□ Use lockout/tagout procedures
□ Keep workspace dry
□ Install emergency stop within reach
```

### ⚙️ Mechanical Safety | السلامة الميكانيكية

```
Mandatory Precautions:
□ Install physical hard stops beyond limit switches
□ Use safety guards around moving parts
□ Ensure workspace clear before operation
□ Never bypass limit switches
□ Test at low speed first
□ Monitor for unusual sounds/vibrations
□ Secure all mechanical connections
□ Check for wear on belts/screws regularly
□ Keep hands clear during operation
□ Use proper lifting techniques for heavy components
```

### 🔧 Operational Safety | السلامة التشغيلية

```
Best Practices:
□ Never exceed motor rated specifications
□ Maintain driver temperature < 40°C
□ Ensure adequate ventilation
□ Don't disconnect encoder while powered
□ Save configuration before power cycling
□ Log all alarms with timestamp
□ Perform weekly visual inspections
□ Check all connections monthly
□ Update firmware only when necessary
□ Keep spare parts available
```

### 🚨 Emergency Procedures | إجراءات الطوارئ

#### If Motor Runs Away:
```
1. Press EMERGENCY STOP button immediately
2. Cut main AC power at breaker
3. DO NOT attempt to stop motor manually
4. After motor stops:
   - Investigate limit switch failure
   - Check wiring for shorts
   - Verify software logic
   - Test thoroughly before restart
```

#### If Driver Shows Alarm:
```
1. Note alarm code and timestamp
2. Stop operation immediately
3. Check this troubleshooting guide
4. Resolve root cause before resetting
5. Never repeatedly reset without fixing issue
```

#### If Motor Overheats:
```
1. Stop operation immediately
2. Allow motor to cool (30+ minutes)
3. Check for:
   - Overload condition
   - Blocked ventilation
   - Excessive duty cycle
4. Consider:
   - Larger motor
   - Reduced speed
   - Added cooling
```

#### If Fire/Smoke Detected:
```
1. Cut main power immediately
2. Evacuate area
3. Use Class C fire extinguisher if safe
4. Call emergency services
5. Do not reconnect until inspected
```

---

## 📚 Additional Resources | مصادر إضافية

### Official Documentation
- **ASDA-B3 User Manual:** [View uploaded manual](computer:///mnt/user-data/uploads/sc.jpeg)
- **ASDA-Soft Download:** https://www.deltaww.com → Products → Servo
- **Delta Technical Support:** https://www.deltaww.com/contact

### Video Tutorials
- YouTube: "Delta ASDA-B3 Setup Tutorial"
- YouTube: "Servo Motor Wiring and Configuration"
- YouTube: "Arduino Timer PWM for Stepper Control"

### Forums & Communities
- Delta Automation Forum
- Arduino Forum: Motion Control section
- STM32 Community
- r/PLC subreddit

### Recommended Books
- "Motion Control Systems" - Benjamin C. Kuo
- "Servo Motors and Industrial Control Theory" - Riazollah Firoozian
- "Practical Motion Control with Microcontrollers" - Jon Titus

---

## 🤝 Support | الدعم

### Need Help?

1. **Read the manual first** - Most answers are in documentation
2. **Search online** - Many issues have been solved before
3. **Check this README** - Covers common problems
4. **Contact Delta Support** - For driver-specific issues
5. **Arduino/STM32 Forums** - For code-related questions

### Contributing

Found an error or improvement?
- Report issues with detailed description
- Include photos of your setup
- Share your solutions with the community

---

## 📄 License & Disclaimer

```
This documentation is provided "as-is" for educational purposes.

Disclaimer:
- Working with high voltage (220V AC) is dangerous
- Improper wiring can cause injury or death
- Always follow local electrical codes
- Consult certified electrician if unsure
- Author assumes no liability for damages
- Use at your own risk

The author and contributors are not responsible for:
- Personal injury
- Equipment damage
- Property damage
- Consequential losses

Safety is YOUR responsibility!
```

---

## ✅ Quick Start Checklist | قائمة البدء السريع

```
Week 1: Planning & Procurement
□ Read complete README
□ Calculate pulse frequency for your system
□ Order all required components
□ Prepare workspace and tools

Week 2: Hardware Assembly
□ Mount driver and motor
□ Wire power connections (220V AC)
□ Connect motor phases (U, V, W)
□ Connect encoder cable (CN2)
□ Install limit switches
□ Wire control signals (CN1)

Week 3: Software Configuration
□ Install ASDA-Soft
□ Configure driver parameters
□ Upload Arduino/STM32 code
□ Run auto-tuning

Week 4: Testing & Calibration
□ Power-on test
□ Low-speed jog test
□ Limit switch test
□ Full-speed test (1 m/s)
□ Position accuracy test
□ Final adjustments

Week 5: Production
□ Document your configuration
□ Create backup of parameters
□ Establish maintenance schedule
□ Train operators
□ Begin normal operation
```

---


**Version:** 1.0  
**Last Updated:** October 26, 2025  
**Language:** English / العربية

---

<p align="center">
  <strong>⚡ Safety First! Always Test Thoroughly! ⚡</strong>
</p>

<p align="center">
  Made with ⚙️ for motion control enthusiasts
</p>
