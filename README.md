# Delta ASDA-B3 Servo Motor Control Project

<div align="center">

![Delta ASDA-B3](https://img.shields.io/badge/Delta-ASDA--B3-blue?style=for-the-badge)
![Speed](https://img.shields.io/badge/Speed-1m%2Fs-green?style=for-the-badge)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-brightgreen?style=for-the-badge)
![STM32](https://img.shields.io/badge/STM32-Compatible-blue?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)

**Complete implementation for controlling Delta ASDA-B3 servo motor with microcontroller**

[English](#english) | [العربية](#arabic)

</div>

---

## 🎯 Project Overview

This repository provides a complete, production-ready implementation for controlling Delta ASDA-B3 series servo motors using Arduino or STM32 microcontrollers. Perfect for CNC machines, robotics, automation projects, and precision motion control applications.

### ✨ Key Features

- 🎮 **Pulse/Direction Control** - High-speed pulse generation up to 500 kHz
- 🛡️ **Hardware Safety** - Limit switch protection and emergency stop
- ⚡ **1 m/s Speed** - Precise speed control with configurable acceleration
- 📊 **Real-time Monitoring** - Serial interface for status and debugging
- 🔧 **Auto-tuning Support** - Easy setup with ASDA-Soft
- 📝 **Well Documented** - Complete guides in English and Arabic
- 🧪 **Tested & Proven** - Production-ready code with error handling

### 🎬 Demo

```
→ Moving forward: 1000 mm (250000 pulses)
✓ Motion complete in 1.02 seconds
✓ Position accuracy: 0.5mm
← Returning to home position...
```

---

## 📦 What's Included

```
Delta-ASDA-B3-Control/
├── README.md                    # This file
├── LICENSE                      # MIT License
├── .gitignore                   # Git ignore rules
│
├── arduino/                     # Arduino implementations
│   ├── Delta_ASDA_B3_Mega/      # Arduino Mega version
│   ├── Delta_ASDA_B3_Uno/       # Arduino Uno version (limited)
│   └── libraries/               # Required libraries
│
├── stm32/                       # STM32 implementations
│   ├── STM32F103_HAL/           # STM32 HAL version
│   └── STM32F103_LL/            # STM32 Low-Layer version
│
├── docs/                        # Documentation
│   ├── COMPLETE_GUIDE.md        # Full step-by-step guide
│   ├── WIRING_DIAGRAM.md        # Detailed wiring instructions
│   ├── PARAMETERS.md            # Driver parameter reference
│   ├── TROUBLESHOOTING.md       # Common issues and solutions
│   └── API_REFERENCE.md         # Code API documentation
│
├── hardware/                    # Hardware files
│   ├── schematics/              # Circuit diagrams
│   ├── pcb/                     # PCB designs (optional)
│   └── BOM.md                   # Bill of materials
│
├── examples/                    # Example projects
│   ├── basic_motion/            # Simple back-and-forth motion
│   ├── cnc_router/              # CNC router application
│   ├── pick_and_place/          # Pick & place robot
│   └── position_tracking/       # Position feedback system
│
└── tools/                       # Utility tools
    ├── parameter_generator/     # Generate driver parameters
    ├── speed_calculator/        # Calculate pulse frequencies
    └── serial_monitor/          # Enhanced serial interface
```

---

## 🚀 Quick Start

### Prerequisites

- **Hardware:**
  - Delta ASDA-B3 Servo Drive (400W - 1.5kW)
  - Compatible Servo Motor (ECM-B3 series)
  - Arduino Mega 2560 or STM32F103 (Blue Pill)
  - 2× Limit Switches (NC configuration)
  - 24V DC Power Supply (2A minimum)
  - 220V AC Power Supply

- **Software:**
  - [Arduino IDE](https://www.arduino.cc/en/software) (1.8.x or 2.x)
  - [ASDA-Soft](https://www.deltaww.com) (for driver configuration)
  - USB-to-RS485 converter

### Installation

#### 1. Clone Repository

```bash
git clone https://github.com/yourusername/Delta-ASDA-B3-Control.git
cd Delta-ASDA-B3-Control
```

#### 2. Hardware Setup

Follow the detailed wiring guide in [`docs/WIRING_DIAGRAM.md`](docs/WIRING_DIAGRAM.md)

**Quick Connection Reference:**
```
Arduino Pin 9  → CN1 Pin 5 (PULS+)
Arduino Pin 8  → CN1 Pin 7 (SIGN+/DIR)
Arduino Pin 7  → CN1 Pin 1 (SERVO-ON)
Arduino GND    → CN1 Common pins
```

#### 3. Driver Configuration

1. Open ASDA-Soft
2. Import parameters from `hardware/asda_b3_default_config.csv`
3. Or manually configure using [`docs/PARAMETERS.md`](docs/PARAMETERS.md)
4. Run auto-tuning procedure

#### 4. Upload Arduino Code

```bash
# Open Arduino IDE
File → Open → arduino/Delta_ASDA_B3_Mega/Delta_ASDA_B3_Mega.ino

# Select board
Tools → Board → Arduino Mega 2560

# Select port
Tools → Port → [Your COM Port]

# Upload
Sketch → Upload
```

#### 5. Test

```bash
# Open Serial Monitor (115200 baud)
Tools → Serial Monitor

# Test commands:
F  → Move forward 100mm
R  → Move reverse 100mm
1  → Move forward 1 meter
?  → Show status
```

---

## 📖 Documentation

### For Beginners

1. **[Complete Guide](docs/COMPLETE_GUIDE.md)** - Start here! Step-by-step tutorial
2. **[Bill of Materials](hardware/BOM.md)** - Everything you need to buy
3. **[Wiring Diagram](docs/WIRING_DIAGRAM.md)** - How to connect everything
4. **[Parameter Setup](docs/PARAMETERS.md)** - Configure the servo driver

### For Advanced Users

1. **[API Reference](docs/API_REFERENCE.md)** - Function documentation
2. **[Speed Calculation](docs/SPEED_CALCULATION.md)** - Calculate pulse frequencies
3. **[Troubleshooting](docs/TROUBLESHOOTING.md)** - Solve common issues
4. **[Examples](examples/)** - Real-world applications

### Video Tutorials (Coming Soon)

- Hardware assembly walkthrough
- Software configuration guide
- First motion test
- Auto-tuning procedure

---

## 🎛️ Serial Commands

| Command | Action | Description |
|---------|--------|-------------|
| `F` / `f` | Forward 100mm | Move forward short distance |
| `R` / `r` | Reverse 100mm | Move reverse short distance |
| `1` | Forward 1 meter | Move forward 1000mm @ 1m/s |
| `2` | Reverse 1 meter | Move reverse 1000mm @ 1m/s |
| `S` / `s` | Stop | Emergency stop |
| `E` / `e` | Enable | Enable servo motor |
| `D` / `d` | Disable | Disable servo motor |
| `H` / `h` | Home | Run homing sequence |
| `A` / `a` | Reset | Reset alarms |
| `?` | Status | Display system status |
| `I` / `i` | Info | Display system information |

---

## ⚙️ Configuration

### Speed Adjustment

Edit `arduino/Delta_ASDA_B3_Mega/config.h`:

```cpp
// Motion parameters
#define PULSES_PER_MM   250      // Adjust for your mechanism
#define MAX_SPEED_MM_S  1000     // 1 meter/second
#define ACCEL_TIME_MS   200      // Acceleration time
#define DECEL_TIME_MS   200      // Deceleration time
```

### Calculate Your Pulse Frequency

```
Pulse Frequency (Hz) = Speed (mm/s) × Pulses per mm

Example (Ball Screw 10mm lead):
Pulses/mm = 2500 PPR / 10mm = 250 pulses/mm
Frequency = 1000 mm/s × 250 = 250,000 Hz (250 kHz)
```

Use the [Speed Calculator Tool](tools/speed_calculator/) for automatic calculation.

---

## 🛠️ Supported Hardware

### Servo Drivers
- ✅ ASDA-B3-0421-B (400W)
- ✅ ASDA-B3-0721-B (750W)
- ✅ ASDA-B3-1021-B (1kW)
- ✅ ASDA-B3-1521-B (1.5kW)
- ⚠️ ASDA-A3 series (compatible with modifications)

### Microcontrollers
- ✅ Arduino Mega 2560 (recommended)
- ⚠️ Arduino Uno (limited to ~125 kHz)
- ✅ STM32F103 Blue Pill (high performance)
- ✅ STM32F4 series (overkill but excellent)
- ⚠️ ESP32 (possible but complex timer setup)

### Motors
- ✅ ECM-B3 Series (all power ratings)
- ✅ ECM-A3 Series (with parameter adjustment)

---

## 📊 Performance Specifications

| Parameter | Value | Notes |
|-----------|-------|-------|
| Max Pulse Frequency | 250 kHz | Arduino Mega |
| Position Accuracy | ±0.5mm | With auto-tuning |
| Speed Range | 0.1 - 1.5 m/s | Configurable |
| Response Time | <10ms | From command to motion |
| Acceleration | 5 m/s² | Default, adjustable |
| Deceleration | 5 m/s² | Default, adjustable |

---

## 🧪 Testing & Validation

### Run Tests

```bash
cd tests/
python run_tests.py
```

### Manual Testing Checklist

- [ ] Power-on test (driver LEDs)
- [ ] Servo enable test (motor energizes)
- [ ] Low-speed jog (100 RPM)
- [ ] Limit switch test (forward & reverse)
- [ ] Speed accuracy test (1 meter in ~1 second)
- [ ] Position accuracy test (±1mm tolerance)
- [ ] Repeated cycles (10× back and forth)
- [ ] Emergency stop test

---

## 🤝 Contributing

Contributions are welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

### Ways to Contribute

- 🐛 Report bugs via [Issues](https://github.com/yourusername/Delta-ASDA-B3-Control/issues)
- 💡 Suggest features or improvements
- 📝 Improve documentation
- 🔧 Submit pull requests
- 🌍 Translate to other languages
- 📹 Create video tutorials

---

## 🐛 Troubleshooting

### Quick Diagnostics

| Symptom | Likely Cause | Solution |
|---------|--------------|----------|
| No motion | Servo not enabled | Send 'E' command |
| Wrong direction | Phase wiring | Swap U and W wires |
| Vibration | Tuning needed | Run auto-tune |
| Stops randomly | Limit switch | Check wiring |
| Alarm AL-010 | Overcurrent | Check motor connections |

See [Full Troubleshooting Guide](docs/TROUBLESHOOTING.md) for detailed solutions.

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Third-Party Acknowledgments

- Delta Electronics for ASDA-B3 servo system
- Arduino community for platform support
- STM32 community for HAL libraries

---

## ⚠️ Safety Warning

```
⚡ WARNING: This project involves 220V AC power which can be LETHAL!

- Always disconnect power before maintenance
- Use proper safety equipment
- Follow local electrical codes
- Consult certified electrician if unsure
- Install emergency stop button
- Test thoroughly before production use

The authors assume NO LIABILITY for any damages, injuries, or losses.
USE AT YOUR OWN RISK!
```

---

## 📞 Support

### Get Help

1. **Documentation:** Check [`docs/`](docs/) folder first
2. **Issues:** Search [existing issues](https://github.com/yourusername/Delta-ASDA-B3-Control/issues)
3. **Discussions:** Join [GitHub Discussions](https://github.com/yourusername/Delta-ASDA-B3-Control/discussions)
4. **Email:** support@yourproject.com

### Commercial Support

Need custom development or integration?
- Email: commercial@yourproject.com
- We offer paid consulting and custom development

---

## 🌟 Star History

[![Star History Chart](https://api.star-history.com/svg?repos=yourusername/Delta-ASDA-B3-Control&type=Date)](https://star-history.com/#yourusername/Delta-ASDA-B3-Control&Date)

---

## 📈 Roadmap

### Version 1.1 (Next Release)
- [ ] ESP32 support with full documentation
- [ ] Modbus RTU communication example
- [ ] Web-based parameter configuration
- [ ] Position tracking with encoder feedback
- [ ] Graphical tuning assistant

### Version 2.0 (Future)
- [ ] Multi-axis coordinated motion
- [ ] G-code interpreter
- [ ] HMI touchscreen interface
- [ ] Industrial IoT integration
- [ ] Cloud monitoring dashboard

---

## 🙏 Acknowledgments

Special thanks to:
- Delta Electronics for technical documentation
- Arduino and STM32 communities
- Early testers and contributors
- Everyone who provided feedback

---

<div align="center">

## 📬 Stay Updated

**Star** ⭐ this repo to receive updates!

Made with ⚙️ and ❤️ by motion control enthusiasts

[Report Bug](https://github.com/yourusername/Delta-ASDA-B3-Control/issues) · [Request Feature](https://github.com/yourusername/Delta-ASDA-B3-Control/issues) · [Documentation](docs/)

</div>

---

<div align="center">

# النسخة العربية | Arabic Version

[الدليل الكامل بالعربية](docs/COMPLETE_GUIDE_AR.md)

</div>

---

## 📊 Project Stats

![GitHub stars](https://img.shields.io/github/stars/yourusername/Delta-ASDA-B3-Control?style=social)
![GitHub forks](https://img.shields.io/github/forks/yourusername/Delta-ASDA-B3-Control?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/yourusername/Delta-ASDA-B3-Control?style=social)
![GitHub issues](https://img.shields.io/github/issues/yourusername/Delta-ASDA-B3-Control)
![GitHub pull requests](https://img.shields.io/github/issues-pr/yourusername/Delta-ASDA-B3-Control)
![GitHub last commit](https://img.shields.io/github/last-commit/yourusername/Delta-ASDA-B3-Control)
![GitHub code size](https://img.shields.io/github/languages/code-size/yourusername/Delta-ASDA-B3-Control)

---

**Happy Building! 🚀**
