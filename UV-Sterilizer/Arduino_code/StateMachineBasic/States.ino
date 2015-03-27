int LapFlag = 0;
int counter = 0;

void states() {
    state_0();    // MAIN MENU
    
    state_1();    // 10^(-3)
    state_2();    // 10^(-6)
    state_3();    // uSWITCH CONTROL
    state_4();    // TURN/REMOVE

}

void state_0() {

  static char Menu_labels[][13] = {"SAL 10^-3", "SAL 10^-6"};
  if (State == 0) {
  value += encoder->getValue();                

  // Print menu entries
  lcd.setCursor(1, 1);  //Position of menu labels
  lcd.print(Menu_labels[0]);
  lcd.setCursor(1, 2);
  lcd.print(Menu_labels[1]);
  //Cursor position: not to make the cursor point to empty lines
  if (value > 2) { value = 2; }
  if (value < 1) { value = 1; }
  if (value != last) { last = value; }
  //Controls cursor position: to make the cursor point to the chices values
  switch (value) {
    
    case 1:
    lcd.setCursor(0,2);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print(">");
    break;
    
    case 2:
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(0,2);
    lcd.print(">");
    break;
  }
  ClickEncoder::Button b = encoder->getButton(); //Controls click encoder
  if (b != ClickEncoder::Open) {
    Serial.print("Button: ");
    #define VERBOSECASE(label) case label: Serial.println(#label); break;
    switch (b) {
      VERBOSECASE(ClickEncoder::Pressed);
      VERBOSECASE(ClickEncoder::Held)
      VERBOSECASE(ClickEncoder::Released)
			  
      // ENCODER CLICKED
      case ClickEncoder::Clicked:
      Serial.println("ClickEncoder::Clicked");
      tone(BUZZER, 4000,50);
      switch (value) {  //Depending on 'value' variable, by clicking you go to
        case 1: State = 1;  //State 1 or State 2
        lcd.clear();
        break;
        
        case 2: State = 2;
        lcd.clear();
        break;
      }  
      
      break;
    }
  }
}
}




// STATE 1: 10^(-3)
void state_1() {
  if (State == 1) {
    timer -= encoder->getValue();
    counter = 900; // 15 minutes in seconds
    LapFlag = 0;
    lcd.setCursor(1, 0);
    lcd.print("E-Time = 15 min");
    lcd.setCursor(1, 2);
    lcd.print("Press to confirm");
    
    ClickEncoder::Button b = encoder->getButton();
    if (b != ClickEncoder::Open) {
      Serial.print("Button: ");
      #define VERBOSECASE(label) case label: Serial.println(#label); break;
      switch (b) {
        VERBOSECASE(ClickEncoder::Pressed);
        VERBOSECASE(ClickEncoder::Held)
        VERBOSECASE(ClickEncoder::Released)
        // ENCODER CLICKED
        case ClickEncoder::Clicked:
        Serial.println("ClickEncoder::Clicked");
        tone(BUZZER, 4000,50);
        State = 3;
        lcd.clear();
        break;
      }
    }
  }    
}


//10^(-6)
void state_2() {
  if (State == 2) {
    counter = 1800; // 30 minutes in seconds
    LapFlag = 0;
    lcd.setCursor(1, 0);
    lcd.print("E-Time = 30 min");
    lcd.setCursor(1, 2);
    lcd.print("Press to confirm");
 
     ClickEncoder::Button b = encoder->getButton();
     if (b != ClickEncoder::Open) {
       Serial.print("Button: ");
       #define VERBOSECASE(label) case label: Serial.println(#label); break;
       
       switch (b) {
         VERBOSECASE(ClickEncoder::Pressed);
         VERBOSECASE(ClickEncoder::Held)
         VERBOSECASE(ClickEncoder::Released)
// ENCODER CLICKED
	case ClickEncoder::Clicked:
	  Serial.println("ClickEncoder::Clicked");
	  tone(BUZZER, 4000,50);
          State = 3;
          lcd.clear();
        break;
        break;
      }
    }
  }
}



// STATE 3: uSWITCH CONTROL
void state_3() {
  if (State == 3) {
    int val = 0;
    int inPin = 3;
    int inPin2 = 8;
    val = digitalRead(inPin);
//    Serial.print(val);
    if (val == HIGH) {
      lcd.clear();
      lcd.setCursor(4, 1);
      lcd.print("Let's start!");
      delay(2000);
      int c = 0;      
      digitalWrite(inPin2, HIGH);
      while (c != counter && digitalRead(inPin) == HIGH) {
        c++;
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Remaining: ");
        lcd.setCursor(12, 1);
        lcd.print(counter - c);
        lcd.setCursor(16, 1);
        lcd.print("s");
        Serial.print(inPin);
        Serial.print(c);
        delay(1000);
        //Serial.print(c);
      }
      if (c == counter) { //controls if while loop was stopped by the uSwitch
        digitalWrite(inPin2, LOW);
        State = 4;
      }
      else {
        lcd.clear();
        lcd.setCursor(3, 1);
        lcd.print("Close the door!");
        delay(1000);
        state_3();
      }      
    }
    else {
        lcd.clear();
        lcd.setCursor(3, 1);
        lcd.print("Close the door!");
        delay(1000);       
    }
  } 
}


// STATE 4: TURN/REMOVE
void state_4() {
  if (State == 4) {
    if (LapFlag == 0) {
//      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("Turn the object     press the button!" );
//      lcd.setCursor(1, 2);
//      lcd.print("press the button");
      
      ClickEncoder::Button b = encoder->getButton();
		  
      if (b != ClickEncoder::Open) {
	Serial.print("Button: ");
	#define VERBOSECASE(label) case label: Serial.println(#label); break;
	switch (b) {
	  VERBOSECASE(ClickEncoder::Pressed);
	  VERBOSECASE(ClickEncoder::Held)
	  VERBOSECASE(ClickEncoder::Released)
          
          // ENCODER CLICKED
	  case ClickEncoder::Clicked:
	    Serial.println("ClickEncoder::Clicked");
	    tone(BUZZER, 4000,50);
            LapFlag = 1;
            State = 3;
            lcd.clear();
          break;
         }
       }
     }
     else {
      lcd.clear();
      lcd.setCursor(1, 1);
      lcd.print("Remove the object");
      delay(10000);
      lcd.clear();
      State = 0;
     }
  }
}
