void states() {
    state_0();    // MAIN MENU
    
    state_1();    // TIMER
    state_2();    // PROFILES
    state_3();    // START
    //state_4();    //

}

void state_0() {
    static char Menu_labels[][13] = {"Timer", "Profile", "Start"};

	if (State == 0) {
                value += encoder->getValue();
                
                // Print menu entries
                lcd.setCursor(1, 0);
                lcd.print(Menu_labels[0]);
                lcd.setCursor(1, 1);
                lcd.print(Menu_labels[1]);
                lcd.setCursor(1, 2);
                lcd.print(Menu_labels[2]);
                //lcd.setCursor(1, 3);
                //lcd.print(Menu_labels[3]);
		
		  
		  if (value > 3) { value = 3; }
                  if (value < 0) { value = 0; }
                  if (value != last) { last = value; }

                  switch (value) {
                    case 0:  
                      clear_cursor(); 
                      lcd.setCursor(0,0);
                      lcd.print(">");
                      break;
                    
                    case 1: 
                      clear_cursor();
                      lcd.setCursor(0,1);
                      lcd.print(">");
                      break;
                      
                    case 2: 
                      clear_cursor();
                      lcd.setCursor(0,2);
                      lcd.print(">");
                      break;
                      
                    case 3: 
                      clear_cursor();
                      lcd.setCursor(0,3);
                      lcd.print(">");
                      break;
                    
                  }
                          

		  
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
                                  switch (value) {
                                    case 0: State = 1; lcd.clear();
                                      break;
                                    case 1: State = 2; lcd.clear();
                                      break;
                                    case 2: State = 3; lcd.clear();
                                      break;
                                    case 3: State = 4; lcd.clear();
                                      break;
                                  }  
                                      
				break;
			  
			  // ENCODER DOUBLE CLICKED
			  case ClickEncoder::DoubleClicked:
				  Serial.println("ClickEncoder::DoubleClicked");
				  encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
				  tone(BUZZER, 4000, 150);
				  Serial.print("  Acceleration is ");
				  Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
				break;
		    
		   }
		}
	}
}




// STATE 1: TIMER
void state_1() {

    if (State == 1) {
                timer -= encoder->getValue();
                // Print menu entries
                lcd.setCursor(1, 0);
                lcd.print("Set Timer: ");
                
                
                if (timer > 0){
                  lcd.setCursor(13, 0);
                  lcd.print(timer);
                  lcd.setCursor(18, 0);
                  lcd.print("s");
                }
                
                if (timer < 0) timer = 0;
                
                  if (timer != last) {
                    last = timer;
                    Serial.print("Encoder Value: ");
                    Serial.println(value);
                    lcd.setCursor(13, 0);
                    lcd.print("    ");
                    lcd.setCursor(13, 0);
                    lcd.print(value);
                    lcd.setCursor(18, 0);
                    lcd.print("s");
                  }
                  
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
                                  State = 0;
                                  lcd.clear();
				break;
			  
			  // ENCODER DOUBLE CLICKED
			  case ClickEncoder::DoubleClicked:
				  Serial.println("ClickEncoder::DoubleClicked");
				  encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
				  tone(BUZZER, 4000, 150);
				  Serial.print("  Acceleration is ");
				  Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
				break;
		    
    		           }
		   }
    }
    
}


//PROFILES
void state_2() {
  
static char Profile_Menu_labels[][13] = {"2 minutes", "5 minutes", "10 minutes", "30 minutes"};

	if (State == 2) {
  
              if (subState == 1001)
              { timer = 120;
                State = 0;
                subState = 0;
                tone(BUZZER, 1000, 150);
               }
              else if (subState == 1002)
              {  timer = 300;
                State = 0; 
                subState = 0;
                tone(BUZZER, 1000, 150);
              }
              else if (subState == 1003)
              {  timer = 600;
                State = 0; 
                subState = 0;
                tone(BUZZER, 1000, 150);
              }
              else if (subState == 1004)
              {  timer = 1800;
                State = 0; 
                subState = 0;
                tone(BUZZER, 1000, 150);
              }
              else
              {
                value += encoder->getValue();
                
                // Print menu entries
                lcd.setCursor(1, 0);
                lcd.print(Profile_Menu_labels[0]);
                lcd.setCursor(1, 1);
                lcd.print(Profile_Menu_labels[1]);
                lcd.setCursor(1, 2);
                lcd.print(Profile_Menu_labels[2]);
                lcd.setCursor(1, 3);
                lcd.print(Profile_Menu_labels[3]);
		
		  
		  if (value > 3) { value = 3; }
                  if (value < 0) { value = 0; }
                  if (value != last) { last = value; }

                  switch (value) {
                    case 0:  
                      clear_cursor(); 
                      lcd.setCursor(0,0);
                      lcd.print(">");
                      break;
                    
                    case 1: 
                      clear_cursor();
                      lcd.setCursor(0,1);
                      lcd.print(">");
                      break;
                      
                    case 2: 
                      clear_cursor();
                      lcd.setCursor(0,2);
                      lcd.print(">");
                      break;
                      
                    case 3: 
                      clear_cursor();
                      lcd.setCursor(0,3);
                      lcd.print(">");
                      break;
                    
                  }
                          

		  
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
                                  switch (value) {
                                    case 0: State = 2 ; subState = 1001; lcd.clear(); delay(500);
                                      break;
                                    case 1: State = 2 ; subState = 1002; lcd.clear(); delay(500); 
                                      break;
                                    case 2: State = 2 ; subState = 1003; lcd.clear(); delay(500); 
                                      break;
                                    case 3: State = 2 ; subState = 1004; lcd.clear(); delay(500);
                                      break;
                                  }  
                                      
				break;
			  
			  // ENCODER DOUBLE CLICKED
			  case ClickEncoder::DoubleClicked:
				  Serial.println("ClickEncoder::DoubleClicked");
				  encoder->setAccelerationEnabled(!encoder->getAccelerationEnabled());
				  tone(BUZZER, 4000, 150);
				  Serial.print("  Acceleration is ");
				  Serial.println((encoder->getAccelerationEnabled()) ? "enabled" : "disabled");
				break;
		    
		   }
		}
	}
  }
}


// STATE 3: START
void state_3() {
      if (State == 3) {
                
                //startup sequence
                if (subState == 0){  
                  
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Starting in");
                  lcd.setCursor(0, 1);
                  lcd.print("5 seconds...");
                  delay(5000);
                  subState = 1;
                  tone(BUZZER, 5000,50);
                }
                
                //Cycle end
                else if ( subState == 99){
                    timer = 0; 
                    lcd.clear();
                    lcd.setCursor(3, 1);
                    lcd.print("== CYCLE END ==");
                    delay (10);
                    tone(BUZZER, 4000,6);
                    
                    ClickEncoder::Button b = encoder->getButton();
                    if (b != ClickEncoder::Open) {
  			switch (b) {
  			  VERBOSECASE(ClickEncoder::Pressed);
  			  VERBOSECASE(ClickEncoder::Held)
  			  VERBOSECASE(ClickEncoder::Released)
  			  
  			  // ENCODER CLICKED
  			   case ClickEncoder::Clicked:
  				  Serial.println("ClickEncoder::Clicked");
  				  tone(BUZZER, 4000,500);
                                    timer = 0;
                                    State = 0;
                                    subState = 0;
                                    digitalWrite (POWER, LOW);
                                    lcd.clear();
  				break;
      		           }
  		   }
                    
                }
                //COUNTDOWN
                else {
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Count down timer: ");
                  lcd.setCursor(18,0);
                  lcd.print ("       ");
                  lcd.setCursor(18,0);
                  lcd.print (timer);                
                  if (timer <= 0 ) { subState = 99; digitalWrite (POWER, LOW);}
                  else {
                    timer = timer - 1;
                    digitalWrite (POWER, HIGH); 
                    ClickEncoder::Button b = encoder->getButton();
  		  
                  // IF CLICK WHEN RUNNING = STOP/PAUSE 
                  if (b != ClickEncoder::Open) {
  			switch (b) {
  			  VERBOSECASE(ClickEncoder::Pressed);
  			  VERBOSECASE(ClickEncoder::Held)
  			  VERBOSECASE(ClickEncoder::Released)
  			  
  			  // ENCODER CLICKED
  			   case ClickEncoder::Clicked:
  				  Serial.println("ClickEncoder::Clicked");
  				  tone(BUZZER, 4000,500);
                                    State = 0;
                                    digitalWrite (POWER, LOW);
                                    lcd.clear();
  				break;
      		           }
  		   }
  
                   delay(1000);
                  }
                }
      }
}


// Clear the menu cursors
void clear_cursor(){
   lcd.setCursor(0,0); lcd.print(" ");
   lcd.setCursor(0,1); lcd.print(" ");
   lcd.setCursor(0,2); lcd.print(" ");
   lcd.setCursor(0,3); lcd.print(" ");
}
