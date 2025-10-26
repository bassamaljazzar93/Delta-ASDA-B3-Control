# Quick Start Guide
# دليل البدء السريع

## ⚡ 5-Minute Setup | الإعداد في 5 دقائق

### 1. Hardware | العتاد
```
Arduino Pin 9  → CN1 Pin 5 (PULS+)
Arduino Pin 8  → CN1 Pin 7 (DIR+)  
Arduino Pin 7  → CN1 Pin 1 (SERVO-ON)
Arduino GND    → CN1 Pin 2,6,8,10
```

### 2. Driver Config | إعدادات الدرايفر
```
Pn00.00 = 0x02  (Position mode)
Pn02.00 = 500000  (Max frequency)
Pn04.00 = 0x01  (SERVO-ON)
```

### 3. Upload Code | رفع الكود
```bash
1. Open Arduino IDE
2. File → Examples → Delta_ASDA_B3
3. Upload to Arduino Mega
4. Open Serial Monitor (115200)
```

### 4. Test | الاختبار
```
Send: E  (Enable servo)
Send: F  (Move forward 100mm)
Send: ?  (Check status)
```

## 📚 Full Documentation
See [`docs/COMPLETE_GUIDE.md`](docs/COMPLETE_GUIDE.md) for detailed instructions.

## ⚠️ Safety First!
- 220V AC is dangerous!
- Use emergency stop
- Test at low speed first
- Follow all safety guidelines

## 🆘 Need Help?
1. Check [`docs/TROUBLESHOOTING.md`](docs/TROUBLESHOOTING.md)
2. Open an [Issue](https://github.com/yourusername/Delta-ASDA-B3-Control/issues)
3. Read the [Complete Guide](docs/COMPLETE_GUIDE.md)
