# Contributing to Delta ASDA-B3 Control Project

First off, thank you for considering contributing to this project! 🎉

The following is a set of guidelines for contributing to the Delta ASDA-B3 Control Project. These are mostly guidelines, not rules. Use your best judgment, and feel free to propose changes to this document in a pull request.

## 📋 Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Development Setup](#development-setup)
- [Pull Request Process](#pull-request-process)
- [Coding Standards](#coding-standards)
- [Documentation](#documentation)
- [Testing](#testing)
- [Community](#community)

---

## 🤝 Code of Conduct

This project and everyone participating in it is governed by our Code of Conduct. By participating, you are expected to uphold this code. Please report unacceptable behavior to [project email].

### Our Standards

- Be respectful and inclusive
- Welcome newcomers and help them get started
- Focus on what is best for the community
- Show empathy towards other community members
- Accept constructive criticism gracefully

---

## 💡 How Can I Contribute?

### Reporting Bugs 🐛

Before creating bug reports, please check the [existing issues](https://github.com/yourusername/Delta-ASDA-B3-Control/issues) to avoid duplicates.

When creating a bug report, include:

- **Clear title and description**
- **Steps to reproduce** the problem
- **Expected behavior**
- **Actual behavior**
- **Hardware setup** (Arduino/STM32 model, driver version, motor specs)
- **Code version** (commit hash or release tag)
- **Serial output** or error messages
- **Photos** of your wiring (if relevant)

**Template:**

```markdown
**Bug Description:**
Brief description of the issue

**To Reproduce:**
1. Step one
2. Step two
3. ...

**Expected Behavior:**
What should happen

**Actual Behavior:**
What actually happens

**Hardware:**
- Microcontroller: Arduino Mega 2560
- Driver: ASDA-B3-0721-B
- Motor: ECM-C20604RS
- Other: ...

**Software:**
- Commit: abc123
- Arduino IDE: 2.0.3
- ASDA-Soft: 2.1.5

**Additional Context:**
Any other relevant information, logs, or screenshots
```

### Suggesting Enhancements 💡

Enhancement suggestions are tracked as GitHub issues. When creating an enhancement suggestion:

- **Use a clear and descriptive title**
- **Provide a detailed description** of the suggested enhancement
- **Explain why this enhancement would be useful**
- **List any alternative solutions** you've considered
- **Include mockups** or examples if applicable

### Contributing Code 👨‍💻

#### First-Time Contributors

Looking for a good first issue? Check issues labeled:
- `good first issue` - Simple tasks perfect for newcomers
- `help wanted` - Issues where we need community help
- `documentation` - Help improve our docs

#### Development Workflow

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes**
4. **Test thoroughly**
5. **Commit with clear messages**
6. **Push to your fork**
7. **Open a Pull Request**

---

## 🔧 Development Setup

### Prerequisites

- Git
- Arduino IDE or STM32CubeIDE
- Python 3.8+ (for tools)
- Hardware for testing (recommended)

### Setup Steps

```bash
# Clone your fork
git clone https://github.com/YOUR-USERNAME/Delta-ASDA-B3-Control.git
cd Delta-ASDA-B3-Control

# Add upstream remote
git remote add upstream https://github.com/original/Delta-ASDA-B3-Control.git

# Create a branch
git checkout -b feature/my-feature

# Install Python dependencies (for tools)
pip install -r requirements.txt
```

### Build and Test

#### Arduino
```bash
# Open in Arduino IDE
arduino/Delta_ASDA_B3_Mega/Delta_ASDA_B3_Mega.ino

# Verify compilation
Sketch → Verify/Compile
```

#### STM32
```bash
# Open in STM32CubeIDE
File → Import → Existing Projects into Workspace
Navigate to stm32/STM32F103_HAL/

# Build
Project → Build All
```

---

## 🔀 Pull Request Process

### Before Submitting

- [ ] Code follows project style guidelines
- [ ] All tests pass
- [ ] Documentation updated (if needed)
- [ ] Commit messages are clear
- [ ] Branch is up to date with main

### PR Checklist

```markdown
## Description
Clear description of what this PR does

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Performance improvement
- [ ] Code refactoring

## Testing
- [ ] Tested on hardware
- [ ] Tested on simulator (if applicable)
- [ ] Added/updated tests

## Hardware Tested On
- [ ] Arduino Mega 2560
- [ ] Arduino Uno
- [ ] STM32F103
- [ ] Other: ___________

## Driver Tested With
- [ ] ASDA-B3-0421-B (400W)
- [ ] ASDA-B3-0721-B (750W)
- [ ] ASDA-B3-1021-B (1kW)
- [ ] Other: ___________

## Checklist
- [ ] My code follows the style guidelines
- [ ] I have commented my code
- [ ] I have updated the documentation
- [ ] My changes generate no new warnings
- [ ] I have added tests that prove my fix/feature works
- [ ] New and existing tests pass locally

## Screenshots (if applicable)
Add screenshots of serial output, oscilloscope traces, etc.

## Related Issues
Fixes #(issue number)
```

### Review Process

1. At least one maintainer must review
2. All automated checks must pass
3. Address any review comments
4. Maintainer will merge when approved

---

## 📝 Coding Standards

### C/C++ Code Style

Follow these guidelines for Arduino and STM32 code:

#### Naming Conventions

```cpp
// Constants: UPPER_CASE
#define MAX_SPEED_MM_S  1000
const int PULSE_PIN = 9;

// Variables: camelCase
int pulseFrequency = 250000;
bool limitFwdTriggered = false;

// Functions: camelCase
void moveForward(int distance);
bool checkLimitSwitch();

// Enums: PascalCase with PREFIX_
enum MotionState {
    STATE_IDLE,
    STATE_MOVING_FORWARD,
    STATE_MOVING_REVERSE
};

// Classes: PascalCase
class ServoController {
    // ...
};
```

#### Code Formatting

```cpp
// Indentation: 4 spaces (no tabs)
void myFunction() {
    if (condition) {
        doSomething();
    }
}

// Braces: K&R style
if (x > 0) {
    // code
} else {
    // code
}

// Comments: Clear and concise
// Single-line comment

/*
 * Multi-line comment
 * for complex explanations
 */

/**
 * @brief Function documentation
 * @param distance Distance in millimeters
 * @return True if successful
 */
bool moveForward(int distance);
```

#### Best Practices

```cpp
// Use const for constants
const int LED_PIN = 13;

// Use constexpr for compile-time constants
constexpr int BUFFER_SIZE = 256;

// Avoid magic numbers
// Bad
delay(100);

// Good
const int DEBOUNCE_DELAY_MS = 100;
delay(DEBOUNCE_DELAY_MS);

// Use meaningful variable names
// Bad
int x, y, z;

// Good
int currentPosition, targetPosition, positionError;

// Check return values
if (setupTimer1PWM() != SUCCESS) {
    handleError();
}

// Initialize variables
int counter = 0;  // Good
int value;        // Bad - uninitialized
```

### Python Code Style

For utility tools:

```python
# Follow PEP 8
# Use 4 spaces for indentation
# Maximum line length: 79 characters

def calculate_pulse_frequency(speed_mm_s, pulses_per_mm):
    """
    Calculate required pulse frequency.
    
    Args:
        speed_mm_s: Linear speed in mm/s
        pulses_per_mm: Encoder pulses per millimeter
        
    Returns:
        Pulse frequency in Hz
    """
    return speed_mm_s * pulses_per_mm
```

---

## 📚 Documentation

### Code Documentation

- **Every function** should have a clear comment explaining its purpose
- **Complex algorithms** need detailed explanations
- **Hardware interactions** must be documented
- **Magic numbers** should be explained

### README Updates

When adding features:
- Update main README.md
- Add examples if applicable
- Update feature list
- Update roadmap if needed

### Wiki Contributions

Help expand our wiki:
- Hardware compatibility notes
- Application examples
- Troubleshooting tips
- Translation to other languages

---

## 🧪 Testing

### Hardware Testing

If you have access to hardware:

1. **Test on actual setup** before submitting
2. **Document test results** in PR
3. **Include oscilloscope traces** if relevant
4. **Test edge cases:**
   - Maximum speed
   - Limit switch triggers
   - Emergency stop
   - Parameter changes

### Simulation Testing

If you don't have hardware:

1. **Verify code compiles** on target platform
2. **Run static analysis** if available
3. **Check for common issues:**
   - Buffer overflows
   - Integer overflows
   - Memory leaks
   - Race conditions

### Test Checklist

```markdown
- [ ] Code compiles without warnings
- [ ] Servo enables properly
- [ ] Forward motion works
- [ ] Reverse motion works
- [ ] Speed is accurate (±5%)
- [ ] Position is accurate (±1mm)
- [ ] Limit switches stop motion
- [ ] Emergency stop works
- [ ] Alarm reset functions
- [ ] Serial commands work
- [ ] No memory leaks (for long runs)
- [ ] Stable operation for 1+ hour
```

---

## 👥 Community

### Communication Channels

- **GitHub Issues:** Bug reports and feature requests
- **GitHub Discussions:** General questions and ideas
- **Email:** For private inquiries
- **Discord/Slack:** (if available) Real-time chat

### Getting Help

1. **Read the docs** - Most questions are answered there
2. **Search issues** - Your question may be answered already
3. **Ask in discussions** - Community can help
4. **Be patient and respectful**

### Helping Others

- Answer questions in discussions
- Review pull requests
- Test new features
- Improve documentation
- Share your projects

---

## 🏆 Recognition

Contributors will be:
- Listed in README.md
- Mentioned in release notes
- Given credit in documentation

---

## 📜 License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

## ❓ Questions?

Don't hesitate to ask! Open a discussion or issue if anything is unclear.

---

**Thank you for contributing! 🙏**

Your efforts help make motion control accessible to everyone.
