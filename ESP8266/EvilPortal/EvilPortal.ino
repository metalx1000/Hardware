/*
   Original code by Captive Portal by: M. Ray Burnette 20150831
   See Notes tab for original code references and compile requirements

   This is a work in progress.
   This is just meant to be a joke to scare people
   I hope to add SDcard support in the future
*/

#include <ESP8266WiFi.h>
#include "./DNSServer.h"                  // Patched lib
#include <ESP8266WebServer.h>

int c = 0;

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>Virus Detected</title></head><body>"
                      "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                      "<h1>Your Device Is Now Infected</h1>"
                      "<p>You are Welcome.</p>"
                      "</body></html>";

void portal(){
  c++;
  webServer.send(200, "text/html", responseHTML);
}

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("Evil Portal");

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



