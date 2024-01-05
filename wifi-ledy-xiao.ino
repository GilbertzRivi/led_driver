#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

int r = 2;
int g = 3;
int b = 4;
int ww = 5;
int cw = 6;
int rv = 0;
int gv = 0;
int bv = 0;
int wwv = 0;
int cwv = 0;
int ontime;
int offtime;
bool strobo;
String response;
const char* ssid = "Matka Boska"; 
const char* password = "Zbawienie420";
WebServer server(80);

void setup() {
  Serial.begin(115200);
  ledcSetup(1, 10000, 8);
  ledcSetup(2, 10000, 8);
  ledcSetup(3, 10000, 8);
  ledcSetup(4, 10000, 8);
  ledcSetup(5, 10000, 8);
  ledcAttachPin(r, 1);
  ledcAttachPin(g, 2);
  ledcAttachPin(b, 3);
  ledcAttachPin(ww, 4);
  ledcAttachPin(cw, 5);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(100);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());
  server.on("/", handle_OnConnect);
  server.on("/form/", handle_form);
  server.on("/status/", handle_status);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void handle_OnConnect() {
  server.send(200, "text/html", mainPage());
}

void handle_form() {
  if (server.method() == HTTP_POST){
    for (uint8_t i = 0; i < server.args(); i++)
      {
        if (server.argName(i) == "r"){
          ledcWrite(1, server.arg(i).toInt());
          rv = server.arg(i).toInt();
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "g"){
          ledcWrite(2, server.arg(i).toInt());
          gv = server.arg(i).toInt();
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "b"){
          ledcWrite(3, server.arg(i).toInt());
          bv = server.arg(i).toInt();
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "ww"){
          ledcWrite(4, server.arg(i).toInt());
          wwv = server.arg(i).toInt();
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "cw"){
          ledcWrite(5, server.arg(i).toInt());
          cwv = server.arg(i).toInt();
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "ontime"){
          ontime = server.arg(i).toInt();
          strobo = true;
          Serial.println(server.argName(i) + server.arg(i));
        }
        else if (server.argName(i) == "offtime"){
          offtime = server.arg(i).toInt();
          strobo = true;
          Serial.println(server.argName(i) + server.arg(i));
        }
      }    
    if (rv == 0 && gv == 0 && bv == 0 && wwv == 0 && cwv == 0){
      strobo = false;
    }
  }
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}

String mainPage(){
  String ptr = "";
  ptr += "<html>\n";
  ptr += "  <head>\n";
  ptr += "<meta http-equiv=\"content-type\" content=\"text/html; charset=windows-1252\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr += "    <title>Led controller</title>\n";
  ptr += "    <style>\n";
  ptr += "      body {\n";
  ptr += "        background-color: #181818;\n";
  ptr += "        font-family: Roboto;\n";
  ptr += "        Color: #ffffff;\n";
  ptr += "        width: 100%;\n";
  ptr += "        }\n";
  ptr += "      #container{\n";
  ptr += "          margin: auto;\n";
  ptr += "          width: fit-content;\n";
  ptr += "          height: 500px;\n";
  ptr += "          background-color: #2b2b2b;\n";
  ptr += "          border-radius: 10px;\n";
  ptr += "          padding: 20px;\n";
  ptr += "      }\n";
  ptr += "      form{\n";
  ptr += "        display: flex;\n";
  ptr += "        flex-direction: column;\n";
  ptr += "        justify-content: space-evenly;\n";
  ptr += "        height: 400px;\n";
  ptr += "      }\n";
  ptr += "      .value{\n";
  ptr += "        width: 75px;\n";
  ptr += "        float: left;\n";
  ptr += "        padding: 5px;\n";
  ptr += "        display: flex;\n";
  ptr += "        justify-content: space-evenly;\n";
  ptr += "      }\n";
  ptr += "      h1{\n";
  ptr += "        padding: 5px;\n";
  ptr += "      }\n";
  ptr += "      .flexrow{\n";
  ptr += "        display: flex;\n";
  ptr += "        flex-direction: row;\n";
  ptr += "        justify-content: space-evenly;\n";
  ptr += "      }\n";
  ptr += "      .slider{\n";
  ptr += "        padding: 5px;\n";
  ptr += "        width: 120px;\n";
  ptr += "      }\n";
  ptr += "    </style>\n";
  ptr += "    </head>\n";
  ptr += "  <body>\n";
  ptr += "    <div id=\"container\">\n";
  ptr += "      <h1>Set color values</h1><br>\n";
  ptr += "      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/form/\">\n";
  ptr += "        <div class=\"flexrow\">\n";
  ptr += "            <div id=\"rValue\" class=\"value\">R = 0</div>\n";
  ptr += "            <input name=\"r\" type=\"range\" min=\"0\" max=\"255\" value=\"" + String(rv) + "\" class=\"slider\" id=\"r\">\n";
  ptr += "            <br>\n";
  ptr += "        </div>\n";
  ptr += "        <div class=\"flexrow\">\n";
  ptr += "            <div id=\"gValue\" class=\"value\">G = 0</div>\n";
  ptr += "            <input name=\"g\" type=\"range\" min=\"0\" max=\"255\" value=\"" + String(gv) + "\" class=\"slider\" id=\"g\">\n";
  ptr += "            <br>\n";
  ptr += "        </div>\n";
  ptr += "        <div class=\"flexrow\">\n";
  ptr += "            <div id=\"bValue\" class=\"value\">B = 0</div>\n";
  ptr += "            <input name=\"b\" type=\"range\" min=\"0\" max=\"255\" value=\"" + String(bv) + "\" class=\"slider\" id=\"b\">\n";
  ptr += "            <br>\n";
  ptr += "        </div>\n";
  ptr += "        <div class=\"flexrow\">\n";
  ptr += "            <div id=\"wwValue\" class=\"value\">CW = 255</div>\n";
  ptr += "            <input name=\"ww\" type=\"range\" min=\"0\" max=\"255\" value=\"" + String(wwv) + "\" class=\"slider\" id=\"ww\">\n";
  ptr += "            <br>\n";
  ptr += "        </div>\n";
  ptr += "        <div class=\"flexrow\">\n";
  ptr += "            <div id=\"cwValue\" class=\"value\">WW = 0</div>\n";
  ptr += "            <input name=\"cw\" type=\"range\" min=\"0\" max=\"255\" value=\"" + String(cwv) + "\" class=\"slider\" id=\"cw\">\n";
  ptr += "            <br>\n";
  ptr += "        </div>\n";
  ptr += "        <input type=\"submit\" value=\"Submit\">\n";
  ptr += "      </form>\n";
  ptr += "    </div>\n";
  ptr += "    <script>\n";
  ptr += "      var rslider = document.getElementById(\"r\");\n";
  ptr += "      var routput = document.getElementById(\"rValue\");\n";
  ptr += "      routput.innerHTML = 'R = ' + rslider.value;\n";
  ptr += "      var gslider = document.getElementById(\"g\");\n";
  ptr += "      var goutput = document.getElementById(\"gValue\");\n";
  ptr += "      goutput.innerHTML = 'G = ' + gslider.value;\n";
  ptr += "      var bslider = document.getElementById(\"b\");\n";
  ptr += "      var boutput = document.getElementById(\"bValue\");\n";
  ptr += "      boutput.innerHTML = 'B = ' + bslider.value;\n";
  ptr += "      var wwslider = document.getElementById(\"ww\");\n";
  ptr += "      var wwoutput = document.getElementById(\"wwValue\");\n";
  ptr += "      wwoutput.innerHTML = 'WW = ' + wwslider.value;\n";
  ptr += "      var cwslider = document.getElementById(\"cw\");\n";
  ptr += "      var cwoutput = document.getElementById(\"cwValue\");\n";
  ptr += "      cwoutput.innerHTML = 'CW = ' + cwslider.value;\n";
  ptr += "      rslider.oninput = function() {\n";
  ptr += "        routput.innerHTML = 'R = ' + this.value;\n";
  ptr += "      }\n";
  ptr += "      gslider.oninput = function() {\n";
  ptr += "        goutput.innerHTML = 'G = ' + this.value;\n";
  ptr += "      }\n";
  ptr += "      bslider.oninput = function() {\n";
  ptr += "        boutput.innerHTML = 'B = ' + this.value;\n";
  ptr += "      }\n";
  ptr += "      wwslider.oninput = function() {\n";
  ptr += "        wwoutput.innerHTML = 'WW = ' + this.value;\n";
  ptr += "      }\n";
  ptr += "      cwslider.oninput = function() {\n";
  ptr += "        cwoutput.innerHTML = 'CW = ' + this.value;\n";
  ptr += "      }\n";
  ptr += "    </script>\n";
  ptr += "</body></html>\n";
  return ptr;
}

void handle_NotFound(){
    server.send(404, "text/plain", "Not found");
}

void handle_status(){
  server.send(200, "application/json", status());
}

String status(){
  StaticJsonDocument<200> object;
  JsonObject doc = object.to<JsonObject>(); 
  doc["r"] = rv;
  doc["g"] = gv;
  doc["b"] = bv;
  doc["ww"] = wwv;
  doc["cw"] = cwv;
  doc["ontime"] = ontime;
  doc["offtime"] = offtime;
  doc["strobo"] = strobo;
  serializeJson(object, response);
  return response;
}

void loop() {
  server.handleClient();
  if (strobo){
    ledcWrite(1, rv);
    ledcWrite(2, gv);
    ledcWrite(3, bv);
    ledcWrite(4, wwv);
    ledcWrite(5, cwv);
    delay(ontime);
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
    ledcWrite(4, 0);
    ledcWrite(5, 0);
    delay(offtime);
    Serial.println("Strobo");
  }
}