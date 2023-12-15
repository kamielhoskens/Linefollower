
int led = 13;
bool startprogram = false;
bool stopprogram = false;
int i = 0;


void setup() 
{

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(7, INPUT); //als we pulldownweerstand willen weglaten -> softwarematige INPUT_PULLDOWN
  attachInterrupt(4, ISR_test, RISING); // attachInterrupt(interuptnr van pin 3, Interupt Service Routine, overgang van 0 naar 1);//

}

void loop() 
{
  if(startprogram == true)
  {
    digitalWrite(led,HIGH);
    
  }

  if (stopprogram == true)
  {
    digitalWrite(led,LOW);
  }

}

void ISR_test(void)
{
  i++;
  if (i == 1)
  {
    startprogram = true;
    stopprogram = false;
    Serial.println("Programma start");

  }

  else if (i == 2)
  {
    stopprogram = true;
    startprogram = false;
    Serial.println("Programma stopt");
    i = 0;
  }
  
  else
  {

  }
  
}
  

  



