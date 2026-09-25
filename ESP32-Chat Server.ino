#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

// ===============================
// Wi-Fi Access Point credentials
// ===============================
const char* ssid = "ESP32_CHAT";
const char* password = "12345678";

// ===============================
// Create servers
// ===============================
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// ===============================
// Chat webpage
// ===============================
const char webpage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <title>ESP32 Chat Server</title>

  <style>
    body {
      font-family: Arial, sans-serif;
      background: #f2f2f2;
      margin: 0;
      padding: 20px;
    }

    .container {
      max-width: 600px;
      margin: auto;
      background: white;
      padding: 20px;
      border-radius: 12px;
      box-shadow: 0 3px 10px rgba(0,0,0,0.2);
    }

    h1 {
      text-align: center;
    }

    #status {
      text-align: center;
      color: green;
      margin-bottom: 15px;
    }

    #messages {
      height: 350px;
      overflow-y: auto;
      border: 1px solid #ccc;
      padding: 10px;
      border-radius: 8px;
      background: #fafafa;
      margin-bottom: 10px;
    }

    .message {
      background: #e8f0fe;
      padding: 8px;
      margin: 5px 0;
      border-radius: 6px;
    }

    .input-area {
      display: flex;
      gap: 8px;
    }

    input {
      flex: 1;
      padding: 12px;
      border: 1px solid #ccc;
      border-radius: 6px;
      font-size: 16px;
    }

    button {
      padding: 12px 18px;
      border: none;
      border-radius: 6px;
      background: #007bff;
      color: white;
      font-size: 16px;
      cursor: pointer;
    }

    button:hover {
      background: #0056b3;
    }
  </style>
</head>

<body>

<div class="container">

  <h1>ESP32 Chat Server</h1>

  <div id="status">Connecting...</div>

  <div id="messages"></div>

  <div class="input-area">
    <input
      type="text"
      id="message"
      placeholder="Type your message..."
      onkeydown="checkEnter(event)"
    >

    <button onclick="sendMessage()">SEND</button>
  </div>

</div>

<script>

  let websocket;

  // Connect to ESP32 WebSocket server
  function connectWebSocket() {

    websocket = new WebSocket(
      "ws://" + window.location.hostname + ":81/"
    );

    websocket.onopen = function() {
      document.getElementById("status").innerHTML =
        "Connected to ESP32";
      document.getElementById("status").style.color = "green";
    };

    websocket.onclose = function() {
      document.getElementById("status").innerHTML =
        "Disconnected";
      document.getElementById("status").style.color = "red";

      // Try reconnecting
      setTimeout(connectWebSocket, 2000);
    };

    websocket.onerror = function() {
      document.getElementById("status").innerHTML =
        "Connection Error";
      document.getElementById("status").style.color = "red";
    };

    websocket.onmessage = function(event) {

      let messages = document.getElementById("messages");

      let message = document.createElement("div");

      message.className = "message";

      message.innerHTML = event.data;

      messages.appendChild(message);

      messages.scrollTop = messages.scrollHeight;
    };
  }


  // Send message
  function sendMessage() {

    let input = document.getElementById("message");

    let message = input.value.trim();

    if (message !== "") {

      websocket.send(message);

      input.value = "";

      input.focus();
    }
  }


  // Press ENTER to send
  function checkEnter(event) {

    if (event.key === "Enter") {
      sendMessage();
    }

  }


  // Start WebSocket connection
  connectWebSocket();

</script>

</body>
</html>
)rawliteral";


// ===============================
// WebSocket event handler
// ===============================

void webSocketEvent(
  uint8_t num,
  WStype_t type,
  uint8_t *payload,
  size_t length
) {

  switch (type) {

    // ---------------------------
    // Client connected
    // ---------------------------
    case WStype_CONNECTED:

      Serial.print("Client connected: ");
      Serial.println(num);

      webSocket.sendTXT(
        num,
        "<b>ESP32:</b> Welcome to the chat!"
      );

      break;


    // ---------------------------
    // Client disconnected
    // ---------------------------
    case WStype_DISCONNECTED:

      Serial.print("Client disconnected: ");
      Serial.println(num);

      break;


    // ---------------------------
    // Message received
    // ---------------------------
    case WStype_TEXT:

      Serial.print("Message from client ");
      Serial.print(num);
      Serial.print(": ");

      Serial.println((char*)payload);

      // Create message
      String message = "<b>User ";
      message += String(num + 1);
      message += ":</b> ";
      message += String((char*)payload);

      // Broadcast message to all connected clients
      webSocket.broadcastTXT(message);

      break;


    default:
      break;
  }
}


// ===============================
// Web server root page
// ===============================

void handleRoot() {

  server.send(
    200,
    "text/html",
    webpage
  );
}


// ===============================
// Setup
// ===============================

void setup() {

  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("==============================");
  Serial.println("ESP32 CHAT SERVER");
  Serial.println("==============================");


  // ---------------------------
  // Start ESP32 Access Point
  // ---------------------------

  WiFi.mode(WIFI_AP);

  bool result = WiFi.softAP(
    ssid,
    password
  );

  if (result) {

    Serial.println("Access Point Started!");

  } else {

    Serial.println("Access Point Failed!");

  }


  // ---------------------------
  // Display network information
  // ---------------------------

  Serial.println();

  Serial.print("Wi-Fi Name: ");
  Serial.println(ssid);

  Serial.print("Wi-Fi Password: ");
  Serial.println(password);

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.softAPIP());

  Serial.println();


  // ---------------------------
  // Start Web Server
  // ---------------------------

  server.on(
    "/",
    handleRoot
  );

  server.begin();

  Serial.println("Web Server Started");


  // ---------------------------
  // Start WebSocket Server
  // ---------------------------

  webSocket.begin();

  webSocket.onEvent(
    webSocketEvent
  );

  Serial.println("WebSocket Server Started");

  Serial.println();
  Serial.println("Connect your phone/laptop to:");
  Serial.println(ssid);

  Serial.println();
  Serial.println("Then open:");
  Serial.println("http://192.168.4.1");

  Serial.println("==============================");
}


// ===============================
// Main loop
// ===============================

void loop() {

  // Handle normal HTTP requests
  server.handleClient();

  // Handle WebSocket communication
  webSocket.loop();

}
