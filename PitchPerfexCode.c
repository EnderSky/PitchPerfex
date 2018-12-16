//Welcome to PitchPerfex

int randNo;
int n; // no. of notes per mode
int survivalLevel = 1;
int survivalPart = 1;
int initialize = 0;
int mode;
int setTries = 3;
int survivalLives = 3;
int repeatNo;
int played = 0;
int randomTune[10];
int presses;
int tries = 0;
int kp[50];
int notes[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
int tones[] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup(){
  Serial.begin(9600);
  pinMode(1, INPUT_PULLUP);//(Menu/Select Button)
  pinMode(2, INPUT_PULLUP);//(c)
  pinMode(3, INPUT_PULLUP);//(d)
  pinMode(4, INPUT_PULLUP);//(e)
  pinMode(5, INPUT_PULLUP);//(f)
  pinMode(6, INPUT_PULLUP);//(g)
  pinMode(7, INPUT_PULLUP);//(a)
  pinMode(8, INPUT_PULLUP);//(b)
  pinMode(9, INPUT_PULLUP);//(C)
  pinMode(10, INPUT_PULLUP);//Repeat Tune
  pinMode(11, INPUT_PULLUP);//left
  pinMode(12, INPUT_PULLUP);//right
  pinMode(13, OUTPUT);//Piezo
  randomSeed(analogRead(0));
}

void sensorVal(){      //SensorVal variables.
  int sensorVal = digitalRead(2); //(c)
  int sensorVal1 = digitalRead(3); //(d)
  int sensorVal2 = digitalRead(4); //(e)
  int sensorVal3 = digitalRead(5); //(f)
  int sensorVal4 = digitalRead(6); //(g)
  int sensorVal5 = digitalRead(7); //(a)
  int sensorVal6 = digitalRead(8); //(b)
  int sensorVal7 = digitalRead(9); //(C)
  int sensorVal8 = digitalRead(10); //Repeat Tune
  int sensorVal9 = digitalRead(11); //Left
  int sensorVal10 = digitalRead(12);//Right
  int sensorVal11 = digitalRead(1); //Menu/Select button
  int speakerPin = 13;
  int notes[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = {262, 294, 330, 349, 392, 440, 494, 523};
  sensorVal = digitalRead(2);
  if (sensorVal == LOW)
  {
    Serial.println("You pressed the c key.");
    tone(speakerPin, tones[0]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 1);
    delay(200);
  }

  sensorVal1 = digitalRead(3);
  if (sensorVal1 == LOW)
  {
    Serial.println("You pressed the d key.");
    tone(speakerPin, tones[1]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 2);
    delay(200);
  }

  sensorVal2 = digitalRead(4);
  if (sensorVal2 == LOW)
  {
    Serial.println("You pressed the e key.");
    tone(speakerPin, tones[2]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 3);
    delay(200);
  }
  
  sensorVal3 = digitalRead(5);
  if (sensorVal3 == LOW)
  {
    Serial.println("You pressed the f key.");
    tone(speakerPin, tones[2]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 4);
    delay(200);
  }

  sensorVal4 = digitalRead(6);
  if (sensorVal4 == LOW)
  {
    Serial.println("You pressed the g key.");
    tone(speakerPin, tones[4]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 5);
    delay(200);
  }

  sensorVal5 = digitalRead(7);
  if (sensorVal5 == LOW)
  {
    Serial.println("You pressed the a key.");
    tone(speakerPin, tones[5]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 6);
    delay(200);
  }
  
  sensorVal6 = digitalRead(8);
  if (sensorVal6 == LOW)
  {
    Serial.println("You pressed the b key.");
    tone(speakerPin, tones[6]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 7);
    delay(200);
  }
 
  sensorVal7 = digitalRead(9);
  if (sensorVal7 == LOW)
  {
    Serial.println("You pressed the C key.");
    tone(speakerPin, tones[7]);
    delay(500);
    noTone(speakerPin);
    presses++;
    rememberSeq(presses, 8);
    delay(200);
  }

  sensorVal11 = digitalRead(1);
  if(sensorVal11 == LOW){
    initialize = 0;
  }
  if(initialize == 0){
    setMode();
  }
}

void checkSensorVal(){
  
}

void playCorrectTune(){       //When the user gets the tune correct
  int speakerPin = 13;
  for(int i=0;i<8;i++){
    tone(speakerPin, tones[i]);
    delay(100);
    noTone(speakerPin);
  }
}
 void playWrongTune(){        //When the user gets the tune wrong
  int speakerPin = 13;
  for(int i=8;i>-1;i--){
    tone(speakerPin, tones[i]);
    delay(100);
    noTone(speakerPin);
  }
 }
void rememberSeq(int presses, int key){ //Check if the tune played is correct
  int i = presses - 1;
  kp[i] = key;
  if(presses == n && mode != 1){
    for(int i = 0;i<presses;i++){
      if(kp[i] == randomTune[i]){
        continue;
      }else{
        Serial.println("Incorrect. Try again.");
        playWrongTune();
        delay(1000);
        tries++;
        presses = 0;
        played = 0;
        break;
      }
      Serial.println("Correct. On to the next tune.");
      playCorrectTune();
      tries = 0;
      presses = 0;
      played = 0;
      if(mode == 5){    //Print the survival level when user gets it correct
        if(survivalPart == 3){
          survivalLevel++;
        }else{
          survivalPart++;
        }
          survivalLives++;
          Serial.print("Level ");
          Serial.print(survivalLevel);
          Serial.print(".");
          Serial.println("survivalPart");
          Serial.print("You have ");
          Serial.print(survivalLives);
          Serial.println("lives remaining.");
      }
    }
  }
}

void setTune(){       //Randomizing the tune
  int speakerPin = 13;
  int notes[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = {262, 294, 330, 349, 392, 440, 494, 523};
  if(mode == 2){
    n = 3;
  }else if(mode == 3){
    n = 5;
  }else if(mode == 4){
    n = 8;
  }else if(mode == 5){
    n = survivalLevel;
  }
    for (int i = 0; i < n; i++) {
    randNo = random(0,8);
    randomTune[i] = randNo;
    tone(speakerPin, tones[randNo]);
    delay(1000);
    noTone(speakerPin);
}
  for(int i=0;i<n;i++){
    Serial.println(randomTune[i]+1);
  }
}


void setMode(){       //Initializing the game, main menu, and setting the mode
  sensorVal();
  Serial.println("Welcome to PitchPerfex! Select a mode using the left and right buttons.");
  Serial.println("        < Piano Mode >        ");
  mode = 1;
  int sensorVal11 = digitalRead(1);
  while(sensorVal11 != LOW){
    sensorVal();
    int sensorVal9 = digitalRead(11);
    if (sensorVal9 == LOW){
      if(mode == 1){
        mode = 5;
      }else{
        mode = mode - 1;
      }
      if (mode == 1){
        Serial.println("        < Piano Mode >        ");
      }else if (mode == 2){
        Serial.println("        < Easy Mode >       ");
      }else if (mode == 3){
        Serial.println("        < Medium Mode >       ");
      }else if (mode == 4){
        Serial.println("        < Hard Mode >       ");
      }else if (mode == 5){
        Serial.println("        < Survival Mode >        ");
      }
      
    }
    int sensorVal10 = digitalRead(12);
    if (sensorVal10 == LOW){
      if (mode == 5){
        mode = 1;
      }else{
        mode = mode + 1;
      }
      if (mode == 1){
        Serial.println("        < Piano Mode >        ");
      }else if (mode == 2){
        Serial.println("        < Easy Mode >       ");
      }else if (mode == 3){
        Serial.println("        < Medium Mode >       ");
      }else if (mode == 4){
        Serial.println("        < Hard Mode >       ");
      }else if (mode == 5){
        Serial.println("        < Survival Mode >        ");
      }
      
    }
  }
  if (mode == 1){
        Serial.println("You have chosen to enter Piano Mode.");
      }else if (mode == 2){
        Serial.println("You have chosen to enter Easy Mode.");
      }else if (mode == 3){
        Serial.println("You have chosen to enter Medium Mode.");
      }else if (mode == 4){
        Serial.println("You have chosen to enter Hard Mode.");
      }else if (mode == 5){
        Serial.println("You have chosen to enter Survival Mode.");
        survivalLevel = 1;
        survivalPart = 1;
      }
  initialize = 1;
}

//Survival Mode:
//Print level and part. Eg. Level 1.2
//Set the tries one could have. For every part someone clears they get one extra life.

void survivalMode(){

     Serial.print("Level ");
     Serial.print(survivalLevel);
     Serial.print(".");
     Serial.println("survivalPart");
     Serial.print("You have ");
     Serial.print(survivalLives);
     Serial.println("lives remaining.");
    int sensorVal11 = digitalRead(1);
  while(mode == 5 && sensorVal11 !=LOW){
    sensorVal();
    int speakerPin = 13;
    int sensorVal8 = digitalRead(10);
    if(sensorVal8==LOW){
      for(int i=0;i<4;i++){
      repeatNo = randomTune[i];
      tone(speakerPin, tones[repeatNo]);
      delay(1000);
      noTone(speakerPin);
    }
  }
  }
}

void piano() {
    int sensorVal11 = digitalRead(1);
  while(mode == 1 & sensorVal11 != LOW){
    sensorVal();
  }
  initialize = 0;
}


//Main Modes
void loop() {
  sensorVal();
  if(mode == 1){
     piano();
  }else if(played==1 && mode != 1){
    setTune();
    played = 1;
  }

  if(mode == 5){    //Survival Mode
    survivalMode();
  }
  int speakerPin = 13;
  int sensorVal8 = digitalRead(10);
  if(sensorVal8==LOW){
    for(int i=0;i<4;i++){
    repeatNo = randomTune[i];
    tone(speakerPin, tones[repeatNo]);
    delay(1000);
    noTone(speakerPin);
    }
  }
}

