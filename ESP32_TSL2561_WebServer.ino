/*
 * Smart Sleep Monitoring System with TSL2561 Sensor
 * Upgraded by ChatGPT
 * Features:
 * - TSL2561 Light sensor integration
 * - ESP32 WiFi Access Point
 * - Web-based dashboard
 * - Real-time lux monitoring
 * - Smart morning/night alerts with chicken popup
 * - Voice alert in web using browser TTS
 */

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// WiFi Access Point
const char* ssid = "Sleep-Monitor-AP";
const char* password = "kynatium123";

// TSL2561 sensor
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// Web server
WebServer server(80);

// Lux thresholds
#define MORNING_LUX_THRESHOLD 500
#define NIGHT_LUX_THRESHOLD 10

// Data storage
float currentLux = 0;
float luxHistory[100];
int historyIndex = 0;
unsigned long lastUpdate = 0;
unsigned long sessionStartTime = 0;

// Sleep tracking45
bool isSleeping = false;
unsigned long sleepStartTime = 0;
int sleepSessions = 0;
float totalSleepHours = 0;
int disturbanceCount = 0;

void setup() {
  Serial.begin(115200);
  
  Wire.begin(21,22); // SDA=21, SCL=22

  if(!tsl.begin()){
    Serial.println("TSL2561 sensor not found!");
    while(1);
  }

  // Configure sensor
  tsl.enableAutoRange(true);
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);
  tsl.setGain(TSL2561_GAIN_1X); // Start with low gain

  Serial.println("TSL2561 initialized!");

  // WiFi AP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP: "); Serial.println(IP);

  // Server routes
  server.on("/", handleRoot);
  server.on("/api/lux", handleLux);
  server.on("/api/history", handleHistory);
  server.on("/api/sleep", handleSleep);
  server.on("/api/stats", handleStats);
  server.on("/api/sleep-action", HTTP_POST, handleSleepAction);
  
  server.begin();
  Serial.println("Web server started!");

  sessionStartTime = millis();
  for(int i=0;i<100;i++) luxHistory[i]=0;
}

void loop() {
  server.handleClient();

  if(millis()-lastUpdate>2000){
    sensors_event_t event;
    tsl.getEvent(&event);

    if(event.light){
      currentLux = event.light;

      // Store history
      luxHistory[historyIndex] = currentLux;
      historyIndex = (historyIndex + 1) % 100;

      // Check disturbances
      if(isSleeping && currentLux>50) disturbanceCount++;

      Serial.print("Lux: "); Serial.println(currentLux);
    }else{
      Serial.println("Sensor error/overload");
      currentLux = -1;
    }

    lastUpdate = millis();
  }
}

// Web pages & API
void handleRoot(){ server.send(200,"text/html",getHTML()); }
void handleLux(){ server.send(200,"application/json","{\"lux\":" + String(currentLux) + "}"); }

void handleHistory(){
  String json="{\"history\":[";
  for(int i=0;i<100;i++){
    int idx=(historyIndex+i)%100;
    json+=String(luxHistory[idx]);
    if(i<99) json+=",";
  }
  json+="]}";
  server.send(200,"application/json",json);
}

void handleSleep(){
  String status = isSleeping?"sleeping":"awake";
  unsigned long duration=0;
  if(isSleeping) duration=(millis()-sleepStartTime)/1000;
  String json="{\"status\":\""+status+"\",\"duration\":"+String(duration)+",\"disturbances\":"+String(disturbanceCount)+"}";
  server.send(200,"application/json",json);
}

void handleStats(){
  unsigned long uptime=(millis()-sessionStartTime)/1000;
  String json="{\"sessions\":"+String(sleepSessions)+",\"totalHours\":"+String(totalSleepHours,1)+",\"uptime\":"+String(uptime)+",\"disturbances\":"+String(disturbanceCount)+"}";
  server.send(200,"application/json",json);
}

void handleSleepAction(){
  if(server.hasArg("action")){
    String act=server.arg("action");
    if(act=="sleeping"){
      isSleeping=true; sleepStartTime=millis(); disturbanceCount=0; sleepSessions++;
      Serial.println("Sleep started");
      server.send(200,"application/json","{\"status\":\"ok\",\"message\":\"Sleep started\"}");
    }else if(act=="cancel"){
      if(isSleeping){
        float hours=(millis()-sleepStartTime)/3600000.0;
        totalSleepHours+=hours; isSleeping=false; Serial.println("Sleep cancelled");
      }
      server.send(200,"application/json","{\"status\":\"ok\",\"message\":\"Cancelled\"}");
    }else if(act=="wake"){
      if(isSleeping){
        float hours=(millis()-sleepStartTime)/3600000.0;
        totalSleepHours+=hours; isSleeping=false; Serial.println("Woke up");
      }
      server.send(200,"application/json","{\"status\":\"ok\",\"message\":\"Woke up\"}");
    }
  }else server.send(400,"application/json","{\"status\":\"error\",\"message\":\"No action provided\"}");
}

// HTML + JS + CSS
String getHTML(){
  return R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Smart Sleep Monitor</title>
<style>
body{font-family:sans-serif;margin:0;padding:0;background:#0f0c29;color:#fff;}
.container{max-width:1200px;margin:auto;padding:20px;}
.header{text-align:center;margin-bottom:30px;}
.header h1{font-size:2.5em;color:#f093fb;}
.card{background:rgba(255,255,255,0.05);padding:20px;margin-bottom:20px;border-radius:15px;}
.lux-display{font-size:3em;text-align:center;margin:10px 0;}
.status-badge{padding:5px 15px;border-radius:20px;margin:5px;}
.status-sleeping{background:linear-gradient(90deg,#4776E6,#8E54E9);}
.status-awake{background:linear-gradient(90deg,#f093fb,#f5576c);}
.status-morning{background:linear-gradient(90deg,#FFB75E,#ED8F03);}
.status-night{background:linear-gradient(90deg,#2E3192,#1BFFFF);}
.popup-overlay{display:none;position:fixed;top:0;left:0;width:100%;height:100%;background:rgba(0,0,0,0.8);z-index:1000;}
.popup{position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);background:#764ba2;padding:30px;border-radius:20px;text-align:center;}
.btn{padding:10px 25px;margin:5px;border:none;border-radius:20px;cursor:pointer;}
.btn-primary{background:#fff;color:#764ba2;}
.btn-secondary{background:rgba(255,255,255,0.3);color:#fff;}
</style>
</head>
<body>
<div class="container">
  <div class="header">
    <h1>🌙 Smart Sleep Monitor</h1>
    <p>Live Light & Sleep Dashboard</p>
  </div>
  <div class="card">
    <div>Current Light Level:</div>
    <div class="lux-display" id="luxValue">--</div>
    <div>
      <span class="status-badge" id="lightStatus">Measuring...</span>
      <span class="status-badge" id="sleepStatus">Awake</span>
    </div>
  </div>

  <div class="card">
    <div>Sleep Analytics:</div>
    <div>Current Session: <span id="sleepDuration">0:00</span></div>
    <div>Total Sessions: <span id="sleepSessions">0</span></div>
    <div>Total Sleep: <span id="totalHours">0.0h</span></div>
    <div>Disturbances: <span id="disturbances">0</span></div>
  </div>
</div>

<div class="popup-overlay" id="popupOverlay">
  <div class="popup">
    <div id="popupIcon">🐔</div>
    <h2 id="popupTitle">Popup</h2>
    <p id="popupMessage">Message</p>
    <button class="btn btn-primary" id="btnSleeping">😴 Sleeping</button>
    <button class="btn btn-secondary" id="btnCancel">❌ Cancel</button>
  </div>
</div>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
let lastAlert=null;

function speakText(text){
  if('speechSynthesis' in window){
    let u=new SpeechSynthesisUtterance(text);
    u.lang='en-US'; u.pitch=1.2; u.rate=1;
    window.speechSynthesis.speak(u);
  }
}

function showMorningPopup(){
  document.getElementById('popupIcon').textContent='🐔';
  document.getElementById('popupTitle').textContent='Good Morning!';
  document.getElementById('popupMessage').textContent='Rise and shine!';
  document.getElementById('btnSleeping').style.display='none';
  document.getElementById('btnCancel').textContent='✨ Thanks!';
  document.getElementById('popupOverlay').style.display='block';
  speakText("Good Morning Kynatium Labs");
  fetch('/api/sleep-action',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action=wake'});
  setTimeout(()=>{document.getElementById('popupOverlay').style.display='none';document.getElementById('btnSleeping').style.display='inline-block';},3000);
}

function showNightPopup(){
  document.getElementById('popupIcon').textContent='🐔';
  document.getElementById('popupTitle').textContent='Time for Sleep';
  document.getElementById('popupMessage').textContent='It\'s getting dark 🌙';
  document.getElementById('btnSleeping').style.display='inline-block';
  document.getElementById('btnCancel').textContent='❌ Cancel';
  document.getElementById('popupOverlay').style.display='block';
  speakText("Time for Sleep Kynatium Labs");
  setTimeout(()=>{if(document.getElementById('popupOverlay').style.display==='block') document.getElementById('popupOverlay').style.display='none';},3000);
}

// Button handlers
document.getElementById('btnSleeping').addEventListener('click',()=>{
  fetch('/api/sleep-action',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action=sleeping'}).then(()=>{document.getElementById('popupOverlay').style.display='none';updateData();});
});
document.getElementById('btnCancel').addEventListener('click',()=>{
  fetch('/api/sleep-action',{method:'POST',headers:{'Content-Type':'application/x-www-form-urlencoded'},body:'action=cancel'}).then(()=>{document.getElementById('popupOverlay').style.display='none';updateData();});
});

// Update loop
function updateData(){
  fetch('/api/lux').then(r=>r.json()).then(data=>{
    const lux=data.lux;
    document.getElementById('luxValue').textContent=lux.toFixed(1);
    updateStatus(lux);
    checkAlerts(lux);
  });
  fetch('/api/sleep').then(r=>r.json()).then(data=>{
    if(data.status==='sleeping'){
      let h=Math.floor(data.duration/3600);
      let m=Math.floor((data.duration%3600)/60);
      document.getElementById('sleepDuration').textContent=h+":"+m.toString().padStart(2,'0');
      document.getElementById('sleepStatus').textContent='😴 Sleeping';
      document.getElementById('sleepStatus').className='status-badge status-sleeping';
    }else{
      document.getElementById('sleepDuration').textContent='0:00';
      document.getElementById('sleepStatus').textContent='👁️ Awake';
      document.getElementById('sleepStatus').className='status-badge status-awake';
    }
    document.getElementById('disturbances').textContent=data.disturbances;
  });
  fetch('/api/stats').then(r=>r.json()).then(data=>{
    document.getElementById('sleepSessions').textContent=data.sessions;
    document.getElementById('totalHours').textContent=data.totalHours+'h';
  });
}
setInterval(updateData,2000);

function updateStatus(lux){
  const statusEl=document.getElementById('lightStatus');
  if(lux>=500){ statusEl.textContent='☀️ Bright/Morning'; statusEl.className='status-badge status-morning'; }
  else if(lux>=100){ statusEl.textContent='🌅 Daylight'; statusEl.className='status-badge status-morning'; }
  else if(lux>=50){ statusEl.textContent='🌆 Evening'; statusEl.className='status-badge'; }
  else { statusEl.textContent='🌙 Night'; statusEl.className='status-badge status-night'; }
}

function checkAlerts(lux){
  if(lux>=500 && lastAlert!=='morning'){ lastAlert='morning'; showMorningPopup(); }
  else if(lux<=10 && lastAlert!=='night'){ lastAlert='night'; showNightPopup(); }
  else if(lux>10 && lux<500) lastAlert=null;
}
</script>
</body>
</html>
)rawliteral";
}
