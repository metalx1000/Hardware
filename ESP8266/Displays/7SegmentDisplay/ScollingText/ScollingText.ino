#include <HC4LED.h>

#define DISP_DATA_PIN 5
#define DISP_CLOCK_PIN 4
#define DISP_BLANK_PIN 2

HC4LED disp(DISP_CLOCK_PIN, DISP_DATA_PIN, DISP_BLANK_PIN, true);

void setup()
{
  // Why do you think I don't say "hello world" here? :)
  disp.scroll_text("hello happy place    ", 1000);
  disp.scroll_text("0123456789-'    ", 2000);
  disp.display_text("hi", 1000);
  disp.set_upside_down(false);
  disp.display_text("hi", 1000);
  disp.set_upside_down(true);
}

void loop()
{
  // display a count of seconds since the computer started
  disp.display_number((unsigned short)(millis() / 1000));
  delay(1000);
}
