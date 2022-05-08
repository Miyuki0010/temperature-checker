# Temperature Sensor REST-API

For the database:

`
create table tbl_data
(
    IoT_MAC  varchar(20)                  null,
    time     int default unix_timestamp() null,
    temp     float                        null,
    humidity int                          null
);
`

For the config file: Copy Config-Sample as the Config.php file and change the values.

For the API call: `../upload.php?sensor=MACAdress&temp=SomeTemperature&humid=somevalue`.

