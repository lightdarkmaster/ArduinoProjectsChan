//library here
#include <DHT.h>
#include <Servo.h>
Servo myservoWindow;
//declare pins of the following sensors
const int fan = 4; //fan pin to pin 4
const int humiditySensor = 2; //Dht22 to pin 2
const int rainSensor = A1; //rainsensor to A1
const int servoMotor = 12;//Servo motor to pin 12
const int pump = A7; //pump to pin 7
const int photoresistor = A0; //photoresistor to A0
#define DHTTYPE DHT22   // DHT 11 or DHT 22
DHT dht(humiditySensor, DHTTYPE);

//initial value of the following data
int temperatureVal;
int humidityVal;
int photoVal;
int rainVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(fan, OUTPUT);
  pinMode(humiditySensor, INPUT);
  pinMode(rainSensor, INPUT);
  pinMode(servoMotor, 12);
  pinMode(pump, OUTPUT);
  pinMode(photoVal, INPUT);
  myservoWindow.attach(9);

  Serial.begin(9600);

  dht.begin();

  //digitalWrite(pump, HIGH);
  //delay(10000);
 //digitalWrite(pump, LOW);
}

void loop() {

readRainsensor();
readDHT();
//if dire nauran {readDHT} else{rainsensor}

}

void readRainsensor(){
  rainVal = analogRead(rainSensor);  // Read the sensor value
  Serial.print("Sensor value: ");
  Serial.println(rainVal);

  if (rainVal < 500) {  // If the sensor value is less than 500, it's raining
    Serial.println("It's raining!");
  }else{
    Serial.println("Not Raining");
  }
  delay(500);              // Delay for 500ms before taking another reading
}

void readDHT(){
    delay(10);  // Wait 2 seconds between measurements
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(temperature >= 15){
    digitalWrite(fan, HIGH);
    myservoWindow.write(180);
  }else{
    digitalWrite(fan, LOW);
    myservoWindow.write(90);
  }

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}

