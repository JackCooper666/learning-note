# KML（Keyhole Markup Language）
本质：基于XML的地理数据标记语言
起源：由Keyhole Inc开发（后并入Google）
核心能力：
	标记点/线/面等地理要素
	定义样式、嵌入多媒体
	支持动态数据加载（NetworkLink）
文件扩展名：.kml
## KML文件结构解析
example
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
## Placemark
### Placemark的基本属性和用途

`Placemark` 元素是KML中最基本的构建块之一，它用于在地图上定位和标记特定的地理点或地理区域。一个 `Placemark` 元素可以包含有关一个位置的信息，如经纬度坐标、名称、描述以及样式信息。
```XML
<Placemark>
  <name>Great Pyramid</name>
  <description>See the world's oldest tourist attraction.</description>
  <Point>
    <coordinates>29.9792,31.1313</coordinates>
  </Point>
</Placemark>
```
通过 `Point` 元素内的 `coordinates` 标签， `Placemark` 标记了具体的经纬度位置。同时， `name` 和 `description` 提供了地点的名称和详细描述，这对于用户交互和数据展示至关重要。
### Placemark与地理信息的关联
Placemark 元素的强大之处在于其灵活性，它可以与多种地理信息相关联，包括点、线、多边形以及地理覆盖等。通过使用不同的几何元素，开发者可以创建具有不同地理意义的数据表示。

```xml
<Placemark>
  <name>Route to Work</name>
  <LineString>
    <extrude>1</extrude>
    <altitudeMode>clampToGround</altitudeMode>
    <coordinates>
      -73.976417,40.750319,0 -73.987303,40.741082,0 -73.987182,40.744465,0
    </coordinates>
  </LineString>
</Placemark>
```

在上述示例中， Placemark 与一条 LineString 相关联，表示了一条路线。 extrude 和 altitudeMode 元素提供了额外的视觉效果和高程控制。

## Folder
Folder 元素为KML文档提供了分组管理的功能，它使得复杂的地理数据能够被有序组织。通过创建文件夹，开发者可以对地点进行分类，为特定类型的地点创建分组，或者为不同项目的地点创建分组。文件夹内部可以包含 Placemark 、其他 Folder 甚至 NetworkLink 。
```xml
<Folder>
  <name>Favorite Places</name>
  <Placemark>
    <name>Statue of Liberty</name>
    <description>Icon of New York</description>
    <!-- Location coordinates -->
  </Placemark>
  <Folder>
    <name>NYC Landmarks</name>
    <Placemark>
      <!-- Location coordinates -->
    </Placemark>
  </Folder>
</Folder>
```
## Geometry
在KML中， `Geometry` 元素是一系列定义空间数据的元素的集合，包括 `Point` 、 `LineString` 、 `Polygon` 等。这些几何元素使得KML能够表示不同的空间特征，是构建复杂地理信息系统的基础。
```xml
<Placemark>
  <name>Mountain Range</name>
  <description>View of the Rocky Mountains</description>
  <Polygon>
    <extrude>1</extrude>
    <altitudeMode>clampToGround</altitudeMode>
    <outerBoundaryIs>
      <LinearRing>
        <coordinates>-109.03,37.45 -109.03,41.00 -102.05,41.00 -102.05,37.45 -109.03,37.45</coordinates>
      </LinearRing>
    </outerBoundaryIs>
  </Polygon>
</Placemark>
```
## Style
`Style` 元素允许开发者自定义KML元素的外观和行为。通过 `Style` 及其子元素 `IconStyle` 、 `LabelStyle` 、 `LineStyle` 和 `PolyStyle` 等，可以指定各种视觉效果，如图标样式、标签样式、线样式以及多边形样式等。
```xml
<Style id="myStyle">
  <IconStyle>
    <scale>1.1</scale>
    <Icon>
      <href>http://example.com/icon.png</href>
    </Icon>
  </IconStyle>
</Style>
<Placemark>
  <styleUrl>#myStyle</styleUrl>
  <!-- Location coordinates -->
</Placemark>
```
在上述示例中， `Style` 元素定义了一个特定的样式，并通过 `styleUrl` 属性将其应用于一个 `Placemark` 。这种样式定制极大地增强了地理信息的表现力。
## NetworkLink
`NetworkLink` 元素是KML中用于集成网络资源的重要组件。它允许KML文档链接到其他KML文件或网络服务，使KML文档能够动态地从外部源获取内容更新。
```xml
<NetworkLink>
  <name>Real-Time Traffic</name>
  <Link>
    <href>http://example.com/traffic.kml</href>
  </Link>
</NetworkLink>
```
通过 NetworkLink ，地图可以实时展示交通流量信息，从而为用户提供最新的地图数据。这一功能在动态变化的环境中尤为有用，例如交通监控和天气更新。

至此，我们已经详细剖析了KML文件的基本结构，从文档组织方式的 Document 元素，到地点标记的 Placemark 元素，再到分组管理功能的 Folder 与 Geometry 元素，以及样式定制的 Style 和网络功能的 NetworkLink 元素。下一部分将深入探讨KML在多样场景下的实际应用实例，包括地图标注、路线规划、区域与图像覆盖以及动态视觉效果与数据可视化等。