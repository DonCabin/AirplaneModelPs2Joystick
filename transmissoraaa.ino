/*
João Fernandes
Dúvidas: enviar mensagem github...
Esse código será aplicado para o envio de mensagens de controle , qualquer arduino.
Perdão pela falta de profissionalidade, foi um projeto feito a muito tempo atrás.
Sorry for the unprofessionality, it was a project done a long time ago.
*/
#include<VirtualWire.h>
#include<PS2X_lib.h>

PS2X ps2x; // Define um controle de playstation 2
// ------ Inicialização de variáveis
int analogY=0;
int analogX=0;
int aviao;
char valorchar[3];
int valor;
byte vibrate=0;
int error=0;
//------ Fim de Inicialização

void setup() {

Serial.begin(9600);
vw_set_tx_pin(4);// PIno de entrada do comunicador de transmissão RF 433 MHZ
vw_setup(5000);// Definição necessária
Serial.println("começou!");
error = ps2x.config_gamepad(13,11,10,12, true, true);//Iniciando o controle de playstation 2

}

void loop() {
  aviao = 0;
  ps2x.read_gamepad(false, vibrate); // Desliga vibração do controle
  analogY = ps2x.Analog(PSS_LY); // Define variável para o analógico Y
  analogX = ps2x.Analog(PSS_RX);// Define variável para o analógico X

  // -------- MOTOR ---------
  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1) || ps2x.Button(PSB_R2) || ps2x.Button(PSB_L2)){
    aviao = aviao + 200;
    // motor ligado
  }
  else{
    aviao = aviao + 100;
    //motor desligado
  }

  //-------- FLAPS FRONTAIS --------

  if(ps2x.Button(PSB_RED)){
    aviao = aviao + 2;
    //  flaps direita
  }
  else{
      if (ps2x.Button(PSB_PINK)){
          aviao = aviao + 3;
          // flaps esquerda
           }
          else{
             aviao = aviao + 1;
          }
 }
  //---------- TRANSMISSAO --------------

  itoa(aviao,valorchar,10); // Converte valor de int da variável aviao para string para variável valorchar
  vw_send((uint8_t *)valorchar, strlen(valorchar)); // Envia a mensagem
  vw_wait_tx();// Aguarda o envio
  Serial.print (" VALOR ENVIADO: ");
  Serial.println (valorchar); // Printa o valor
 delay(50);
}
