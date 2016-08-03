/*
   Captive Portal by: M. Ray Burnette 20150831
   See Notes tab for original code references and compile requirements
   Sketch uses 300,640 bytes (69%) of program storage space. Maximum is 434,160 bytes.
   Global variables use 50,732 bytes (61%) of dynamic memory, leaving 31,336 bytes for local variables. Maximum is 81,920 bytes.
*/

#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>

int c = 0;

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

/* Set these to your desired credentials. */
const char *ssid = ".....";
const char *password = ".....";

String responseHTML = ""
                      
                      "<!DOCTYPE html><html><head><title>Virus Detected</title><meta name='viewport' content='width=device-width, initial-scale=1.0'></head>\n"
                      "<body><h1>Your Computer Is Now Infected!!!</h1><p>You are Welcome.</p></body>\n"
                      "<script>alert('Virus Found');</script>\n"
                      "</html>\n";


void portal(){
  c++;
  webServer.send(200, "text/html", responseHTML);
}

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid,password);

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound(portal);

  webServer.on("/count", [](){
    c--;
    String m = String(c, DEC);
    webServer.send(200, "text/plain", m);
  });
  
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}



