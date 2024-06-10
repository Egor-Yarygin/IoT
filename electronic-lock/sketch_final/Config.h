#ifndef CONFIG_H
#define CONFIG_H

const char *ap_ssid = "ESP8266";
const char *ap_password = "<KVL=0nR!<}Pi9KQ";

const char *index_html = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP8266 Wi-Fi Config</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 0;
        font-size: 16px; 
    }
    .container {
        max-width: 90%; 
        margin: 0 auto;
        padding: 2em;
    }
    h2 {
        text-align: center;
        color: #333;
        font-size: 1.5em;
    }
    form {
        background-color: #f9f9f9;
        padding: 1.25em;
        border-radius: 0.5em;
        box-shadow: 0 0 0.625em rgba(0, 0, 0, 0.1);
    }
    label {
        display: block;
        margin-bottom: 0.3125em;
        font-weight: bold;
        color: #333;
    }
    input[type="text"], input[type="password"] {
        width: 100%;
        padding: 0.625em;
        margin-bottom: 1.25em;
        border: 0.0625em solid #ddd;
        border-radius: 0.25em;
        box-sizing: border-box;
        font-size: 1em;
    }
    input[type="submit"] {
        width: 100%;
        background-color: #4CAF50;
        color: white;
        padding: 0.625em;
        text-align: center;
        text-decoration: none;
        font-size: 1em;
        margin-top: 0.625em;
        border-radius: 0.25em;
        border: none;
        cursor: pointer;
    }
    input[type="submit"]:hover {
        background-color: #45a049;
    }
  </style>
</head>
<body>
  <div class="container">
    <h2>ESP8266 Wi-Fi Config</h2>
    <form action="/connect">
      <label for="ssid">SSID:</label>
      <input type="text" id="ssid" name="ssid" required><br>
      <label for="password">Password:</label>
      <input type="password" id="password" name="password" required><br>
      <input type="submit" value="Submit">
    </form>
  </div>
</body>
</html>)rawliteral";

const char *success_connect = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Connected to Wi-Fi!</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 0;
        font-size: 16px; 
    }
    .container {
        max-width: 90%; 
        margin: 0 auto;
        padding: 2em;
    }
    h1 {
        text-align: center;
        color: #333;
        font-size: 1.5em;
    }
    p {
        text-align: center;
        color: #333;
        font-size: 1em;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Successfully connected to Wi-Fi!</h1>
    <p>Connect to your internet connection and follow the link: <a href="http://192.168.0.104:8000/">SERVER</a></p>
  </div>
</body>
</html>)rawliteral";

const char *failed_connect = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Failed to connect to Wi-Fi!</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
        font-family: Arial, sans-serif;
        margin: 0;
        padding: 0;
        font-size: 16px; 
    }
    .container {
        max-width: 90%; 
        margin: 0 auto;
        padding: 2em;
    }
    h1 {
        text-align: center;
        color: #333;
        font-size: 1.5em;
    }
    p {
        text-align: center;
        color: #333;
        font-size: 1em;
    }
    a {
        color: #4CAF50;
        text-decoration: none;
    }
    a:hover {
        text-decoration: underline;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Failed to connect to Wi-Fi!</h1>
    <p>Please try again: <a href="/">Go back to configuration</a></p>
  </div>
</body>
</html>)rawliteral";

#endif