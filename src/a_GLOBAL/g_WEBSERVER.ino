// WEBSERVER STUFF
String HEADER = "<!DOCTYPE html>\
  <html lang='en'>\
  <head>\
  <meta charset='UTF-8'>\
  <meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, shrink-to-fit=no'>\
  <title>vMix M5Stick-C Tally</title>\
  <style>\
  @import url(https://fonts.googleapis.com/css2?family=Open+Sans&display=swap);.wrapper,input[type=text],input[type=number],input[type=submit],select{width:100%;box-sizing:border-box}body,html{background:#2b2b2b;color:#eee;padding:0;margin:0;font-family:'Open Sans',verdana,sans-serif}.wrapper{padding:10px}.wrapper h1{text-align:center}input[type=text],input[type=number],select{margin-bottom:10px}input,select{background-color:#6d6d6d;color:#f0f0f0;border:1px solid #000;font-size:18px;height:35px;padding:0 5px}input[type=submit]{height:50px;margin:0 auto}@media screen and (min-width:600px){.wrapper{width:600px;margin:0 auto}}\
  </style>\
  </head>\
  <body>\
  <div class='wrapper'>";

String FOOTER = "</div>\
  </body>\
  </html>";

void handle_root()
{
  String tally = (String)TALLY_NR;
  String justLive = (String)JUSTLIVE;
  String bright = (String)BRIGHTNESS;
  String _mode = (String)MODE;
  String _pmmode = (String)PM_MODE;
  String _pmcolor = (String)PM_COLOR;
  String _vmixcustomenable = (String)VMIX_CUSTOM_ENABLE;
  String vmixcustomport = (String)VMIX_CUSTOM_PORT;
  String HTML = HEADER;

  HTML += "<div class=wrapper data-theme=light><h1>vMix M5Stack Tally Settings</h1><form action=/save id=frmData method=post onsubmit=return!1><div>SSID:<br><select id=ssid><option disabled selected>Scanning wifi...</option></select></div><div class=ssidCustomDiv style=display:none>Hidden SSID Name:<br><input id=ssidCustom type=text value='" + (String)WIFI_SSID + "'name=ssidCustom></div><div>Password:<br><input id=pwd type=text value='" + (String)WIFI_PASS + "'name=pwd></div><div>vMix IP Address:<br><input id=vmixip type=text value='" + (String)VMIX_IP + "'name=vmixip></div><div>vMix Use Custom TCP Port:<br><select id=drpVmixcustomenable name=vmixcustomenable><option value=0>Disabled, Will use Port 8099</option><option value=1>Enable Custom TCP Port</option></select></div><div>vMix Custom TCP Port:<br><input id=vmixcustomport type=number value='" + vmixcustomport + "'name=vmixcustomport max=65000 min=0></div><div>Main Tally Number:<br><input id=tally_num type=number value='" + tally + "'name=tally_num max=1000 min=1></div><div>Multi Input (comma separated):<br><input id=m_tally type=text value='" + (String)M_TALLY + "'name=m_tally></div><div>Reconnect interval (in seconds, 0 means no reconnection interval):<br><input id=conn_int type=number value='" + CONN_INT + "'name=conn_int></div><div>Brightness:<br><select id=drpBright name=bright><option value=7>0%</option><option value=8>10%</option><option value=9>20%</option><option value=10>40%</option><option value=11>60%</option><option value=12>80%</option><option value=13>100%</option></select></div><div>Just Live:<br><select id=drpJustLive name=justLive><option value=0>False</option><option value=1>True</option></select></div><div>Mode:<br><select id=drpMode name=mode><option value=0>Text (SAFE, PRE, LIVE)</option><option value=1>Tally Number</option></select></div><div>LED Matrix Mode:<br><select id=drpPMMode name=pmmode><option value=0>Follow Input Tally</option><option value=1>Follow PGM Tally</option><option value=2>Follow PVW Tally</option><option value=3>Follow Input Tally, Hidden Numbers</option></select></div><div>LED Number Colors:<br><select id=drpPMColor name=pmcolor><option value=0>Disable Colored Numbers</option><option value=1>Enable Colored Numbers</option></select></div><input id=btnSave type=submit value=SAVE class='btn btn-primary'></form><h2>Reconnect to vMix</h2><form action=/reconnect id=frmReconnect method=post onsubmit=return!1><input id=btnReconnect type=submit value=RECONNECT></form></div><script>const btnSave = document.querySelector('#btnSave'); const btnReconnect = document.querySelector('#btnReconnect'); const drpBright = document.querySelector('#drpBright'); const ssidSelect = document.querySelector('#ssid'); const drpJustLive = document.querySelector('#drpJustLive'); const drpVmixcustomenable = document.querySelector('#drpVmixcustomenable'); const drpMode = document.querySelector('#drpMode'); const drpPMMode = document.querySelector('#drpPMMode'); const drpPMColor = document.querySelector('#drpPMColor'); drpBright.value = '" + bright + "'; drpJustLive.value = '" + justLive + "'; drpVmixcustomenable.value = '" + _vmixcustomenable + "'; drpMode.value = '" + _mode + "'; drpPMMode.value = '" + _pmmode + "'; drpPMColor.value = '" + _pmcolor + "'; btnSave.addEventListener('click', async function(e){ e.preventDefault(); let ssid = document.querySelector('#ssid').value; if(ssid === '__hidden__'){ ssid = document.querySelector('#ssidCustom').value; } const pwd = document.querySelector('#pwd').value; const vmixip = document.querySelector('#vmixip').value; const vmixcustomport = document.querySelector('#vmixcustomport').value; const m_tally = document.querySelector('#m_tally').value; const frmData = document.querySelector('#frmData'); const tally_num = document.querySelector('#tally_num').value; const bright = drpBright.value; const vmixcustomenable = drpVmixcustomenable.value; const mode = drpMode.value; const pmmode = drpPMMode.value; const pmcolor = drpPMColor.value; const justLive = drpJustLive.value; const conn_int = parseInt(document.querySelector('#conn_int').value, 10) || 0; let formData = new FormData(); formData.append('ssid', ssid.trim()); formData.append('pwd',pwd.trim()); formData.append('vmixip', vmixip.trim()); formData.append('vmixcustomenable', vmixcustomenable); formData.append('vmixcustomport', vmixcustomport); formData.append('m_tally', m_tally.trim().replace(/[^0-9,]+/g, '')); formData.append('tally_num', tally_num); formData.append('conn_int', conn_int); formData.append('bright', bright); formData.append('mode', mode); formData.append('pmmode', pmmode); formData.append('pmcolor', pmcolor); formData.append('justLive', justLive); btnSave.setAttribute('disabled', ''); const res = await fetch('/save', { method: 'POST', cache: 'no-cache', referrerPolicy: 'no-referrer', body: formData }); if(res.status === 200){ btnSave.value = 'SETTINGS SAVED!'; await setTimeout(()=>{btnSave.value = 'SAVE';}, 3000); } btnSave.removeAttribute('disabled'); }); btnReconnect.addEventListener('click', function(e){ e.preventDefault(); fetch('/reconnect'); }); ssidSelect.addEventListener('change', e => { const val = e.target.value; const ssidcd = document.querySelector('.ssidCustomDiv'); if(val === '__hidden__'){ ssidcd.style.display = 'block'; } else { ssidcd.style.display = 'none'; } }); document.addEventListener('DOMContentLoaded', async function(){ const res = await fetch('/scanNetwork'); res.text().then(text=>{ let networks = [text]; let str = ''; if(text.indexOf('|||') !== -1){ networks = text.split('|||'); } let sel = document.getElementById('ssid'); sel.innerHTML = ''; let existingNetwork = ''; networks.forEach(network => { let opt = document.createElement('option'); opt.appendChild( document.createTextNode(network) ); opt.value = network; if('" + (String)WIFI_SSID + "' === network){ existingNetwork = network; } sel.appendChild(opt); }); let opt = document.createElement('option'); opt.appendChild( document.createTextNode('Hidden network') ); opt.value = '__hidden__'; sel.appendChild(opt); if(existingNetwork !== ''){ sel.value = existingNetwork; } }); });</script>";
  HTML += FOOTER;

  server.send(200, "text/html", HTML);
}

void handle_save()
{
  String message = "";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  message += " direct:" + server.arg("tally_num");
  server.send(200, "text/plain", message);
  Serial.println(message);

  String tally = server.arg("tally_num");
  String bright = server.arg("bright");
  String justLive = server.arg("justLive");
  String _mode = server.arg("mode");
  String _pmmode = server.arg("pmmode");
  String _pmcolor = server.arg("pmcolor");
  String _vmixcustomenable = server.arg("vmixcustomenable");
  String vmixcustomport = server.arg("vmixcustomport");
  String conn_int = server.arg("conn_int");

  Serial.print("BRIGHTNESS: ");
  Serial.println(bright);

  // save value in preferences
  preferences.begin("vMixTally", false);
  if (tally != "")
  {
    TALLY_NR = std::atoi(tally.c_str());
    preferences.putUInt("tally", TALLY_NR);
    Serial.println("PUT TALLY NR");
  }
  if (bright != "") {
    BRIGHTNESS = std::atoi(bright.c_str());
    preferences.putUInt("bright", BRIGHTNESS);
    Serial.println("PUT BRIGHT");
  }
  if (justLive != "") {
    JUSTLIVE = std::atoi(justLive.c_str());
    preferences.putUInt("justLive", JUSTLIVE);
    Serial.println("PUT JUSTLIVE");
  }
  if (_mode != "") {
    MODE = std::atoi(_mode.c_str());
    preferences.putUInt("mode", MODE);
    Serial.println("PUT MODE");
  }
  if (_pmmode != "") {
    PM_MODE = std::atoi(_pmmode.c_str());
    preferences.putUInt("pmmode", PM_MODE);
    Serial.println("PUT PM_MODE");
  }
  if (_pmcolor != "") {
    PM_COLOR = std::atoi(_pmcolor.c_str());
    preferences.putUInt("pmcolor", PM_COLOR);
    Serial.println("PUT PM_COLOR");
  }

  if (_vmixcustomenable != "") {
    VMIX_CUSTOM_ENABLE = std::atoi(_vmixcustomenable.c_str());
    preferences.putUInt("customenable", VMIX_CUSTOM_ENABLE);
    Serial.print("PUT VMIX_CUSTOM_ENABLE");
  }

  if (vmixcustomport != "") {
    VMIX_CUSTOM_PORT = std::atoi(vmixcustomport.c_str());
    preferences.putUInt("vmixcustomport", VMIX_CUSTOM_PORT);
    Serial.println("PUT VMIX_CUSTOM_PORT");
  }

  if (server.arg("ssid") != "")
  {
    WIFI_SSID = server.arg("ssid");
    WIFI_PASS = server.arg("pwd");
    preferences.putString("wifi_ssid", &(WIFI_SSID[0]));
    preferences.putString("wifi_pass", &(WIFI_PASS[0]));
    Serial.println("PUT WIFI_SSID & WIFI PASS");
  }

  M_TALLY = server.arg("m_tally");
  preferences.putString("m_tally", &(M_TALLY[0]));

  if (conn_int != "")
  {
    CONN_INT = std::atoi(conn_int.c_str());
    preferences.putUInt("connint", CONN_INT);
    Serial.print("PUT CONN INT: ");
    Serial.println(CONN_INT);
  }

  if (server.arg("vmixip") != "")
  {
    VMIX_IP = server.arg("vmixip");
    preferences.putString("vmix_ip", &(VMIX_IP[0]));
    Serial.println("PUT VMIX IP");
  }
  preferences.end();

  cls();
  delay(100);

  //Reboot stick
  ESP.restart(); //Thanks to Babbit on vMix forums!
}

void handleReconnect() {
  connectTovMix(false);
  server.send(200, "text/plain", "success");
}

void handleScanNetwork() {
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {

  } else {
    String retStr = "";
    for (int thisNet = 0; thisNet < numSsid; thisNet++) {
      if (thisNet == 0) {
        retStr += WiFi.SSID(thisNet);
      } else {
        retStr += "|||" + WiFi.SSID(thisNet);
      }
    }
    server.send(200, "text/plain", retStr);
  }
}

void startServer()
{
  server.on("/", handle_root);
  server.on("/save", handle_save);
  server.on("/reconnect", handleReconnect);
  server.on("/scanNetwork", handleScanNetwork);
  server.begin();
  Serial.println("HTTP server started");
}
