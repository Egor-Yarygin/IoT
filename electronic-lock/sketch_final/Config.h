#ifndef CONFIG_H
#define CONFIG_H

const char *ap_ssid = "ESP8266-AP";
const char *ap_password = "12345678";

const char *index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP8266 Wi-Fi Config</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <form action="/connect">
    SSID: <input type="text" name="ssid"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Submit">
  </form>
</body>
</html>)rawliteral";

const char *success_connect = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Connected to Wi-Fi!</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>Successfully connected to Wi-Fi!</h1>
  <p>Success</p>
</body>
</html>)rawliteral";

const char *failed_connect = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Failed to connect to Wi-Fi!</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h1>Failed to connect to Wi-Fi!</h1>
  <p>Please try again: <a href="/">Go back to configuration</a></p>
</body>
</html>)rawliteral";

#endif // CONFIG_H
