# nmea
NMEA是一套定义接收机输出的标准信息，有几种不同的格式，每种都是独立相关的ASCII格式，逗点隔开数据流，数据流长度从30-100字符不等，通常以每秒间隔选择输出，最常用的格式为"GGA"，它包含了定位时间，纬度，经度，高度，定位所用的卫星数，其他的有速度，跟踪，日期等。

NMEA0183格式以“$”开始，主要语句有GPGGA，GPVTG，GPRMC等
$GPGGA,121252.000,3937.3032,N,11611.6046,E,1,05,2.0,45.9,M,-5.7,M,,0000*77   
$GPRMC,121252.000,A,3958.3032,N,11629.6046,E,15.15,359.95,070306,,,A*54   
$GPVTG,359.95,T,,M,15.15,N,28.0,K,A*04   
$GPGGA,121253.000,3937.3090,N,11611.6057,E,1,06,1.2,44.6,M,-5.7,M,,0000*72   
$GPGSA,A,3,14,15,05,22,18,26,,,,,,,2.1,1.2,1.7*3D   
$GPGSV,3,1,10,18,84,067,23,09,67,067,27,22,49,312,28,15,47,231,30*70   
$GPGSV,3,2,10,21,32,199,23,14,25,272,24,05,21,140,32,26,14,070,20*7E   
$GPGSV,3,3,10,29,07,074,,30,07,163,28*7D


### **1. `$GPGSA` - GPS DOP and Active Satellites (RTK Enhanced)**

**Format:**  
`$GPGSA,<1>,<2>,<3>,<3>,...,<3>,<4>,<5>,<6>,<7>*hh`

|Field|Name|RTK-Specific Details|Values|
|---|---|---|---|
|`<1>`|Mode|**Auto/Manual selection**|`A`=Auto (RTK prefers this), `M`=Manual|
|`<2>`|Fix Type|**RTK Fix Status**|`1`=No Fix  <br>`2`=2D  <br>`3`=3D  <br>`**4`=RTK Fixed**  <br>`**5`=RTK Float**|
|`<3>`|PRNs|**Satellites used in solution** (up to 12)|PRN numbers (e.g., `23` for GPS, `R12` for GLONASS)|
|`<4>`|PDOP|**Position Dilution of Precision** (Lower = Better)|`0.5` (RTK Ideal) to `99.9` (Poor)|
|`<5>`|HDOP|**Horizontal DOP** (Critical for RTK)|`<1.0` (RTK Quality)|
|`<6>`|VDOP|**Vertical DOP**|`<1.5` (Good RTK Altitude)|
|`<7>`|Checksum|Data integrity|`*hh` (Hex XOR value)|

**RTK Example:**  
`$GPGSA,A,4,23,14,12,31,18,22,32,25,,,,,0.8,0.5,0.6*12`  
→ **RTK Fixed** with 8 satellites, HDOP=0.5 (Excellent)

---

### **2. `$GPGSV` - GPS Satellites in View (Full RTK Version)**

**Format:**  
`$GPGSV,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>,<13>,<14>,<15>,<16>*hh`

|Field|Name|RTK-Specific Details|Values|
|---|---|---|---|
|`<1>`|Total Msgs|Number of GSV messages|`1`-`3` (1 msg = max 4 sats)|
|`<2>`|Msg Num|Current message number|`1` to `<1>`|
|`<3>`|Sats in View|**Total visible satellites**|`00`-`32` (RTK needs ≥12)|
|`<4>`|PRN|Satellite ID|`01`-`32` (GPS), `R01`-`R24` (GLONASS)|
|`<5>`|Elevation|Satellite elevation|`00`-`90`° (Higher = Better for RTK)|
|`<6>`|Azimuth|Satellite direction|`000`-`359`°|
|`<7>`|SNR|**Signal-to-Noise Ratio** (Critical for RTK)|`00`-`99` dB  <br>`≥40` dB needed for RTK|
|`<8>`-`<16>`|Repeat fields|Next 3 satellites|Same as `<4>`-`<7>`|

**Key RTK Notes:**

- **Dual-frequency satellites** (L1+L2) will show **higher SNR** (e.g., `45` dB).
    
- Messages split every **4 satellites** (e.g., 12 sats = 3 GSV messages).
    

**Example:**

text

$GPGSV,3,1,12,23,65,312,45,14,42,087,47,12,18,260,44,31,15,120,43*71  
$GPGSV,3,2,12,18,58,029,46,22,87,234,49,32,12,198,42,25,36,076,48*74  
$GPGSV,3,3,12,,,,,,,,,,,,*7A

→ 12 satellites, PRN 23 (SNR=45 dB, ideal for RTK)

---

### **3. `$GPGGA` - GPS Fix Data (Full RTK Version)**

**Format:**  
`$GPGGA,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,M,<10>,M,<11>,<12>*hh`

|Field|Name|RTK-Specific Details|Values|
|---|---|---|---|
|`<1>`|UTC Time|Time of fix|`hhmmss.sss`|
|`<2>`|Latitude|**High-precision (RTK)**|`ddmm.mmmmm` (7+ decimals)|
|`<3>`|N/S|Hemisphere|`N` or `S`|
|`<4>`|Longitude|**High-precision (RTK)**|`dddmm.mmmmm` (7+ decimals)|
|`<5>`|E/W|Hemisphere|`E` or `W`|
|`<6>`|Fix Quality|**RTK Status**|`0`=Invalid  <br>`1`=GPS  <br>`2`=DGPS  <br>`**4`=RTK Fixed**  <br>`**5`=RTK Float**|
|`<7>`|Satellites Used|**Dual-freq sats**|`00`-`32` (RTK needs ≥6)|
|`<8>`|HDOP|Horizontal precision|`<1.0` for RTK|
|`<9>`|Altitude|MSL height|`-9999.9`-`99999.9` meters|
|`<10>`|Geoid Sep|WGS84 ellipsoid|Meters|
|`<11>`|Diff Age|**RTCM correction age**|Seconds (`0`=RTK Fixed)|
|`<12>`|Base ID|**Reference station ID**|`0000`-`1023`|

**RTK Example:**  
`$GPGGA,082707.50,0118.0498162,N,10346.4556487,E,4,10,0.5,22.29,M,5.89,M,0,2001*67`  
→ **RTK Fixed** at cm-level precision, Station ID `2001`.

---

### **4. `$GPRMC` - Recommended Minimum Data (RTK Enhanced)**

**Format:**  
`$GPRMC,<1>,<2>,<3>,<4>,<5>,<6>,<7>,<8>,<9>,<10>,<11>,<12>*hh`

|Field|Name|RTK-Specific Details|Values|
|---|---|---|---|
|`<1>`|UTC Time|`hhmmss.sss`|Same as GGA|
|`<2>`|Status|**Fix validity**|`A`=Valid (RTK), `V`=Invalid|
|`<3>`-`<6>`|Lat/Lon|Same as GGA|High-precision|
|`<7>`|Speed|Over ground|Knots|
|`<8>`|Course|True North heading|Degrees|
|`<9>`|UTC Date|`ddmmyy`||
|`<10>`|Mag Var|Magnetic variation|Degrees|
|`<11>`|Var Dir|`E`/`W`||
|`<12>`|Mode|**RTK/DGPS mode**|`A`=Autonomous  <br>`D`=DGPS  <br>`**F`=RTK Fixed**  <br>`**R`=RTK Float**|

**RTK Example:**  
`$GPRMC,082707.50,A,0118.0498162,N,10346.4556487,E,0.1,45.2,300623,,,F*6A`  
→ **RTK Fixed** with valid cm-level position.

---

### **5. `$GPVTG` - Track Made Good (RTK Enhanced)**

**Format:**  
`$GPVTG,<1>,T,<2>,M,<3>,N,<4>,K,<5>*hh`

|Field|Name|RTK-Specific Details|Values|
|---|---|---|---|
|`<1>`|True Course|Degrees True North|`000`-`359`|
|`<2>`|Mag Course|Degrees Magnetic North|`000`-`359`|
|`<3>`|Speed (knots)||`000.0`-`999.9`|
|`<4>`|Speed (km/h)||`0000.0`-`1851.8`|
|`<5>`|Mode|**RTK status**|`A`=Autonomous  <br>`D`=DGPS  <br>`**F`=RTK Fixed**  <br>`**R`=RTK Float**|
