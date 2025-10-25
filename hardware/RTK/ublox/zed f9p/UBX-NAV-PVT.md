你这段“`carrSoln 在 flags2(bit5~4)`”的说法不适用于 **UBX-NAV-PVT**（F9 系列常用的版本）。  
**在 NAV-PVT 里，RTK 的载波解状态 `carrSoln` 明确在 `flags` 的最高两位（bit7..6），而不是在 `flags2`。** 这点从你贴的 `NavPVT.msg` 里就能直接看出来：

- `flags` 里定义了  
    `FLAGS_CARRIER_PHASE_MASK = 192`（十六进制 `0xC0`，二进制 `1100 0000`）  
    并给了取值：
    
    - `CARRIER_PHASE_NO_SOLUTION = 0`
        
    - `CARRIER_PHASE_FLOAT = 64`（`0x40` → bit6=1）
        
    - `CARRIER_PHASE_FIXED = 128`（`0x80` → bit7=1）
        
- `flags2` 只定义了 UTC 时间/日期确认相关的三个位：
    
    - `FLAGS2_CONFIRMED_AVAILABLE = 32`（bit5）
        
    - `FLAGS2_CONFIRMED_DATE = 64`（bit6）
        
    - `FLAGS2_CONFIRMED_TIME = 128`（bit7）  
        **与 RTK 状态无关。**