# luftdaten json data format

## data format expected
```
{"esp8266id": "xxxxxxx", "software_version": "NRZ-2018-123B", "sensordatavalues":[{"value_type":"SDS_P1","value":"27.65"},{"value_type":"SDS_P2","value":"10.60"},{"value_type":"temperature","value":"43.30"},{"value_type":"humidity","value":"5.20"},{"value_type":"BME280_temperature","value":"33.87"},{"value_type":"BME280_humidity","value":"10.25"},{"value_type":"BME280_pressure","value":"99623.66"},{"value_type":"samples","value":"748814"},{"value_type":"min_micro","value":"78"},{"value_type":"max_micro","value":"25389"},{"value_type":"signal","value":"-68"}]}
```

```
{
  "esp8266id": "xxxxxxx",
  "software_version": "NRZ-2018-123B",
  "sensordatavalues": [
    {
      "value_type": "SDS_P1",
      "value": "27.65"
    },
    {
      "value_type": "SDS_P2",
      "value": "10.60"
    },
    {
      "value_type": "temperature",
      "value": "43.30"
    },
    {
      "value_type": "humidity",
      "value": "5.20"
    },
    {
      "value_type": "BME280_temperature",
      "value": "33.87"
    },
    {
      "value_type": "BME280_humidity",
      "value": "10.25"
    },
    {
      "value_type": "BME280_pressure",
      "value": "99623.66"
    },
    {
      "value_type": "samples",
      "value": "748814"
    },
    {
      "value_type": "min_micro",
      "value": "78"
    },
    {
      "value_type": "max_micro",
      "value": "25389"
    },
    {
      "value_type": "signal",
      "value": "-68"
    }
  ]
}
```