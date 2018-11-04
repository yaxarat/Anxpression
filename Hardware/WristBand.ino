#include "arduinoFFT.h"

#define SAMPLES 128       //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC

unsigned int sampling_period_us;
unsigned long microseconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

int RR_count = 0;
float RR = 0;

int soundSensor = 1;
float Noise = 0;
float Ambient = 0;
int Loud = 0;

#include <Adafruit_Sensor.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 8
#define DHTTYPE   DHT11
DHT dht(DHTPIN, DHTTYPE);

#define samp_siz 20
#define rise_threshold 5
// Pulse Monitor Test Script
int sensorPin = 0;


void setup() {
  Serial.begin(9600);
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  dht.begin();
}
void loop ()
{
  float reads[samp_siz], sum;
  long int now, ptr;
  float last, reader, start, k;
  float first, second, third, before;
  int heartBeat, humid, temp;
  bool rising;
  int rise_count;
  int n, i;
  long int last_beat;

  for (int i = 0; i < samp_siz; i++)
    reads[i] = 0;
  sum = 0;
  ptr = 0;
  while (1)
  {
    // calculate an average of the sensor
    // during a 20 ms period (this will eliminate
    // the 50 Hz noise caused by electric light
    n = 0;
    start = millis();
    reader = 0.;
    do
    {
      reader += analogRead (sensorPin);
      n++;
      now = millis();
    }
    while (now < start + 20);
    reader /= n;  // we got an average
    // Add the newest measurement to an array
    // and subtract the oldest measurement from the array
    // to maintain a sum of last measurements
    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = (sum / samp_siz) * 50;
    //Serial.println(last);
    //Serial.print('\t');
    humid = dht.readHumidity();
    temp = dht.readTemperature();
    Noise = analogRead(soundSensor);
    //Serial.print(Noise);
    //Serial.print('\n');
    if (Noise > 82) {
      Loud = 1;
    }
    else {
      Loud = 0;
    }
    // now last holds the average of the values in the array
    // check for a rising curve (= a heart beat)
    if (last > before)
    {
      rise_count++;
      if (!rising && rise_count > rise_threshold)
      {
        // Ok, we have detected a rising curve, which implies a heartbeat.
        // Record the time since last beat, keep track of the two previous
        // times (first, second, third) to get a weighed average.
        // The rising flag prevents us from detecting the same rise
        // more than once.
        rising = true;
        first = millis() - last_beat;
        last_beat = millis();
        // Calculate the weighed average of heartbeat rate
        // according to the three last beats
        heartBeat = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
        char BPM [3];
        sprintf(BPM, "%03d", heartBeat);
        //Serial.println(heartBeat);
        //Serial.print('\t');
        third = second;
        second = first;
        //rial.println(humid);
        //rial.println(temp);
        int Result[4] = {heartBeat, humid, temp, Loud};
        Serial.print(BPM);
        Serial.print(humid);
        Serial.print(temp);
        Serial.println(Loud);
        //RR_count++;
        //Serial.println(RR_count);
        //Serial.println(RR);
      }
    }
    else
    {
      // Ok, the curve is falling
      rising = false;
      rise_count = 0;
    }
    /*
        if (RR_count = 10) {
          arduinoFFT FFT = arduinoFFT();
          for (int i = 0; i < SAMPLES; i++) {
            microseconds = micros();    //Overflows after around 70 minutes!
            vReal[i] = last;
            vImag[i] = 0;
            while (micros() < (microseconds + sampling_period_us)) {
            }
          }

          FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
          FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
          FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
          double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
          k = 0;
          for (i = 0; i < SAMPLES; i++) {
            RR = max(vReal[i], k);
            k = RR;
          }
          RR_count = 0;
        }

        else {
          return;
        }
    */
    before = last;
    ptr++;
    ptr %= samp_siz;
  }

}
