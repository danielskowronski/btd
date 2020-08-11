#ifndef secrets_h
#define secrets_h

#define wifi_ssid "..."
#define wifi_password "..."

#define get_influxdb_path "http://...:...@...:8086/query?db=...&q=select%20%20mean%28%22SDS_P1%22%29%2C%20mean%28%22BME280_temperature%22%29%20FROM%20%22feinstaub%22%20WHERE%20time%20%3E%3D%20now%28%29%20-%205m"

#define post_influxdb_path "http://...:8086/write?db=..."
#define post_influxdb_user "..."
#define post_influxdb_pass "..."

#endif
