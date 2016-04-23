
    #include <Servo.h>
    
    int seguridad = 30;
    int posicion_base;  // pot base
    int posicion_codo; // pot codo
    int posicion_hombro; // pot hombro

    int destino_hombro;//destino del hombro
    int destino_hombro2;
    int destino_hombro3;
    int destino_codo;
    int destino_codo2;
    int destino_mun;

    
    int objetivo_hombro=0;
    int objetivo_codo=0;

    int enviado; //Aqui enviamos el numero completo
    int num; //Numero del servo
    int posicion; //Posicion del servo

    int Lecturas[20]; //Vector de lecturas.
    int Val, i = 0, Total = 0, Promedio = 0;
    
    int Lecturas2[20]; //Vector de lecturas.
    int Val2, i2 = 0, Total2 = 0, Promedio2 = 0, Val2a;
    
    int Lecturas3[20]; //Vector de lecturas.
    int Val3, i3 = 0, Total3 = 0, Promedio3 = 0;
    
    int Lecturas4[20]; //Vector de lecturas.
    int Val4, i4 = 0, Total4 = 0, Promedio4 = 0;

    int Lecturas5[20]; //Vector de lecturas.
    int Val5, i5 = 0, Total5 = 0, Promedio5 = 0;
    
    int Lecturas6[20]; //Vector de lecturas.
    int Val6, i6 = 0, Total6 = 0, Promedio6 = 0;

    
    Servo shorizontal;
    Servo smuneca1;
    Servo smuneca2;
    Servo sgiro;
    Servo spinza;
        
    int hombro_up = 22;
    int hombro_down = 23;
    
    int giro_izquierda = 24;
    int giro_derecha = 25;
    
    int codo_up = 26;
    int codo_down = 27;
    
    int pulgar = 28;    
    int gatillo = 29;
    
    int espulgar = 0;
    int esgatillo = 0;
    int led = 13;
    
     
    int SENSOR_PIN = 7; // center pin of the potentiometer
     
    int RPWM_Output = 12; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
    int LPWM_Output = 13; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
    
    int RPWM_Output2 = 4; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
    int LPWM_Output2 = 3; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

    
    void setup()
{
    Serial.begin(9600);

    shorizontal.attach(2);
    smuneca1.attach(5);
    smuneca2.attach(6);
    sgiro.attach(11);
    spinza.attach(8);
        
    
    posicion = 0;
    
    pinMode(seguridad, INPUT);
  
    pinMode(giro_izquierda, OUTPUT);
    pinMode(giro_derecha, OUTPUT);
    
    pinMode(gatillo, INPUT);
    pinMode(pulgar, INPUT);
    pinMode(led, OUTPUT);
    
    pinMode(RPWM_Output, OUTPUT);
    pinMode(LPWM_Output, OUTPUT);
    
    pinMode(RPWM_Output2, OUTPUT);
    pinMode(LPWM_Output2, OUTPUT);

    
}     

    void loop()
{

  if(seguridad, HIGH) //funcion de interruptor de seguridad.
  {
    
  //lectura posicion codo
    posicion_base = map(analogRead(A8), 200, 800, 320, 0);
    posicion_codo = map(analogRead(A6), 0, 1023, 180, 0);
    posicion_hombro = map(analogRead(A7), 0, 1023, 180, 0);
    Serial.print(" B ");
    Serial.print(posicion_base, DEC);
    Serial.print(" H ");
    Serial.print(posicion_hombro, DEC);
    Serial.print(" C ");
    Serial.println(posicion_codo, DEC);

    shorizontal.write(89);
 
 //programacion movimientos:
  if(Serial.available() >= 1)
  {
    /*
    1- Leer un numero entero por serial
    2- Calculamos su modulo por 10 (sera el numero del motor)
    3- Dividir el entero inicial por 10
    4- Lo que quede, sera la posicion del motor
    */
    enviado = Serial.parseInt();
    num = enviado%10;
    enviado = enviado/10;
    posicion = enviado;
     
    if(num == 0) //abrimos pinza 
    {
      spinza.write(180);    
    }
    if(num == 9)  //cerramos pinza
    {
      spinza.write(0); 
    }
    
    if( num == 1)
    {
      base(posicion);
    }
    
    if ( num == 2 )
    {
      hombro(posicion);
    }
    
    if ( num == 3)
    {
      codo(posicion);
    }
    
    
    if(num == 4) //quiere decir que movemos en vertical la muñeca
    {
      smuneca1.write(posicion);
      //smuneca2.write(posicion2);//falta poner este, pero hayq ue hacer lo del cambio de grados
    }

    if(num ==5) //quiere decir que giramos la muñeca
    {
      sgiro.write(posicion);
    }

    
     
  if (num == 7) // prueba programaicon movimientos
    {

      spinza.write(180);
      codo (70);
      hombro (117);
      spinza.write(0);
      delay(1000);
      hombro(90);
      codo(100);
      base(350);
      codo(80);
      hombro(100);
      spinza.write(180);
      hombro(90);
      codo(100);
      base(180);
      
      
    } // fin movimiento programado


  }

  }//fin seguridad
 } // fin loop

    void codo(int objetivo)
    {

    if(objetivo>posicion_codo){
    do{
      analogWrite(LPWM_Output, 0);
      analogWrite(RPWM_Output, 250);
      posicion_codo = map(analogRead(A6), 0, 1023, 180, 0);
      Serial.print("subiendo codo  ");
      Serial.println(posicion_codo, DEC);
          if(num == 3) // parar todo
        {
          analogWrite(LPWM_Output, 0);
          analogWrite(RPWM_Output, 0);
          analogWrite(LPWM_Output2, 0);
          analogWrite(RPWM_Output2, 0);
        }
     }
     while(posicion_codo < objetivo);
      }
      
      
    //aqui subimos el codo hasta que llega al angulo correcto  
    if(objetivo<posicion_codo){
    do{
      analogWrite(LPWM_Output, 150);
      analogWrite(RPWM_Output, 0);
      posicion_codo = map(analogRead(A6), 0, 1023, 180, 0);
      Serial.print("codo codo  ");
      Serial.println(posicion_codo, DEC);
          if(num == 3) // parar todo
        {
          analogWrite(LPWM_Output, 0);
          analogWrite(RPWM_Output, 0);
          analogWrite(LPWM_Output2, 0);
          analogWrite(RPWM_Output2, 0);
        }
     }
     while(posicion_codo > objetivo);
      }
      
      //aqui paramos los motores al llegar al angulo correcto 
      analogWrite(LPWM_Output, 0);
      analogWrite(RPWM_Output, 0);


    }

    void hombro(int objetivo)
    {

     //aqui bajamos el hombro hasta que llega al angulo correcto  
      if(objetivo>posicion_hombro){
    do{
      analogWrite(LPWM_Output2, 0);
      analogWrite(RPWM_Output2, 100);
      posicion_hombro = map(analogRead(A7), 0, 1023, 180, 0);
      Serial.print("bajando hombro  ");
      Serial.println(posicion_hombro, DEC);
          if(num == 3) // parar todo
        {
          analogWrite(LPWM_Output, 0);
          analogWrite(RPWM_Output, 0);
          analogWrite(LPWM_Output2, 0);
          analogWrite(RPWM_Output2, 0);
        }
     }
     while(posicion_hombro < objetivo);
      }
      
      //aqui subimos el hombro hasta que llega al angulo correcto  
    if(objetivo<posicion_hombro){
    do{
      analogWrite(LPWM_Output2, 100);
      analogWrite(RPWM_Output2, 0);
      posicion_hombro = map(analogRead(A7), 0, 1023, 180, 0);
      Serial.print("subiendo hombro  ");
      Serial.println(posicion_hombro, DEC);
          if(num == 3) // parar todo
        {
          analogWrite(LPWM_Output, 0);
          analogWrite(RPWM_Output, 0);
          analogWrite(LPWM_Output2, 0);
          analogWrite(RPWM_Output2, 0);
        }
     }
     while(posicion_hombro > objetivo);
      }
      //aqui paramos los motores al llegar al angulo correcto 
      analogWrite(LPWM_Output2, 0);
      analogWrite(RPWM_Output2, 0);
    }
    
      
    


 
    void base(int objetivo)
    {
              if(objetivo>posicion_base)
      {
        do{
          shorizontal.write(120);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando izqda ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo>posicion_base+15);

        do{
          shorizontal.write(100);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando izqda ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo>posicion_base+10);

        do{
          shorizontal.write(93);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando izqda ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo>posicion_base);
      }
      
      if(objetivo<posicion_base)
      {
        do{
          shorizontal.write(55);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando dcha ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo<posicion_base-15);

        do{
          shorizontal.write(75);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando dcha ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo<posicion_base-10);

        do{
          shorizontal.write(77);
          posicion_base = map(analogRead(A8), 200, 800, 320, 0);
          Serial.print("girando dcha ");
          Serial.println(posicion_base, DEC);
        }
        while(objetivo<posicion_base);
      }
      
    }
    
    
    


