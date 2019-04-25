#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "data_post.h"
#include "thm.h"
#include "light.h"
#include "secrets.h"
#include "debug.h"

HTTPClient http2;
void postBedsideTableData(){
  http2.begin(post_influxdb_path);
  http2.setAuthorization(post_influxdb_user,post_influxdb_pass);
  int ret=http2.POST("btd thm="+String(getThm())+",light="+String(readLight()));
  debugLog("postBedsideTableData()","HTTP POST: "+String(ret));
  return;
}
