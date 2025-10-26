# Bill of Materials (BOM)
# Delta ASDA-B3 Servo Control Project

## 📦 Complete Shopping List

This document lists everything you need to build this project, including part numbers, specifications, and estimated costs.

---

## ✅ What You Already Have

Before shopping, check if you have:
- ✅ Servo Motor (ECM-B3 series)
- ✅ Limit Switches (2 pcs)

---

## 🛒 Required Components

### 1. Core Components

| # | Part | Description | Specifications | Qty | Unit Price | Total | Supplier |
|---|------|-------------|----------------|-----|------------|-------|----------|
| 1 | **Servo Drive** | Delta ASDA-B3 | Model based on motor power | 1 | $250-400 | $250-400 | Delta authorized dealers |
| 2 | **Microcontroller** | Arduino Mega 2560 | ATmega2560, 16MHz, 256KB Flash | 1 | $15 | $15 | Arduino.cc, Amazon, AliExpress |
| 2a | *Alternative* | STM32F103C8T6 Blue Pill | 72MHz, 64/128KB Flash | 1 | $3-5 | $3-5 | AliExpress, LCSC |
| 3 | **Power Supply 24V** | Switching PSU | 24V DC, 2A min (50W), DIN rail | 1 | $20 | $20 | Mean Well, Schneider |
| 4 | **Power Supply 220V** | Based on motor | Single/3-phase per motor spec | 1 | Existing | $0 | - |

**Core Components Subtotal:** ~$285-435

### 2. Connectors & Cables

| # | Part | Description | Specifications | Qty | Unit Price | Total | Supplier |
|---|------|-------------|----------------|-----|------------|-------|----------|
| 5 | **Control Cable** | CN1 connector cable | 20-pin, 0.5-1m length | 1 | $10 | $10 | Delta, eBay |
| 6 | **Motor Power Cable** | 3-phase power cable | 3-core, AWG14-16, shielded | 2m | $3/m | $6 | Generic |
| 7 | **Encoder Cable** | CN2 connector | Usually included with motor | 1 | $0-10 | $0-10 | Check motor package |
| 8 | **USB Cable** | For Arduino | USB-A to USB-B, 1m | 1 | $3 | $3 | Generic |
| 9 | **Jumper Wires** | DuPont connectors | Male-Male & Male-Female, 40pcs | 1 set | $3 | $3 | Generic |
| 10 | **USB-to-RS485** | For ASDA-Soft config | MAX485 chip, USB powered | 1 | $5 | $5 | Generic |

**Connectors & Cables Subtotal:** ~$37

### 3. Protection & Safety

| # | Part | Description | Specifications | Qty | Unit Price | Total | Supplier |
|---|------|-------------|----------------|-----|------------|-------|----------|
| 11 | **Circuit Breaker** | AC main protection | 10A, 240V AC, 1-pole, DIN rail | 1 | $5 | $5 | Schneider, ABB |
| 12 | **Emergency Stop Button** | Red mushroom | NC contact, 22mm diameter | 1 | $5 | $5 | Generic |
| 13 | **Fuse** | 24V DC protection | 5A fast-blow, 5×20mm | 2 | $1 | $2 | Generic |
| 14 | **Relay Module** | Isolation (optional) | 24V coil, 2-channel | 1 | $3 | $3 | Generic |
| 15 | **Terminal Blocks** | Wire connections | 10-position, 5mm pitch, DIN rail | 2 | $3 | $6 | Phoenix, Wago |

**Protection & Safety Subtotal:** ~$21

### 4. Enclosure & Mounting

| # | Part | Description | Specifications | Qty | Unit Price | Total | Supplier |
|---|------|-------------|----------------|-----|------------|-------|----------|
| 16 | **DIN Rail** | Component mounting | 35mm × 7.5mm, 30cm length | 1 | $5 | $5 | Generic |
| 17 | **Electrical Box** | Weatherproof enclosure | IP65, 200×150×100mm ABS/metal | 1 | $15 | $15 | Generic |
| 18 | **Cable Glands** | Cable entry | PG11/PG13, IP68, nylon | 4 | $1 | $4 | Generic |
| 19 | **Cable Ties** | Cable management | 150mm, black nylon | 50 | $0.05 | $2.5 | Generic |
| 20 | **Heat Shrink Tubing** | Wire protection | Assorted sizes, 2:1 ratio | 1 set | $5 | $5 | Generic |

**Enclosure & Mounting Subtotal:** ~$31.5

### 5. Optional but Recommended

| # | Part | Description | Specifications | Qty | Unit Price | Total | Supplier |
|---|------|-------------|----------------|-----|------------|-------|----------|
| 21 | **Braking Resistor** | For fast decel | Match driver (100W-200W) | 1 | $30-50 | $40 | Delta, generic |
| 22 | **Proximity Sensors** | Better limit detection | NPN, M12, 10-30V DC | 2 | $10 | $20 | Generic |
| 23 | **Status LEDs** | Visual indicators | 5mm, red/green/yellow | 3 | $0.5 | $1.5 | Generic |
| 24 | **LED Holders** | Panel mount | 5mm LED panel mount | 3 | $0.5 | $1.5 | Generic |
| 25 | **Resistors** | For LEDs | 470Ω-1kΩ, 1/4W | 5 | $0.1 | $0.5 | Generic |
| 26 | **Push Buttons** | Start/Stop/Reset | 22mm, NO+NC contacts | 3 | $3 | $9 | Generic |

**Optional Components Subtotal:** ~$72.5

---

## 🔧 Tools Required

### Essential Tools

| Tool | Purpose | Est. Cost | Notes |
|------|---------|-----------|-------|
| **Multimeter** | Voltage/continuity testing | $10-50 | Digital, AC/DC voltage, continuity |
| **Screwdriver Set** | Assembly | $10-20 | Phillips & flat, insulated |
| **Wire Strippers** | Prepare cables | $5-15 | 14-24 AWG range |
| **Crimping Tool** | Terminals & connectors | $10-30 | For ferrules and terminals |
| **Hex Key Set** | Motor/driver mounting | $5-10 | Metric, 2-10mm |
| **Cable Cutters** | Cut wires | $5-10 | Side cutters |
| **Heat Gun** | Heat shrink | $10-20 | Or lighter (carefully) |

**Tools Subtotal:** ~$55-155 (if you don't have any)

### Optional but Useful

| Tool | Purpose | Est. Cost | Notes |
|------|---------|-----------|-------|
| **Oscilloscope** | Signal debugging | $50-500 | Essential for advanced troubleshooting |
| **Label Maker** | Wire identification | $15-30 | Brother P-touch or similar |
| **Torque Wrench** | Proper tightening | $20-50 | For motor mounting |

---

## 💰 Cost Summary

### Budget Breakdown

| Category | Cost (USD) | Notes |
|----------|------------|-------|
| **Core Components** | $285-435 | Main servo system |
| **Connectors & Cables** | $37 | Wiring materials |
| **Protection & Safety** | $21.5 | Critical for safety |
| **Enclosure & Mounting** | $31.5 | Professional installation |
| **Optional Components** | $72.5 | Enhanced functionality |
| **Tools** | $55-155 | One-time investment |
| **Shipping & Tax** | $50-100 | Estimate 10-15% |
|||
| **TOTAL (Minimum)** | **$430** | Basic setup, no options |
| **TOTAL (Recommended)** | **$560** | With optional parts |
| **TOTAL (First Project)** | **$715** | Including all tools |

### Cost Reduction Tips

- **Buy from AliExpress** for non-critical components (expect 2-4 week shipping)
- **Bundle orders** to save on shipping
- **Generic cables** work fine for most connections
- **3D print** enclosures if you have access to a printer
- **Borrow tools** from friends or makerspace
- **Skip optional** components initially, add later if needed

---

## 🛍️ Where to Buy

### Delta Components (Official)

**Servo Drive & Motor:**
- **Delta Official Store:** https://www.deltaww.com
- **Authorized Distributors:** Contact Delta for regional dealers
- **Industrial Suppliers:** Grainger, MSC Industrial, etc.

**Why Buy Official:**
- ✅ Warranty and support
- ✅ Guaranteed compatibility
- ✅ Latest firmware
- ❌ Higher cost

### Microcontrollers

**Arduino Mega 2560:**
- **Official:** Arduino.cc
- **Clones:** Amazon, AliExpress ($10-15)
- **Note:** Clones work fine for this project

**STM32 Blue Pill:**
- **AliExpress:** $2-5 (search "STM32F103C8T6")
- **LCSC:** Legitimate source
- **eBay:** Variable quality
- **⚠️ Warning:** Many have fake chips, test before critical use

### Electronic Components

**USA/Canada:**
- **Digi-Key** (www.digikey.com) - Fast shipping, everything available
- **Mouser** (www.mouser.com) - Great for industrial parts
- **Newark** (www.newark.com) - Good for automation components
- **Amazon** - Fast but mixed quality

**Europe:**
- **RS Components** (www.rs-online.com)
- **Farnell** (www.farnell.com)
- **Conrad** (www.conrad.com)

**Asia:**
- **LCSC** (www.lcsc.com) - Excellent for STM32 and basics
- **Taobao** (www.taobao.com) - Best prices (Chinese interface)

**Worldwide Budget:**
- **AliExpress** (www.aliexpress.com) - Cheapest, slow shipping
- **eBay** (www.ebay.com) - Mixed quality
- **Banggood** (www.banggood.com) - Decent quality/price

---

## 📦 Recommended Starter Kits

### Option 1: Budget Setup (~$430)

**Purchase List:**
```
□ ASDA-B3 drive (match your motor)
□ Arduino Mega 2560 (clone is fine)
□ 24V power supply (Mean Well RS-50-24)
□ Basic cable set
□ Terminal blocks
□ Emergency stop button
□ Basic tools (if needed)
```

**Good for:**
- Learning and prototyping
- Non-critical applications
- Budget-constrained projects

### Option 2: Recommended Setup (~$560)

**Adds to Budget Setup:**
```
□ Braking resistor
□ Proximity sensors for limits
□ Professional enclosure
□ USB-to-RS485 adapter
□ Extra cables and connectors
```

**Good for:**
- Semi-production use
- Better reliability
- Easier troubleshooting

### Option 3: Professional Setup (~$800+)

**Adds to Recommended:**
```
□ Genuine Arduino (not clone)
□ HMI touchscreen panel
□ Industrial enclosure (metal)
□ Schneider/ABB protection devices
□ Quality oscilloscope
□ Complete tool set
□ Spare parts kit
```

**Good for:**
- Production equipment
- Mission-critical applications
- Long-term reliability

---

## 📋 Pre-Purchase Checklist

Before ordering, verify:

### Motor Specifications
- [ ] Motor model number
- [ ] Power rating (W)
- [ ] Voltage (AC)
- [ ] Rated speed (RPM)
- [ ] Encoder type and resolution

### Driver Compatibility
- [ ] Driver matches motor power
- [ ] Voltage rating correct
- [ ] Control mode supported (position control)
- [ ] Has CN1 and CN2 connectors

### Mechanical System
- [ ] Ball screw lead OR belt pulley size
- [ ] Travel distance required
- [ ] Load weight and inertia
- [ ] Speed requirements

### Electrical Supply
- [ ] Available AC voltage (220V single/3-phase)
- [ ] Current capacity of circuit
- [ ] Grounding available
- [ ] Circuit breaker rating

---

## 🔄 Component Substitutions

### Can I Use...?

**Arduino Uno instead of Mega?**
- ⚠️ Limited - Maximum ~125 kHz pulse frequency
- ✅ OK for low-speed applications
- ❌ Not recommended for 1 m/s with high-resolution encoder

**ESP32 instead of Arduino?**
- ⚠️ Possible but complex timer setup
- ✅ Adds WiFi capability
- ❌ More difficult for beginners

**ASDA-A3 instead of ASDA-B3?**
- ✅ Compatible with parameter adjustments
- ⚠️ Check manual for differences
- ✅ Same wiring and control methods

**Generic servo drive?**
- ❌ Not recommended
- ⚠️ Would require complete code rewrite
- ⚠️ Parameter structure different

---

## 📦 Packaging & Delivery

### Shipping Considerations

**Fragile Items:**
- Servo motor (encoder is sensitive!)
- Arduino/STM32 boards
- Emergency stop button

**Heavy Items:**
- Servo drive (~2-5 kg)
- Metal enclosure
- Power supplies

**Shipping Time Estimates:**
- **Local suppliers:** 1-3 days
- **Amazon Prime:** 1-2 days  
- **Standard shipping:** 5-7 days
- **AliExpress:** 15-45 days (use AliExpress Standard Shipping)

### Customs & Import

**If ordering internationally:**
- Check import duties for your country
- Declare correct value
- Include harmonized tariff code if required
- Budget +10-30% for duties and taxes

---

## ✅ Receiving & Inspection

When parts arrive:

### Immediate Checks
- [ ] Package condition (any damage?)
- [ ] All items received (check packing list)
- [ ] Correct part numbers
- [ ] No obvious defects

### Testing
- [ ] Multimeter: Check power supplies (voltage output)
- [ ] Microcontroller: Upload blink test
- [ ] Driver: Power on, check LEDs
- [ ] Motor: Check encoder resistance (should be kΩ)
- [ ] Switches: Continuity test

### Documentation
- [ ] Save all receipts
- [ ] Keep datasheets
- [ ] Note serial numbers
- [ ] Save supplier contacts

---

## 📞 Supplier Contact Information

### Delta Electronics

**Global:**
- Website: https://www.deltaww.com
- Support: Check website for regional contacts

**USA:**
- Delta Products Corporation
- Phone: +1 (510) 271-0800
- Email: info@deltaww.com

**Europe:**
- Delta Energy Systems (Germany) GmbH  
- Phone: +49 (0) 6103 - 3979-0

**Asia-Pacific:**
- Check Delta website for country-specific contacts

### Arduino

- Website: https://www.arduino.cc
- Support: https://support.arduino.cc

---

## 💡 Tips for First-Time Buyers

1. **Don't buy everything at once** - Start with core components
2. **Buy from reputable sellers** - Check reviews and ratings
3. **Keep receipts** - For warranty and returns
4. **Order 10% extra** - Connectors, wires, heat shrink
5. **Plan for delays** - Start project with buffer time
6. **Join communities** - Ask for supplier recommendations
7. **Compare prices** - But consider shipping and reliability

---

## 📝 Maintenance Spare Parts

For long-term operation, keep spares:

| Part | Reason | Est. Cost |
|------|--------|-----------|
| Limit switches | Mechanical wear | $5 |
| Fuses | Electrical protection | $2 |
| Jumper wires | Connection failures | $3 |
| Emergency stop | Safety critical | $5 |
| USB cable | Debugging access | $3 |
| **Total Spare Kit** | | **~$20** |

---

## 🔄 Updates & Revisions

This BOM is current as of October 2025. Prices and availability may change.

**Revision History:**
- v1.0 (Oct 2025) - Initial release

**Submit Updates:**
Open an issue or PR if you find better sources or pricing.

---

**Questions about sourcing?** Open a discussion on GitHub!

**Found a great deal?** Share it with the community!
