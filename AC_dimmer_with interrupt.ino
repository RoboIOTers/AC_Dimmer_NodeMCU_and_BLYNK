

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "Your auth token";        // You should get Auth Token in the Blynk App.
                                        // Go to the Project Settings (nut icon) in the Blynk app or check your email for auth token.

char ssid[] = "Your wifi SSID";         // Your WiFi credentials.
char pass[] = "Your wifi password";    // Set password to "" for open networks.

volatile byte LOAD = 4;    // Output to Optocoupler Triac pin controlling the AC load  (D2 pin in NodeMCU means GPIO04 pin)
                            // you can choose your pin of choice from any GPIO pin in NodeMCU
volatile int dimming = 128;  // Dimming level (0-128)  0 = ON, 100 = OFF
volatile byte ZVC=12 ;     // INPUT PIN for the Zero Voltage Cross Signal d6 means GPIO12
int Slider_Value = 0;

BLYNK_WRITE(V1)   // function to assign value to variable Slider_Value whenever slider changes position
{
  Slider_Value = param.asInt(); // assigning incoming value from pin V1 to a variable 
}

void zero_crosss_int()  //function to be fired at the zero crossing to dim the light
{
                      // Firing angle calculation : 1 full 50Hz wave =1/50=20ms 
                      // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) 
                      // For 60Hz => 8.33ms (10.000/120)// 10ms=10000us  
                      // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65
  
  volatile int dimtime = (75*dimming);    // For 60Hz = 65    
  delayMicroseconds(dimtime);    // Wait till firing the TRIAC    
  digitalWrite(LOAD, HIGH);   // Fire the TRIAC
  delayMicroseconds(10);         // triac On propogation delay 
         // (for 60Hz use 8.33) Some Triacs need a longer period
  digitalWrite(LOAD, LOW);    // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIAC
  
}
ICACHE_RAM_ATTR void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(LOAD, OUTPUT);// Set AC Load pin as output
  attachInterrupt(digitalPinToInterrupt(ZVC), zero_crosss_int, RISING);  // Choose the zero cross interrupt pin from any GPIO pin of NodeMCU
}
void loop() 
{
  Blynk.run();
  dimming=map(Slider_Value, 0, 100, 128, 8);   // at lower values than 8 , flickering may start at 100% so keeping it 8 for avoiding flickering
    delay(10);
    //Serial.println(Slider_Value); 
  
}
