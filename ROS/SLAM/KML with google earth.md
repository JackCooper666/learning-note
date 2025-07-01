# KML（Keyhole Markup Language）
本质：基于XML的地理数据标记语言
起源：由Keyhole Inc开发（后并入Google）
核心能力：
	标记点/线/面等地理要素
	定义样式、嵌入多媒体
	支持动态数据加载（NetworkLink）
文件扩展名：.kml
## KML文件结构解析
```xml
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://www.opengis.net/kml/2.2">
  <Document>
    <!-- 样式定义 -->
    <Style id="myStyle">...</Style>
    
    <!-- 地理要素 -->
    <Placemark>
      <name>示例地标</name>
      <Point>
        <coordinates>经度,纬度,高度</coordinates>
      </Point>
    </Placemark>
  </Document>
</kml>
```