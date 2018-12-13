

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ejecutarFuncion(print_1);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int print_1(){
  Serial.println("Hola yo soy print 1");
  return 0;
}


int print_2(){
  Serial.println("Hola yo soy print 2");
  return 0;
}


int print_3(){
  Serial.println("Hola yo soy print 3");
  return 0;
}


int print_4(){
  Serial.println("Hola yo soy print 4");
  return 0;
}

void ejecutarFuncion(int (*funcion)()){
  funcion();
}

