/*
João Fernandes
Dúvidas: enviar mensagem github...
Esse código será aplicado para no avião, arduino nano ou mini( recomendado)
Perdão pela falta de profissionalidade, foi um projeto feito a muito tempo atrás.
Sorry for the unprofessionality, it was a project done a long time ago.
*/


#include <VirtualWire.h>

#define serv1 10 // Define entrada servo 1
#define serv2 12 // Define entrada servo 2

// ------ Inicialização de variáveis
int valor;
int valorR[3];
char recebido[3];
int j;
//------ Fim de Inicialização

//=========== Possíveis  SAIDAS =========
const int motores = 7;
void serv1_0();
void serv1_90();
void serv1_180();
void serv2_0();
void serv2_90();
void ser2_180();
void setup() {

  //===== Recepção ====
  Serial.begin(9600);
  vw_set_rx_pin(3); // Pino de comunicação do módulo RF 433 MHZ - Receptor
  vw_setup(5000);
  vw_rx_start();
  Serial.println("Recepçao modulo RF - Aguardando...");

}

void loop() {

 //------ RECEPÇAO -----------

  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if(vw_get_message(buf, &buflen)){

    int i;
    int j=2;
      for(i=0; i<buflen; i++){
        recebido[i] = char(buf[i]);
      }

      recebido[buflen] = '\0';
      valor = atoi (recebido);
     while(j>-1){
      valorR[j] = valor%10;
      valor = valor/10;
      j--;
     }
      Serial.print("\nRecebido: ");
      Serial.print(valorR[0]);
      Serial.print(valorR[1]);
      Serial.print(valorR[2]);


      //============= POSSIBILIDADES ===========

      //------------- MOTORES ------------------
      if(valorR[0] == 2 ){
        digitalWrite(motores, HIGH);

      }
      else {
        digitalWrite(motores, LOW);
      }

      //============ Flaps dianteiros =========

      if(valorR[2] == 1){
         serv1_180();
        serv2_180();

      }
      else{
            if(valorR[2] == 2){
              for(int j=0;j<10;j++){
                serv1_90();
                serv2_90();
              }
                }
                 else{
                  if (valorR[2] == 3){
                  for(int j=0;j<10;j++){
                  serv1_0();
                  serv2_0();
                  }
            }
       }
      }
  }
}
void serv1_180(){
  digitalWrite(serv1, HIGH);
  delayMicroseconds(600);
  digitalWrite(serv1, LOW);
  //Serial.println(" 0 GRAUS \n");
  delayMicroseconds(19400);

}
void serv1_90(){
   digitalWrite(serv1, HIGH);
  delayMicroseconds(1500);
 // Serial.println(" 90 GRAUS \n");
  digitalWrite(serv1, LOW);
  delayMicroseconds(18500);
}
void serv1_0(){
  digitalWrite(serv1, HIGH);
  delayMicroseconds(240);
  //Serial.println(" 180 GRAUS \n");
  digitalWrite(serv1, LOW);
  delayMicroseconds(19760);
}
void serv2_180(){
  digitalWrite(serv2, HIGH);
  delayMicroseconds(600);
  digitalWrite(serv2, LOW);
  //Serial.println(" 0 GRAUS \n");
  delayMicroseconds(19400);

}
void serv2_90(){
   digitalWrite(serv2, HIGH);
  delayMicroseconds(1500);
 // Serial.println(" 90 GRAUS \n");
  digitalWrite(serv2, LOW);
  delayMicroseconds(18500);
}
void serv2_0(){
  digitalWrite(serv2, HIGH);
  delayMicroseconds(240);
  //Serial.println(" 180 GRAUS \n");
  digitalWrite(serv2, LOW);
  delayMicroseconds(19760);
}
