#include <pgmspace.h>

#define SECRET
#define THINGNAME "Gyro_ESP32"
#define PUBLISH_TOPIC   "gyro/pub"
#define SUBSCRIBE_TOPIC "gyro/sub"

const char WIFI_SSID[] = "Dasun's Galaxy M21";          
const char WIFI_PASSWORD[] = "sise9444";       
// const char AWS_IOT_ENDPOINT[] = "a33hi7uoksyr8d-ats.iot.eu-north-1.amazonaws.com";
const char AWS_IOT_ENDPOINT[] = "192.168.146.122";
// const int AWS_IOT_PORT = 8883;
const int AWS_IOT_PORT = 1883;

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUDCM5pNbhQBIjgYPfeqXlZovOjlEwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI0MDEwNjE4Mzcw
NVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAJucTSNt2VpWIn5HDjxp
3gvz6ndOuYGQ03Y4RMowaOyUvOYpU5qP8ujou2fd38C10FSLkK7L7mujWagMpgio
n2O7JvGb7tEmhFPpOKlXJLRyhKOOOsfISQE3exXjNbZn7KD/Obpbd56wAkgu/Kt0
i6L0tvoDkbCzCVljQ6AOtVIMbHyIzVPOKjGq2gEcUSasDoZZEqfTFq2c2pK4+r4C
jiV61tDf8jwFG4tr7/wyxqB/7PfdldVHw4OUVnPR4XiyIipPG7G6ZONqUBL8W4K4
e7yzwUovA3K9EDRjJzHo+T0h9ISFVXTgkjLo51zOLCwq/GEMDDZfkMH8l6yasOYq
4N8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUSt5aN+i3nkji4tf686X24rD6Ec0wHQYD
VR0OBBYEFEpCDqcmpM7elF4H3G8FpnML+yGuMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQDWaz2SjgbzZKCqwpMZJg3L9lf7
pwF9V5PAHtkMYxGc1Qmx/CKfqxe3v+JYHEGgW0El+0/mwgsUwE/VceiP03lIU2uD
YnS3nqC0kt2pcCABE7TVNpF2JmYodtTiEHTcuCZBUfA767dSs9Jr+aViUDYWMvLU
nznKuXLSCHOS/jmRNIc3+2msvIOqef3ZZBXnwa1L8pH1WpIj+D/gTj7hMnPIFyNE
KpNeUNTPAuOosHhImKTh/e4B2OrZgm6Pk4/179REYbKnQjwVZmTUULXBqpBQSDkv
3GkpRbQccOHjaMDefXuNl+ynkGsG0VWDRTBccauH3naOyToDdHxY6GoEl+Iv
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAm5xNI23ZWlYifkcOPGneC/Pqd065gZDTdjhEyjBo7JS85ilT
mo/y6Oi7Z93fwLXQVIuQrsvua6NZqAymCKifY7sm8Zvu0SaEU+k4qVcktHKEo446
x8hJATd7FeM1tmfsoP85ult3nrACSC78q3SLovS2+gORsLMJWWNDoA61UgxsfIjN
U84qMaraARxRJqwOhlkSp9MWrZzakrj6vgKOJXrW0N/yPAUbi2vv/DLGoH/s992V
1UfDg5RWc9HheLIiKk8bsbpk42pQEvxbgrh7vLPBSi8Dcr0QNGMnMej5PSH0hIVV
dOCSMujnXM4sLCr8YQwMNl+QwfyXrJqw5irg3wIDAQABAoIBAHwoL5vvD5b2Vrsu
cntddN9QlGjxFS39odsXdjtkeLMa0cVKf/w4knWnC7AJ5XdbGYf7e0scR3T2dpiQ
zwDlmZb3QlFQOzIBa1+QG7dxYkXfgVkGKHwyn50q6ThDex24uaKTQTohtMWWZZu2
cb9TU/6HBl9g7aNwlisN+m0Aj0eQh2kjhBeEMRMdAFdWMUCpMNNCEs5ohPrg74KL
xnkGmX1f5P4Jlpg8GkayvkzAvLuXY4HHkLmY7mnQtnDH6JbIJUrtUcXlrUO7jrUA
8Dfhm0V9OOPoISCDr7ycciDOuZIyYeM8NOW1lcLwyP60vg1mwL24kT24mkfWeemG
hKdQhxECgYEAzmQS2B8o0dD9+E4FrvSQX94LyS77A+dHxnh/kta6R+mYIG4RPM7y
nL88+tZcXlnLcH4slhMLQP1yFjcmx6MEolQ+LEWhVQ+wnX4HwHkOrCpCLOPFzZZK
1p8kH90urZSk55Uy7s51t3TK0y+dtPvY0r2BtNDPWORJMBa2FWNJeGUCgYEAwQOK
nywMKdJ97I6GL4/ZqQ3xjLfRGE9WCUQHIY6a1YsLIVHdgCkxnsDW/sj/sOYDTYTo
QpSR/XGB3TexStGDQh1lAwdder5su98Mw+JSXd4DLZpUn53Qwtbly24QZoqOUoj4
an+hdupN16DKI+QwDtjKS4mqYZhugzUceib7JfMCgYAuC3t8xe7YaHTQma+A6cTv
7lzYxGdx5n5H1Ag6HTev5Xhv+75Sv6S2vZ+AIqS20/ekIDIYRSVkmWaDeEhpj3/w
KzU3sU0d6gMwD7bxBND2LfNXinVNuXL20MhBZ5oLVbc4hzu2tU7j3+WEGgJoJyun
UGoIifFIVp3RYa+7s8vnVQKBgQCVGKg/VqY6tEfjsSEEoolPpt69hcz2i2p5k9wy
VtdSN6ssXPHOq4OSD4LEo/2n57YLbqx/qgawEbtwaDIDCp7rNout8EWMqIaUBbP1
qOFZc0NfOcU+24jEyX4PTAFNRKC2Luo+UkMm+c2R0Ln1SbK59UsnWLuN0lMj9aX+
0hfVcwKBgEVdKospaoOrdhYdfZ73E/y7mYcaEHxDddH1yKQuSDQFzbNtjS0vUuJ4
9zx5HcEc5WEhz+aGe32aIOJUgsMqNBcXkGREW0j3VIa78i73Zm/Klk6e5zeHGgzo
mIhrYTlEot5JyBbbwuBRkZ39Dx4rxqRCWDxLz39Bkl/9qP0+KsvY
-----END RSA PRIVATE KEY-----
 
 
)KEY";