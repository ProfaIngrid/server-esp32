#include <WiFi.h>
#include <WebServer.h>

//Nome e senha do ponto de acesso
const char* ssid = "IoT01-Senac-Ingrid";
const char* password = "12345678";

//Criar um servidor web na porta 80
WebServer server(80);

//Página HTML que vai ser exibida nesse servidor
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR"> 
    <h1>Turma de IoT01 - Senac L13</h1>
    <p>Voce esta conectado ao Servidor de <strong>Ingrid</strong></p>
</html>
)rawliteral";

void handleRoot(){
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

  //iniciar o servidor
  server.begin();
  Serial.println("Servidor web iniciado!"); 
}


void loop() {
  //configuração que mantem o servidor ativo
  server.handleClient();
}
