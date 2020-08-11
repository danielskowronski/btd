# luftdaten 

## InfluxDB query
```
select  mean("SDS_P1"), mean("BME280_temperature") FROM "feinstaub" WHERE time >= now() - 5m
```

## example data
```
{
  "results": [
    {
      "statement_id": 0,
      "series": [
        {
          "name": "feinstaub",
          "columns": [
            "time",
            "mean",
            "mean_1"
          ],
          "values": [
            [
              "2020-08-11T21:44:00Z",
              3.1,
              22.5
            ],
            [
              "2020-08-11T21:46:00Z",
              4.72,
              22.49
            ],
            [
              "2020-08-11T21:48:00Z",
              3.55,
              22.45
            ]
          ]
        }
      ]
    }
  ]
}
```