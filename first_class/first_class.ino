class US_Sensor{

  public: 
    US_Sensor(int trig_pin, int echo_pin)
    : echo_pin_(echo_pin), trig_pin_(trig_pin), cm_(0), inches_(0), MAX_DISTANCE(200)
    {
      pinMode(trig_pin, OUTPUT);
      pinMode(echo_pin, INPUT);
    }

    ~US_Sensor(){};

    int get_distance_cm(){
      // convert the time into a distance
      cm_ = microsecondsToCentimeters(ping_microsec());
      if( 0 == cm_ ) {
        cm_ = MAX_DISTANCE;  
      }
      return cm_;
    }

    int get_distance_inches(){
      // convert the time into a distance
      inches_ = microsecondsToInches(ping_microsec());
      return inches_;
    }

  private:
    int echo_pin_;
    int trig_pin_;

    int cm_;
    int inches_;
    const int MAX_DISTANCE;

    long ping_microsec() {
      // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
      // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
      digitalWrite(trig_pin_, LOW);
      delayMicroseconds(2);
      digitalWrite(trig_pin_, HIGH);
      delayMicroseconds(5);
      digitalWrite(trig_pin_, LOW);
    
      // The same pin is used to read the signal from the PING))): a HIGH pulse
      // whose duration is the time (in microseconds) from the sending of the ping
      // to the reception of its echo off of an object.
      return pulseIn(echo_pin_, HIGH);
    }

    int microsecondsToInches(long microseconds) {
      // According to Parallax's datasheet for the PING))), there are 73.746
      // microseconds per inch (i.e. sound travels at 1130 feet per second).
      // This gives the distance travelled by the ping, outbound and return,
      // so we divide by 2 to get the distance of the obstacle.
      // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
      return microseconds / 74 / 2;
    }

    int microsecondsToCentimeters(long microseconds) {
      // The speed of sound is 340 m/s or 29 microseconds per centimeter.
      // The ping travels out and back, so to find the distance of the object we
      // take half of the distance travelled.
      return microseconds / 29 / 2;
    }

};

US_Sensor front_sensor(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  Serial.print(front_sensor.get_distance_cm());
  Serial.print("cm");
  Serial.println();

  delay(100);
}
