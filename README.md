# 🌙 Smart Sleep Monitoring System with TSL2561 Sensor

> A beautiful, modern sleep monitoring system using TSL2561 Luminosity sensor with ESP32 that creates a WiFi access point and serves an elegant web dashboard for tracking light levels and sleep patterns. **Now with voice alerts using browser TTS!**

![ESP32](https://img.shields.io/badge/ESP32-Enabled-blue?style=flat-square)
![TSL2561](https://img.shields.io/badge/Sensor-TSL2561-green?style=flat-square)
![Voice](https://img.shields.io/badge/Voice-TTS_Enabled-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)

---

## 📋 Table of Contents
- [Features](#-features)
- [Demo & Screenshots](#-demo--screenshots)
- [Hardware Requirements](#️-hardware-requirements)
- [Bill of Materials](#-bill-of-materials)
- [Wiring Diagram](#-wiring-diagram)
- [Software Requirements](#-software-requirements)
- [Installation Guide](#-installation-guide)
- [Quick Start](#-quick-start)
- [Dashboard Features](#-dashboard-features)
- [Configuration](#️-configuration)
- [API Documentation](#-api-documentation)
- [Technical Specifications](#-technical-specifications)
- [Troubleshooting](#-troubleshooting)
- [Customization](#-customization)
- [License](#-license)

---

## ✨ Features

### Core Functionality
- 📊 **Real-time lux value monitoring** from TSL2561 sensor (updates every 2 seconds)
- 🌐 **ESP32 WiFi Access Point** - No router needed!
- 📈 **Live animated chart** with 100-point history
- 💤 **Sleep session tracking** with duration and disturbances
- 🎨 **Modern glassmorphism UI** with dark theme
- 📱 **Fully responsive** - Works on phone, tablet, and desktop

### Smart Alerts
- 🌅 **Morning Alert** (Lux ≥ 500): "Good Morning Kynatium Labs" with 🐔 chicken icon
- 🌙 **Night Alert** (Lux ≤ 10): "Time for Sleep" popup with 🐔 chicken icon
- 🔊 **Voice Alerts**: Browser TTS speaks "Good Morning Kynatium Labs" / "Time for Sleep Kynatium Labs"
- ⏰ **Auto-dismiss popups** - 3 seconds timer
- 🎯 **Smart detection** - Alerts only trigger once per threshold crossing

### Visual Experience
- 🎨 Deep blue and purple gradient backgrounds
- ✨ Smooth color transitions based on light levels
- 💎 Glassmorphism card effects
- 🐔 Fun chicken emoji popups for alerts
- 🎭 Clean, optimized UI with minimal animations
- 🔊 Audio feedback with browser speech synthesis

---

## 🖼️ Demo & Screenshots

### Dashboard Preview
```
┌─────────────────────────────────────────┐
│      🌙 Smart Sleep Monitor             │
│   Kynatium Labs - Light & Sleep Analytics│
├─────────────────────────────────────────┤
│  💡 Current Light Level                 │
│                                         │
│           234.5 Lux                     │
│      ☀️ Bright/Morning | 👁️ Awake      │
├─────────────────────────────────────────┤
│  📊 Light Level History                 │
│  [Smooth animated line chart]           │
├─────────────────────────────────────────┤
│  📈 Sleep Analytics                     │
│  Current: 0:00  Sessions: 5             │
│  Total: 42.5h   Disturbances: 3         │
└─────────────────────────────────────────┘
```

---

## 🛠️ Hardware Requirements

### Core Components
| Component | Specification | Quantity |
|-----------|--------------|----------|
| ESP32 Development Board | ESP32-WROOM-32, 240MHz | 1 |
| TSL2561 Light Sensor | I2C, 3.3V, 0.1-40,000 Lux | 1 |
| Jumper Wires (F-F) | 20cm length | 4 |
| USB Cable | Micro-USB or USB-C | 1 |
| Breadboard (Optional) | 400-830 tie-points | 1 |

### Supported ESP32 Boards
✅ ESP32 DevKit V1  
✅ NodeMCU-32S  
✅ ESP32-WROOM-32 Dev Board  
✅ DOIT ESP32 DevKit  
✅ ESP32 Feather (Adafruit)  
✅ FireBeetle ESP32  

---

## 💰 Bill of Materials

### Budget Breakdown
| Item | Price (USD) | Where to Buy |
|------|-------------|--------------|
| ESP32 Board | $8-12 | Amazon, AliExpress, Adafruit |
| TSL2561 Sensor | $5-8 | Adafruit (#439), Amazon |
| Jumper Wires (40pcs set) | $2-3 | Any electronics store |
| USB Cable | $3-5 | Reuse or buy online |
| **Total Estimated Cost** | **$18-28** | |

### Shopping Links
- **Adafruit TSL2561**: https://www.adafruit.com/product/439
- **ESP32 Search**: Amazon - "ESP32 Development Board"
- **Budget Option**: AliExpress - "ESP32 WROOM" + "TSL2561 module"

### Optional Components
- Enclosure/Case: $5-10
- Power Bank (for portability): $10-20
- MicroSD Module (data logging): $3-5
- OLED Display (local display): $5-8

---

## 📌 Wiring Diagram

### Simple Connection
```
┌─────────────────┐          ┌──────────────┐
│   TSL2561       │          │    ESP32     │
├─────────────────┤          ├──────────────┤
│ VCC (Red)    ───┼──────────┼──→ 3.3V      │
│ GND (Black)  ───┼──────────┼──→ GND       │
│ SDA (Blue)   ───┼──────────┼──→ GPIO 21   │
│ SCL (Yellow) ───┼──────────┼──→ GPIO 22   │
└─────────────────┘          └──────────────┘
```

### Pin Mapping Table
| TSL2561 Pin | Wire Color | ESP32 Pin | Function |
|-------------|-----------|-----------|----------|
| VCC/VIN | Red | 3.3V | Power Supply |
| GND | Black | GND | Ground |
| SDA | Blue | GPIO 21 | I2C Data |
| SCL | Yellow | GPIO 22 | I2C Clock |

### ⚠️ Important Notes
- **Use 3.3V, NOT 5V!** TSL2561 is a 3.3V device
- Double-check connections before powering on
- Ensure firm contact - loose wires cause communication errors
- Keep wires short (< 30cm) for reliable I2C communication

---

## 📚 Software Requirements

### Arduino IDE
- **Version**: 1.8.19 or newer (or Arduino IDE 2.x)
- **Download**: https://www.arduino.cc/en/software

### ESP32 Board Package
- **Package**: esp32 by Espressif Systems (v2.0.0+)
- **Board Manager URL**: 
  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```

### Required Libraries
| Library | Version | Installation |
|---------|---------|--------------|
| Adafruit TSL2561 | 1.1.0+ | Library Manager |
| Adafruit Unified Sensor | 1.1.0+ | Library Manager |
| WiFi | Built-in | Included with ESP32 |
| WebServer | Built-in | Included with ESP32 |

### Library Installation Links
- **Adafruit TSL2561**: https://github.com/adafruit/Adafruit_TSL2561
- **Adafruit Unified Sensor**: https://github.com/adafruit/Adafruit_Sensor

---

## 📥 Installation Guide

### Step 1: Install Arduino IDE

1. Download from https://www.arduino.cc/en/software
2. Install for your operating system (Windows/Mac/Linux)
3. Launch Arduino IDE

### Step 2: Add ESP32 Board Support

1. Open **File → Preferences**
2. In "Additional Board Manager URLs", paste:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Click **OK**
4. Go to **Tools → Board → Boards Manager**
5. Search for "ESP32"
6. Install **"esp32 by Espressif Systems"**
7. Wait for installation to complete

### Step 3: Install Required Libraries

**Option A: Via Library Manager (Recommended)**
1. Open **Tools → Manage Libraries** (or Sketch → Include Library → Manage Libraries)
2. Search and install each:
   - "Adafruit TSL2561"
   - "Adafruit Unified Sensor"

**Option B: Manual ZIP Installation**
1. Download library ZIPs from GitHub links above
2. **Sketch → Include Library → Add .ZIP Library**
3. Select downloaded ZIP files

### Step 4: Wire the Hardware

Follow the [Wiring Diagram](#-wiring-diagram) above to connect TSL2561 to ESP32.

### Step 5: Upload the Code

1. **Connect ESP32** to computer via USB
2. **Open** `ESP32_TSL2561_WebServer.ino` in Arduino IDE
3. **Select Board**: Tools → Board → ESP32 Arduino → ESP32 Dev Module
4. **Select Port**: Tools → Port → (Your COM port)
5. **Upload Settings** (recommended):
   - Upload Speed: 115200
   - Flash Frequency: 80MHz
   - Flash Mode: QIO
   - Partition Scheme: Default 4MB with spiffs
6. Click **Upload** button (→ arrow icon)
7. Wait for "Done uploading" message

### Step 6: Verify Upload

1. Open **Tools → Serial Monitor**
2. Set baud rate to **115200**
3. You should see:
   ```
   TSL2561 sensor initialized!
   =================================
   WiFi Access Point Created!
   SSID: Sleep-Monitor-AP
   Password: kynatium123
   IP Address: 192.168.4.1
   =================================
   Web server started!
   Lux: 234.5
   ```

---

## 🚀 Quick Start

### 1. Connect to WiFi
After uploading the code:
- **Network Name**: `Sleep-Monitor-AP`
- **Password**: `kynatium123`
- Connect from your phone/tablet/laptop

### 2. Open Dashboard
- Open web browser
- Navigate to: **http://192.168.4.1**
- Dashboard loads automatically

### 3. Start Monitoring
- Lux value updates every 2 seconds
- Chart builds up history automatically
- Alerts trigger based on light levels

---

## 🎨 Dashboard Features

### 1. Current Light Level Card
- **Large Lux Display**: Shows current light intensity
- **Dynamic Icon**: Changes based on light level
  - 🌙 Night (< 50 lux)
  - 🌆 Evening (50-99 lux)
  - 🌅 Daylight (100-499 lux)
  - ☀️ Bright/Morning (500+ lux)
- **Status Badges**: 
  - Light status (Night/Evening/Daylight/Morning)
  - Sleep status (Sleeping/Awake)

### 2. Light Level History Chart
- **100-point line graph** with smooth curves
- **Auto-updating** every 2 seconds
- **No animation lag** for smooth visualization
- **Gradient fill** under the line
- **Responsive** - Scales to screen size

### 3. Sleep Analytics Card
Four stat boxes displaying:
- **Current Session**: Hours:Minutes of current sleep
- **Total Sessions**: Number of sleep sessions tracked
- **Total Sleep**: Cumulative hours slept
- **Disturbances**: Light interruptions during sleep

### 4. Voice Alerts 🔊

The system uses **Browser Speech Synthesis API** (TTS) to speak alerts:

**Features**:
- **Automatic voice notifications** when alerts trigger
- **Clear audio feedback** without external speakers
- **Works on all modern browsers** (Chrome, Firefox, Safari, Edge)
- **Customizable voice settings**: Language (en-US), pitch (1.2), rate (1.0)
- **No additional hardware needed** - uses device speakers

**Voice Messages**:
- Morning: "Good Morning Kynatium Labs"
- Night: "Time for Sleep Kynatium Labs"

**Browser Compatibility**:
✅ Chrome/Edge (Windows, Mac, Android)  
✅ Safari (iOS, Mac)  
✅ Firefox (Desktop)  
⚠️ Requires user interaction first (browser security)

### 5. Alert Popups

#### Morning Alert (Lux ≥ 500)
- **Message**: "Good Morning!"
- **Subtitle**: "Rise and shine!"
- **Icon**: 🐔 Chicken (fun wake-up mascot)
- **Voice**: Browser TTS speaks "Good Morning Kynatium Labs"
- **Background**: Purple gradient
- **Action**: Automatically ends sleep session
- **Duration**: Auto-dismisses after 3 seconds
- **Button**: "✨ Thanks!" (closes popup)

#### Night Alert (Lux ≤ 10)
- **Message**: "Time for Sleep"
- **Subtitle**: "It's getting dark 🌙"
- **Icon**: 🐔 Chicken (bedtime mascot)
- **Voice**: Browser TTS speaks "Time for Sleep Kynatium Labs"
- **Background**: Purple gradient
- **Duration**: Auto-dismisses after 3 seconds if no action
- **Buttons**:
  - **😴 Sleeping**: Starts sleep tracking
  - **❌ Cancel**: Dismisses without action

---

## ⚙️ Configuration

### Adjust Light Thresholds

In `ESP32_TSL2561_WebServer.ino`, modify these values:

```cpp
#define MORNING_LUX_THRESHOLD 500  // Morning alert trigger
#define NIGHT_LUX_THRESHOLD 10     // Night alert trigger
```

**Examples**:
- **Early riser**: Change `MORNING_LUX_THRESHOLD` to `300`
- **Night owl**: Change `NIGHT_LUX_THRESHOLD` to `5`

### Change WiFi Credentials

```cpp
const char* ssid = "Sleep-Monitor-AP";      // Change network name
const char* password = "kynatium123";       // Change password
```

### Modify Update Frequency

```cpp
// ESP32 sensor reading (milliseconds)
if(millis() - lastUpdate > 2000)  // Change 2000 to desired interval

// JavaScript dashboard update (milliseconds)
setInterval(updateData, 2000);  // Change 2000 to match
```

### Adjust History Buffer Size

```cpp
float luxHistory[100];  // Change 100 to desired size
// Also update in JavaScript:
labels: Array(100).fill(''),  // Match the size
```

---

## 📡 API Documentation

### Base URL
```
http://192.168.4.1
```

### Endpoints

#### 1. `GET /`
**Description**: Serves main HTML dashboard  
**Response**: `text/html`  
**Status**: 200 OK

#### 2. `GET /api/lux`
**Description**: Returns current lux value  
**Response**:
```json
{
  "lux": 234.5
}
```
**Update**: Real-time (sensor reading)  
**Status**: 200 OK

#### 3. `GET /api/history`
**Description**: Returns last 100 lux readings  
**Response**:
```json
{
  "history": [120.5, 121.3, 123.1, ..., 234.5]
}
```
**Buffer**: Circular buffer (100 samples)  
**Status**: 200 OK

#### 4. `GET /api/sleep`
**Description**: Returns current sleep session status  
**Response**:
```json
{
  "status": "sleeping",
  "duration": 7200,
  "disturbances": 3
}
```
**Fields**:
- `status`: "sleeping" or "awake"
- `duration`: Seconds since sleep started
- `disturbances`: Count of light interruptions (lux > 50)

**Status**: 200 OK

#### 5. `GET /api/stats`
**Description**: Returns overall statistics  
**Response**:
```json
{
  "sessions": 5,
  "totalHours": 42.5,
  "uptime": 86400,
  "disturbances": 12
}
```
**Status**: 200 OK

#### 6. `POST /api/sleep-action`
**Description**: Control sleep tracking  
**Content-Type**: `application/x-www-form-urlencoded`  
**Parameters**: 
- `action`: "sleeping" | "cancel" | "wake"

**Request Body**:
```
action=sleeping
```

**Response**:
```json
{
  "status": "ok",
  "message": "Sleep started"
}
```
**Status**: 200 OK / 400 Bad Request

---

## 🔧 Technical Specifications

### Hardware Specs

#### TSL2561 Sensor
- **Type**: Digital Luminosity/Lux/Light Sensor
- **Interface**: I2C (address 0x39, 0x29, or 0x49)
- **Voltage**: 2.7V - 3.6V (3.3V recommended)
- **Range**: 0.1 - 40,000+ Lux
- **Resolution**: 16-bit
- **Integration Time**: 402ms (configured)
- **Gain**: 1X (low gain for bright environments)
- **Current Draw**: 0.5mA active, 15µA sleep
- **Accuracy**: Human eye response curve
- **Auto-range**: Enabled for dynamic light conditions

#### ESP32 Microcontroller
- **CPU**: Dual-core Tensilica LX6 @ 240MHz
- **RAM**: 520KB SRAM
- **Flash**: 4MB (typical)
- **WiFi**: 802.11 b/g/n (2.4GHz)
- **I2C Pins**: GPIO 21 (SDA), GPIO 22 (SCL)
- **Power**: ~160mA @ 3.3V (WiFi active)

### Software Architecture

```
System Components:
├── Sensor Reading Module
│   ├── TSL2561 I2C Communication
│   ├── Auto-range mode
│   └── 402ms integration time
├── WiFi Access Point Module
│   ├── SSID: Sleep-Monitor-AP
│   ├── IP: 192.168.4.1
│   └── WPA2 Security
├── Web Server Module
│   ├── HTTP/1.1 Protocol
│   ├── REST API (6 endpoints)
│   └── Embedded HTML/CSS/JS
└── Data Management Module
    ├── Circular buffer (100 samples)
    ├── Sleep session tracking
    └── Statistics calculation
```

### Performance Metrics
- **Sensor Update**: 2 seconds
- **Dashboard Update**: 2 seconds
- **API Response Time**: < 10ms
- **Chart Rendering**: ~50ms initial, ~5ms updates
- **Memory Usage**: ~565KB Flash, ~82KB RAM
- **Max Clients**: 4 simultaneous connections

### Network Configuration
- **Access Point**: 192.168.4.1
- **Subnet Mask**: 255.255.255.0
- **DHCP Range**: 192.168.4.2 - 192.168.4.254
- **Web Server Port**: 80 (HTTP)
- **Max Connections**: 4

---

## 🐛 Troubleshooting

### Hardware Issues

#### Problem: "TSL2561 sensor not found!"
**Symptoms**: Error in Serial Monitor, program stuck  
**Solutions**:
1. Check wiring connections (see [Wiring Diagram](#-wiring-diagram))
2. Verify sensor has power (some have LED indicator)
3. Try different I2C address:
   ```cpp
   Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);
   // or TSL2561_ADDR_HIGH
   ```
4. Test with I2C scanner sketch

#### Problem: Sensor reads -1 or 0
**Symptoms**: Dashboard shows -1.0 or 0.0 lux  
**Solutions**:
- **-1**: Sensor overload (too bright) - reduce light or cover partially
- **0**: Connection issue - check wiring
- **Constant 0**: Wrong I2C address

#### Problem: ESP32 not detected in Arduino IDE
**Symptoms**: No COM port available  
**Solutions**:
1. Install USB drivers:
   - **CH340**: http://www.wch-ic.com/downloads/CH341SER_ZIP.html
   - **CP2102**: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
2. Try different USB cable (must be data-capable)
3. Try different USB port on computer
4. Restart Arduino IDE

### Software Issues

#### Problem: Compilation errors
**Error**: `Adafruit_TSL2561_U.h: No such file or directory`  
**Solution**: Install required libraries (see [Installation](#-installation-guide))

**Error**: `WebServer.h: No such file or directory`  
**Solution**: Install ESP32 board package correctly

#### Problem: Upload fails
**Error**: `Failed to connect to ESP32`  
**Solutions**:
1. Hold **BOOT** button while clicking Upload
2. Check correct board selected: Tools → Board → ESP32 Dev Module
3. Lower upload speed: Tools → Upload Speed → 115200
4. Try different COM port

### Network Issues

#### Problem: Can't find "Sleep-Monitor-AP" WiFi
**Symptoms**: Network not visible  
**Solutions**:
1. Wait 30-60 seconds after uploading
2. Check Serial Monitor - should show "WiFi Access Point Created!"
3. Restart ESP32 (press RESET button)
4. Try from different device

#### Problem: Dashboard doesn't load
**Symptoms**: Browser shows "Can't reach this page"  
**Solutions**:
1. Verify connected to "Sleep-Monitor-AP" WiFi
2. Try both:
   - http://192.168.4.1
   - http://192.168.4.1/ (with trailing slash)
3. Disable mobile data (phone only)
4. Try different browser
5. Clear browser cache

#### Problem: Data not updating
**Symptoms**: Lux value frozen, chart not moving  
**Solutions**:
1. Open browser console (F12) - check for JavaScript errors
2. Refresh page (Ctrl+F5 / Cmd+Shift+R)
3. Check Serial Monitor for sensor errors
4. Verify multiple clients aren't connected (max 4)

### Alert Issues

#### Problem: Alerts not triggering
**Solutions**:
1. Verify lux value crosses threshold:
   - Morning: Must reach ≥ 500 lux
   - Night: Must drop to ≤ 10 lux
2. Alerts trigger only once per crossing
3. Check browser console for JavaScript errors
4. Popup blockers may interfere

#### Problem: Popup doesn't auto-close
**Solution**: JavaScript timeout may be blocked - manually close with button

---

## 🎨 Customization

### Change Dashboard Colors

Edit CSS in the `getHTML()` function:

```css
/* Background gradient */
body {
    background: linear-gradient(135deg, #0f0c29, #302b63, #24243e);
}

/* Card background */
.card {
    background: rgba(255, 255, 255, 0.05);
}

/* Lux display gradient */
.lux-display {
    background: linear-gradient(90deg, #f093fb 0%, #f5576c 100%);
}
```

### Customize Voice Settings

Modify speech synthesis parameters in the JavaScript:

```javascript
function speakText(text){
  if('speechSynthesis' in window){
    let u=new SpeechSynthesisUtterance(text);
    u.lang='en-US';  // Change language: 'en-GB', 'es-ES', etc.
    u.pitch=1.2;     // Change pitch: 0.5 to 2.0
    u.rate=1;        // Change speed: 0.1 to 10
    window.speechSynthesis.speak(u);
  }
}
```

### Add Custom Icons

Replace emoji icons with Font Awesome or custom images:

```javascript
iconEl.textContent = '🐔';  // Fun chicken icon for alerts
// Or use Font Awesome: <i class="fa fa-chicken"></i>
```

### Modify Chart Appearance

In JavaScript chart configuration:

```javascript
borderColor: 'rgba(102, 126, 234, 1)',     // Line color
backgroundColor: 'rgba(102, 126, 234, 0.1)', // Fill color
borderWidth: 3,                              // Line thickness
tension: 0.4,                                // Curve smoothness (0-1)
```

### Add More Statistics

Extend the stats API to include custom metrics:

```cpp
// In handleStats()
json += "\"avgLux\":" + String(calculateAverage()) + ",";
json += "\"minLux\":" + String(minLuxValue) + ",";
json += "\"maxLux\":" + String(maxLuxValue);
```

### Store Data Permanently

Use ESP32 filesystem to save data:

```cpp
#include <SPIFFS.h>

void saveData() {
  File file = SPIFFS.open("/data.txt", FILE_WRITE);
  file.println(currentLux);
  file.close();
}
```

### Add More Sensors

Expand with additional I2C sensors:

```cpp
#include <Adafruit_BME280.h>  // Temperature/Humidity
Adafruit_BME280 bme;

void setup() {
  bme.begin(0x76);
}

void loop() {
  float temp = bme.readTemperature();
  float humidity = bme.readHumidity();
}
```

---

## 🌟 Future Enhancements

### Planned Features
- [ ] Data export to CSV
- [ ] Historical data persistence (SPIFFS/SD card)
- [ ] MQTT integration for IoT platforms
- [ ] Mobile app (React Native)
- [x] ✅ Voice notifications (Browser TTS) - **COMPLETED**
- [x] ✅ Fun chicken popup icons - **COMPLETED**
- [ ] Machine learning sleep quality prediction
- [ ] Multiple user profiles
- [ ] Cloud sync and remote access
- [ ] Adjustable voice pitch and language selection UI
- [ ] Custom alert sounds with audio files

### Community Ideas
Have an idea? Open an issue or submit a pull request!

---

## 🤝 Contributing

Contributions are welcome! Here's how:

1. Fork the repository
2. Create feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

---

## 📞 Support

Having issues? Here's how to get help:

1. **Check [Troubleshooting](#-troubleshooting)** section first
2. **Serial Monitor**: Always check output at 115200 baud
3. **Browser Console**: Press F12 to see JavaScript errors
4. **GitHub Issues**: Report bugs with:
   - Hardware details (ESP32 model, sensor module)
   - Full error messages
   - Serial Monitor output
   - Steps to reproduce

---

## 📄 License

MIT License

Copyright (c) 2026 Kynatium Labs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## 🙏 Acknowledgments

- **Adafruit** - For excellent TSL2561 library and sensor breakout
- **Espressif** - For ESP32 Arduino core
- **Chart.js** - For beautiful data visualization
- **Kynatium Labs** - Project sponsor and inspiration

---

## 👨‍💻 Author

**Created for Kynatium Labs**

Built with ❤️ using ESP32, TSL2561, and modern web technologies.

---

## 📊 Project Stats

- **Lines of Code**: ~315 (Optimized and streamlined)
- **Arduino Code**: Compact and efficient
- **Features**: Real-time monitoring + Voice alerts + Sleep tracking
- **Cost**: < $30 in components
- **Power Consumption**: ~0.53W active
- **WiFi Range**: ~30m typical
- **Browser Compatibility**: All modern browsers with TTS support

---

**Happy Sleep Monitoring! 😴💤🌙**
