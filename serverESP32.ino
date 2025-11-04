#include <WiFi.h>
#include <WebServer.h>

//Nome e senha do ponto de acesso
const char* ssid = "IoT01-Senac-Ingrid";
const char* password = "12345678";

//Define o pino do LED
const int ledPin1 = 14;
const int ledPin2 = 33;

//Criar um servidor web na porta 80
WebServer server(80);

//Página HTML que vai ser exibida nesse servidor
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controlando Led</title>
    <style>
        body{
            margin: 0;
            padding: 20px;
            font-family: Arial, Helvetica, sans-serif;
            background-color: #0f172a;
            color: #e5e7eb;
            text-align: center;
        }
        h1 {
            color: #60a5fa;
        }
        p{
            color: #cbd5e1;
            margin-bottom: 30px;
        }
        button{
            color: #fff;
            border: none;
            padding: 14px 24px;
            margin: 8px;
            border-radius: 8px;
            font-size: 16px;
            width: 100%;
            max-width: 220px;
            font-weight: bold;
        }
        .btn-liga{
            background-color: #77b26b;
            color: #0a5c0a;
        }
        .btn-desliga{
            background-color: #f98098;
            color: #b81414;
        }
        h2{
            border-bottom: 1px solid #cbd5e155;
        }
        .title-led1{
            color: #ff0046;
        }
        .title-led2{
            color: #7b68ee;
        }

    </style>
</head>
<body>
    <h1>Turma de IoT01 - Senac L13</h1>
    <p>Voce esta conectado ao Servidor de <strong>Ingrid</strong></p>
    <h2 class="title-led1">LED 1</h2>
    <button onclick="location.href='/liga1'" class="btn-liga">Liga ✅</button>
    <button onclick="location.href='/desliga1'" class="btn-desliga">Desliga ⛔</button>
    <br>
    <h2 class="title-led2">LED 2</h2>
    <button onclick="location.href='/liga2'" class="btn-liga">Liga ✅</button>
    <button onclick="location.href='/desliga2'" class="btn-desliga">Desliga ⛔</button>
</body>
</html>
)rawliteral";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

//função para ligar o led
void handleLedOn1(){
  digitalWrite(ledPin1, HIGH);
  server.send(200, "text/html", htmlPage);
}

void handleLedOn2(){
  digitalWrite(ledPin2, HIGH);
  server.send(200, "text/html", htmlPage);
}

//função para desligar o led
void handleLedOff1(){
  digitalWrite(ledPin1, LOW);
  server.send(200, "text/html", htmlPage);
}

void handleLedOff2(){
  digitalWrite(ledPin2, LOW);
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Configurando Access Point");

  //Inicia o Ponto de Acesso
  WiFi.softAP(ssid, password);

  //Exibir o IP do ESP32
  Serial.print("IP do ESP32:");
  Serial.println(WiFi.softAPIP());

  //Definir a rota em que a nossa página vai ser exibida (/)
  server.on("/", handleRoot);
  server.on("/liga1", handleLedOn1);
  server.on("/desliga1", handleLedOff1);
  server.on("/liga2", handleLedOn2);
  server.on("/desliga2", handleLedOff2);

  //iniciar o servidor
  server.begin();
  Serial.println("Servidor web iniciado!"); 

  //Definindo porta do led como output 
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}



void loop() {
  //configuração que mantem o servidor ativo
  server.handleClient();
}




