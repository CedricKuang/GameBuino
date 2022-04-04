#define VRX A0
#define VRY A1
#define SW 2
#define UP_THRESHOLD 900
#define DOWN_THRESHOLD 100
#define RIGHT_THRESHOLD 900
#define LEFT_THRESHOLD 100

float vrx_value = 0;
float vry_value = 0;
int sw_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(VRX, INPUT);
  pinMode(VRY, INPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  vrx_value = analogRead(VRX);
  vry_value = analogRead(VRY);
  sw_value = digitalRead(SW);

  Serial.print("X: ");
  Serial.print(vrx_value);
  Serial.print("\t");
  Serial.print("Y: ");
  Serial.print(vry_value);
  Serial.print("\t"); 
  Serial.print("SW: ");
  Serial.println(sw_value); 
  
  if(vrx_value > UP_THRESHOLD)
    Serial.println("UP");
  if(vrx_value < DOWN_THRESHOLD)
    Serial.println("DOWN");
  if(vry_value > RIGHT_THRESHOLD)
    Serial.println("RIGHT");
  if(vry_value < LEFT_THRESHOLD)
    Serial.println("LEFT");
  if(sw_value == 0)
    Serial.println("BUTTON PRESSED"); 
}
