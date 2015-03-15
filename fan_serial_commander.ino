//
// AUTHOR: Sky (TechnologyCatalyst)
//
// PURPOSE: control pwm fan speeds using serial interface while
//          the fans are mounted in the PC for fine tuning of each
//          individual fan's optimal speed for each fan mode
//
// INSTRUCTIONS: just power the arduino up with this sketch, then open serial console,
//               then send it commands to control the fan speeds.  type "front", "rear",
//               or "radiator" without the quotes to choose which set of fans to control,
//               and press enter to send the command.  once you choose which fans to control,
//               now you can send it fan speeds.  0 is off, and 255 is max.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// variable declarations
int fanSpeed = 0;
String command;
char werd;
int currentFan = 0;
int rear = 3;
int rearSpeed = 0;
int front_a = 5;
int front_b = 6;
int frontSpeed = 0;
int radiator_a = 9;
int radiator_b = 10;
int radiatorSpeed = 0;
int commandCheck;
String rearMarker = "   ";
String frontMarker = "-> ";
String radiatorMarker = "   ";

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(4, INPUT);

  // fans
  pinMode(3, OUTPUT);//rear 120mm
  pinMode(5, OUTPUT);//front 140mm
  pinMode(6, OUTPUT);//front 140mm
  pinMode(9, OUTPUT);//radiator 140mm
  pinMode(10, OUTPUT);//radiator 140mm
  pinMode(11, OUTPUT);// unused, maybe to PWM led ring?
  analogWrite(3,0);analogWrite(5,0);analogWrite(6,0);
  analogWrite(9,0);analogWrite(10,0);analogWrite(11,0);
  Serial.begin(9600);
  Serial.println();
}

void loop(){
  // this is what reads your serial commands
  while ( Serial.available() > 0 ) {
    // small delay because it can only deliver the bytes so quickly
    delay(5);
    // you have to read one byte (one character) at a time
    werd = Serial.read();
    // append the character to our "command" string
    command += werd;
  }
  // clear serial so it's ready for your next command
  Serial.flush();
  if ( command.length() > 0 ) {
    commandCheck = 0;
    if ( command == "front" ) {
        currentFan = 0;
        rearMarker = "   ";
        frontMarker = "-> ";
        radiatorMarker = "   ";
    } else if ( command == "rear" ) {
        currentFan = 1;
        rearMarker = "-> ";
        frontMarker = "   ";
        radiatorMarker = "   ";
    } else if ( command == "radiator" ) {
        currentFan = 2;
        rearMarker = "   ";
        frontMarker = "   ";
        radiatorMarker = "-> ";
    } else {
        // flag so we know it wasn't a change fan command
        commandCheck = 1;
    }
    if ( commandCheck == 1 ) {
      // the ".toInt()" appended to the command variable is to convert
      // the user entered "command" from a string into an integer so
      // that we can use it to set the pin's PWM pulse width
      // (it'll error if you send an integer in string format)
      if ( currentFan == 0 ) {
        //front
        analogWrite(front_a, command.toInt());
        analogWrite(front_b, command.toInt());
        frontSpeed = command.toInt();
      } else if ( currentFan == 1 ) {
        //rear
        analogWrite(rear, command.toInt());
        rearSpeed = command.toInt();
      } else if ( currentFan == 2 ) {
        //radiator
        analogWrite(radiator_a, command.toInt());
        analogWrite(radiator_b, command.toInt());
        radiatorSpeed = command.toInt();
      } else {
        //unknown command
      }
    }
    command = "";
    Serial.print(frontMarker);
    Serial.print("Front: ");
    Serial.println(frontSpeed);
    Serial.print(rearMarker);
    Serial.print("Rear: ");
    Serial.println(rearSpeed);
    Serial.print(radiatorMarker);
    Serial.print("Radiator: ");
    Serial.println(radiatorSpeed);
    // this function (below) is just to print a ton of empty lines so that the UI "appears" to be refreshing like a screen.
    // you'll have to set your serial monitor to a certain width to get that effect to work correctly, of course
    clear();
  }
}

void clear() {
  Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();
  Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();
  Serial.println();Serial.println();Serial.println();Serial.println();Serial.println();
}
