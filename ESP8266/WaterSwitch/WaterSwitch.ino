/**
 * ESP delay singal for water pump
 *
 *  Created by Kris Occhipinti
 *  http://filmsbykris.com
 *  GPLv3 License https://www.gnu.org/licenses/gpl-3.0.txt
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

//access point and passphrase
char ap[] = "<AP>";
char pass[] = "<PASSPHRASE>";

//urls
char url1[] = "http://URL/1.php";
char url2[] = "http://URL/2.php";

//delays
int d = 1000;
int d1 = 300000;
int d2 = 60000;

//connection number
int c = 0;

void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP(ap, pass);
    
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS

        if( c == 0 ){
          c++;
          http.begin(url1); //HTTP
          d=d1;
        }else{
          http.begin(url2); //HTTP
          d=d2;
        }

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();

        //delay based on connection number
        delay(d);
    }else{
      //if not connected wait 1 second and try again
      delay(d);
    }
}





