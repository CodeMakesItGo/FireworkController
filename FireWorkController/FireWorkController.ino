#include <FastLED.h>

//Defines for hardware setup
#define LED_PIN     5
#define START_PIN   7
#define NUM_LEDS    50
#define BRIGHTNESS  128
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

//Defines for application
#define UPDATES_PER_SECOND 10     //10Hz
#define DISABLED -1
#define STAY_ON_DURATION_MS 1000  //one second

//Global Variables
CRGB leds[NUM_LEDS];
long int timer = 0;  //The timer used to play the show

//Set the time in 100ms increments, this time is when you want the firework to ignite
//Would recommend to not have more than 2 on at the same time separated by at least 200ms
//DISABLE any lights that are not used or not working
long int igniteTime[NUM_LEDS] = 
{
   DISABLED,  //Status LED 1, always disabled because not part of the show
   5000, //LED 2
   10000, //LED 3
   15000, //LED 4
   20000, //LED 5
   25000, //LED 6
   30000, //LED 7
   31000, //LED 8
   32000, //LED 9
   33000, //LED 10
   34000, //LED 11
   40000, //LED 12
   44500, //LED 13
   42000, //LED 14
   44000, //LED 15
   38000, //LED 16
   50000, //LED 17
   51000, //LED 18
   49500, //LED 19
   50500, //LED 20
   49000, //LED 21
   57000, //LED 22
   65000, //LED 23
   56500, //LED 24
   61000, //LED 25
   56000, //LED 26
   81000, //LED 27
   73000, //LED 28
   69000, //LED 29
   77000, //LED 30
   85000, //LED 31
   89000, //LED 32
   91000, //LED 33
   93000, //LED 34
   95000, //LED 35
   97000, //LED 36
   101000, //LED 37
   101100, //LED 38
   101200, //LED 39
   101300, //LED 40
   101400, //LED 41
   105400, //LED 42
   105000, //LED 43
   105200, //LED 44
   102000, //LED 45
   23000, //LED 46
   24000, //LED 47
   54000, //LED 48
   54500, //LED 49
   82000  //LED 50
};

void allOff()
{
  //Turn off all LEDs
  for( int i = 0; i < NUM_LEDS; i++) 
  {
      leds[i] = CRGB::Black;
  }
}

void setup() 
{
  allOff();

  delay( 3000 ); // power-up safety delay

  pinMode(START_PIN, INPUT);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
}

void playShow()
{
  for( int i = 0; i < NUM_LEDS; i++) 
  {
    leds[i] = CRGB::Black;  //Default to off
    
    if( igniteTime[i] != DISABLED &&
        timer >= igniteTime[i] && 
        timer < (igniteTime[i] + STAY_ON_DURATION_MS) )
    {
       leds[i] = CRGB::White;
    }
  }
}

void loop()
{
  static const int interval = 1000 / UPDATES_PER_SECOND;

  if(digitalRead(START_PIN) == HIGH)
  {
    timer += interval;
    playShow();
    leds[0] = CRGB::Green; //Status LED, actually red
  }
  else
  {
    allOff();
    leds[0] = CRGB::Red; //Status LED, actually green
    timer = 0;  //Keep timer at 0 unless the show has started
  }
        
  FastLED.show();
  FastLED.delay(interval);
}
