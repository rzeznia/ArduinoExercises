void setup() {
pinMode (13, OUTPUT);

}

void loop() {
  digitalWrite(13, HIGH); //właczenie diody
  delay (1000); // opoznienie
  digitalWrite(13, LOW); 
  delay (1000); 
}
