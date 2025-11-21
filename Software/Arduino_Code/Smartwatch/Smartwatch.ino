//IMU
#include "ICM_20948.h"
#include <SPI.h>
#include <math.h>
#define USE_SPI
#define SPI_PORT SPI
#define CS_PIN 2
#define SERIAL_PORT Serial

//Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Vibration
#include "Adafruit_DRV2605.h"

ICM_20948_SPI imu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_DRV2605 drv;

const int N = 10; // amount of samples averaged
float aBuffer[N]; // stores said samples
int bufIndex = 0; // pointer for overwriting

bool firstRun = true; // indicates whether it's the first reading
int stepCount = 0; // this tracks steps
unsigned long lastStepTime = 0; // used for debouncing 
const unsigned long MIN_STEP_INTERVAL = 300; // ms between steps
const float STEP_THRESHOLD = 0.25; // threshold indicating whether a peak is a step

unsigned long lastPrint = 0; // timestamp to avoid flooding serial monitor
unsigned long bumCounter = 0;
unsigned long bumTimer = 0;

void setup() {
  //IMU
  Serial.begin(115200);
  SPI_PORT.begin();
  imu.begin(CS_PIN, SPI_PORT);
  while(!Serial);
    if(imu.begin(CS_PIN, SPI_PORT) != ICM_20948_Stat_Ok){
      Serial.println("IMU init failed! Check wiring/CS pin.");
      while(1);
    }
  Serial.println("IMU ready!");

  //Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  //Vibration
  if (! drv.begin()) {
    Serial.println("Could not find DRV2605");
    while (1) delay(10);
  }
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG); 
}

void loop() {
  if(imu.dataReady()){
    imu.getAGMT(); // reads IMU values

    // acceleration magnitude minus gravity
    float ax = imu.accX() / 1000.0; // convert mg → g
    float ay = imu.accY() / 1000.0;
    float az = imu.accZ() / 1000.0;

    float aMag = sqrt(ax*ax + ay*ay + az*az) - 1.0; // subtract 1g gravity

    // initialize buffer on first run
    if(firstRun){
        for(int i=0;i<N;i++) aBuffer[i] = aMag;
        firstRun = false;
    }

    // update moving average buffer
    aBuffer[bufIndex] = aMag;
    bufIndex = (bufIndex + 1) % N;

    float sum = 0;
    for(int i=0;i<N;i++) sum += aBuffer[i];
    float aSmooth = sum / N;

    // step detection with debounce
    unsigned long now = millis();
    if(aSmooth > STEP_THRESHOLD && (now - lastStepTime > MIN_STEP_INTERVAL)){
        stepCount++;
        lastStepTime = now;
    }

    // print every second
    if(now - lastPrint > 500){
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0,0);
      display.print("Steps: ");
      display.print(stepCount);
      display.display();
      lastPrint = now;
      bumTimer += 500;
        if(bumTimer > 10000 && stepCount == bumCounter){
          drv.setWaveform(0, 14);
          drv.go();
        }
        if(stepCount != bumCounter) {
          bumTimer = 0;
          bumCounter = stepCount;
          drv.stop();
        }
    }
  }
}