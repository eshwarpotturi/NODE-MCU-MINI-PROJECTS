#include "esp_http_client.h"
#include <WiFi.h>
#include "Arduino.h"

const char* ssid = "NSA";
const char* password = "Orange";

const char *post_url = "http://your-webserver.net/yourscript.php"; // Location to send POSTed data
const char *post_data = "field1=value1&field2=value2";  // Post data can be name value, or just value

bool internet_connected = false;

void setup()
{
  Serial.begin(115200);

  if (init_wifi()) { // Connected to WiFi
    internet_connected = true;
    Serial.println("Internet connected");
  }
}

bool init_wifi()
{
  int connAttempts = 0;
  Serial.println("\r\nConnecting to: " + String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
    if (connAttempts > 10) return false;
    connAttempts++;
  }
  return true;
}


esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
  switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
      Serial.println("HTTP_EVENT_ERROR");
      break;
    case HTTP_EVENT_ON_CONNECTED:
      Serial.println("HTTP_EVENT_ON_CONNECTED");
      break;
    case HTTP_EVENT_HEADER_SENT:
      Serial.println("HTTP_EVENT_HEADER_SENT");
      break;
    case HTTP_EVENT_ON_HEADER:
      Serial.println();
      Serial.printf("HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
      break;
    case HTTP_EVENT_ON_DATA:
      Serial.println();
      Serial.printf("HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
      if (!esp_http_client_is_chunked_response(evt->client)) {
        // Write out data
        // printf("%.*s", evt->data_len, (char*)evt->data);
      }
      break;
    case HTTP_EVENT_ON_FINISH:
      Serial.println("");
      Serial.println("HTTP_EVENT_ON_FINISH");
      break;
    case HTTP_EVENT_DISCONNECTED:
      Serial.println("HTTP_EVENT_DISCONNECTED");
      break;
  }
  return ESP_OK;
}

static esp_err_t post_something()
{
  esp_err_t res = ESP_OK;

  esp_http_client_handle_t http_client;
  
  esp_http_client_config_t config_client = {0};
  config_client.url = post_url;
  config_client.event_handler = _http_event_handler;
  config_client.method = HTTP_METHOD_POST;

  http_client = esp_http_client_init(&config_client);
  
  esp_http_client_set_post_field(client, post_data, strlen(post_data));

  // esp_http_client_set_header(http_client, "Content-Type", "image/jpg"); // sending a jpg file

  esp_err_t err = esp_http_client_perform(http_client);
  if (err == ESP_OK) {
    Serial.print("esp_http_client_get_status_code: ");
    Serial.println(esp_http_client_get_status_code(http_client));
  }

  esp_http_client_cleanup(http_client);
}

void loop()
{
  if (condition met) { 
    post_something();
  }
}

On the server side assuming you are using PHP you use this code to name and save files:
1
2
3
$received = file_get_contents('php://input');
$fileToWrite = "upload - ".time().".jpg";
file_put_contents($fileToWrite, $received);
This code below will send a received file to your email address. You need to update the email address in lines 6 and 27. If you are not sending a JPG you need to change line 20 to reflect the content type.



$received = file_get_contents('php://input');
$timeNow = date("F j, Y, g:i a");
$subject = "Email Subject - ".time();
 
$bound_text = "----*%$!$%*";
$bound = "--".$bound_text."\r\n";
$bound_last = "--".$bound_text."--\r\n";
 
$headers = "From: youremail@host.com\r\n";
$headers .= "MIME-Version: 1.0\r\n" .
"Content-Type: multipart/mixed; boundary=\"$bound_text\""."\r\n" ;
$message =
'Content-Type: text/html; charset=UTF-8'."\r\n".
'Content-Transfer-Encoding: 7bit'."\r\n\r\n".
'
<html>
<head>
</head>
<body>
</body>
</html>'."\n\n".
$bound;
 
$message .= "Content-Type: image/jpeg; name=\"filename.jpg\"\r\n"
."Content-Transfer-Encoding: base64\r\n"
."Content-ID: <filename.jpg>\r\n"
."\r\n"
.chunk_split(base64_encode($received))
.$bound_last;
 
echo mail('youremail@yourhost.net', $subject, $message, $headers);
