
char c;
int count =0;
float temp1,temp2;
void setup() {
 Serial.begin(115200);

}

void loop() {
  if(Serial.available()){
    
      temp1 = 32.52;
      temp2 = 51.65;
      char c = Serial.read();
      if(c == 'c'){
        Serial.println("c++");
      }
      if(c == 'z'){
        Serial.print("s,");
        Serial.print(count);
        Serial.print(",");
        Serial.print(temp1);
        Serial.print(",");
        Serial.print(temp2);
        Serial.println(",e");
       
        count ++;
      }
      
      Serial.flush();
  }
 
  
}
