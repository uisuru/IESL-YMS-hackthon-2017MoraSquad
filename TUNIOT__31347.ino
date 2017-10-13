/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>

WiFiClient client;

String MakerIFTTT_Key ;
;String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;

void setup()
{
  Serial.begin(9600);

    WiFi.disconnect();
  delay(3000);
  Serial.println("START");
   WiFi.begin("hansa");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.println("....");

  }
  Serial.println("Connected");
  if (client.connect("maker.ifttt.com",80)) {
    MakerIFTTT_Key ="g0nbd-jRobHwmgN4eC2_lOLRS0lwBHupkZAcfW-M45J";
    MakerIFTTT_Event ="facebook";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "Help me");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "i\'m in trouble");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "at Home (this message sent by Smart security Platform)");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);

    Serial.println("Sent to ifttt");

  }

}


void loop()
{


}