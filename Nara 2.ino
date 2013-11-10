
  //-------------------------------------------------------// 
  #include <AFMotor.h> //Adafruit motor header library: http://www.adafruit.com/products/81

//Motor Layout (Wiring specific)
  AF_DCMotor motorFL(4, MOTOR12_64KHZ);
  AF_DCMotor motorBL(1, MOTOR12_64KHZ); 
  AF_DCMotor motorFR(2, MOTOR12_64KHZ);  
  AF_DCMotor motorBR(3, MOTOR12_64KHZ);

  char rcvDirection = 0; // Forward (F), Backward(B), Neutral steer(N)
  int rcvSpeedL = 0; //0-128?
  int rcvSpeedR = 0;
  bool validCmd = False;
 
 //-------------------------------------------------------// 
void  setup(){
  //Starts the serial connection
  Serial.begin(9600);
  Serial.write("Hello Dave.");
}
//-------------------------------------------------------// 
void loop(){ 
  //Reads the incoming command.
  ReadIncoming();
  //Executes the command. Fetch boy, fetch!
  ExecuteCommands();

}
//-------------------------------------------------------// 
void ReadIncoming(){
  if (Serial.available()) {
    
  }
  while(validCmd == false) {
  //Read the incoming command, 1 byte, into memory to use as a command.
 rcvDirection = Serial.read();
 rcvSpeedL = Serial.read();
 rcvSpeedR = Serial.read();

 if (rcvDirection == 'F' || 'B' || 'n'){
  if (rcvSpeedL >= 0 && rcvSpeedL <= 128){
    if rcvSpeedR >= 0 && rcvSpeedR <= 128) {
        validCmd = True ;
       }
     }
    }
  }

}
//-------------------------------------------------------// 
void ExecuteCommands(){
  
  //Translate the command into a direction. F/B: Fwd/reverse, L/R: Left, Right, l/r: reverse turn.
  switch(rcvDirection){
    //Checks the first byte recieved for the direction to start: Forward, Backward or Neutral steer.
    case 'F':
    // Reply with the direction intended to go
      Serial.println("GOING STRAIGHT AT:");
      Serial.println(rcvSpeedL, rcvspeedR);
      //Start moving with forward intent.
      GoForward(rcvSpeedL, rcvSpeedR);
      break;
    case 'B':
    //Reply with the direction to go
      Serial.println("GOING BACKWARDS AT:");
      Serial.println(rcvSpeedL, rcvSpeedR);
      //Start moving with backwards intent.
      GoBackwards(rcvSpeedL, rcvSpeedR);
      break;
    case 'N':
    // Dat neutral steer.
      Serial.println("NEUTRAL JUST KICKED IN YO")
      NeutralSteer(rcvSpeedL, rcvSpeedR);
      break;
  }
}
//-------------------------------------------------------// 
//Set motor driver to appropriate fwd speeds.
void GoForward(int FSpeed){
  //seperates stop and go command.  Min/Max motor speeds here.
  if(FSpeed > 0 && FSpeed < 10){
    motorL.setSpeed(FSpeed*20);
    motorR.setSpeed(FSpeed*20);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  else if(FSpeed == 0){
    //STOP.
    motorL.setSpeed(0);
    motorR.setSpeed(0);
  }
}
//-------------------------------------------------------// 
void GoBackwards(int FSpeedB){
  //Same as fwd, except reverse.
  if(FSpeedB > 0 && FSpeedB < 10){
    motorL.setSpeed(FSpeedB*20);
    motorR.setSpeed(FSpeedB*20);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
  }
  else if(FSpeedB == 0){
    //STOP.
    motorL.setSpeed(0);
    motorR.setSpeed(0);
  }
}
//-------------------------------------------------------// 
void TurnLeftF(int FSpeedM,int FSpeedB){
  //Left turn by reducing the left motor speed
  if (FSpeedB < 10 && FSpeedB > 0 && FSpeedM < 10 && FSpeedM > 0){
    motorL.setSpeed((FSpeedB*(20-(FSpeedM*2) )));
    motorR.setSpeed(FSpeedB*20);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  //Neutral turn
  else if(FSpeedB == 0 && FSpeedM > 0 && FSpeedM < 10){
    motorL.setSpeed(FSpeedM*20);
    motorR.setSpeed(FSpeedM*20);
    motorL.run(BACKWARD);;
    motorR.run(FORWARD);
  }
}
//-------------------------------------------------------// 
void TurnRightF(int FSpeedM,int FSpeedB){
  //Right turn by reducing Right motors.
  if (FSpeedB < 10 && FSpeedB > 0 && FSpeedM < 10 && FSpeedM > 0){
    motorR.setSpeed((FSpeedB*(20-(FSpeedM*2) )));
    motorL.setSpeed(FSpeedB*20);
    motorL.run(FORWARD);
    motorR.run(FORWARD);
  }
  //Neutral steer right
  else if(FSpeedB == 0 && FSpeedM > 0 && FSpeedM < 10){
    motorL.setSpeed(FSpeedM*20);
    motorR.setSpeed(FSpeedM*20);
    motorR.run(BACKWARD);;
    motorL.run(FORWARD);
  }
}
//-------------------------------------------------------// 
void TurnLeftB(int FSpeedM,int FSpeedB){
  //Turns left while in reverse
  if (FSpeedB < 10 && FSpeedB > 0 && FSpeedM < 10 && FSpeedM > 0){
    motorL.setSpeed((FSpeedB*(20-(FSpeedM*2) )));
    motorR.setSpeed(FSpeedB*20);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
  }
}
//-------------------------------------------------------// 
void TurnRightB(int FSpeedM,int FSpeedB){
  //Turn right while in reverse
  if (FSpeedB < 10 && FSpeedB > 0 && FSpeedM < 10 && FSpeedM > 0){
    motorR.setSpeed((FSpeedB*(20-(FSpeedM*2) )));
    motorL.setSpeed(FSpeedB*20);
    motorL.run(BACKWARD);
    motorR.run(BACKWARD);
  }
}
