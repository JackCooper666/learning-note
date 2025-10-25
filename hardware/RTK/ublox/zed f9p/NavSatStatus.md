That `status.status` field comes from the standard ROS 2 message type `sensor_msgs/msg/NavSatStatus`.  
It’s nested inside every `sensor_msgs/msg/NavSatFix` message, and encodes **the quality of the GNSS fix**.

Here’s the mapping:

|**Value**|**Constant name**|**Meaning**|
|---|---|---|
|`-1`|`STATUS_NO_FIX`|No valid position fix – the receiver has not locked enough satellites.|
|`0`|`STATUS_FIX`|Standard autonomous GPS fix (code-based, no corrections).|
|`1`|`STATUS_SBAS_FIX`|SBAS / WAAS / EGNOS correction in use (DGNSS).|
|`2`|`STATUS_GBAS_FIX`|GBAS correction in use.|
|`> 2`|(non-standard)|Some drivers reuse higher numbers for RTK, PPP, etc.|

So in your echo:

`status:   status: 0   service: 1`

means:

- **`status.status = 0` → standard autonomous GPS fix** (no differential or RTK),
    
- **`status.service = 1` → GPS service** (bitmask: 1 = GPS, 2 = GLONASS, 4 = COMPASS, 8 = GALILEO).
    

If you later see  
`status.status = 1` → SBAS/DGNSS  
`status.status = 2` → GBAS  
`status.status = -1` → no fix.

> Note: the ROS 2 `ublox_driver` doesn’t directly propagate RTK-FIX/FLOAT into `status.status`; for true RTK state you must still check `flags` bits 7-6 (`carrSoln`) from the `/navpvt` topic.