# Gaussian Process
A **Gaussian Process** is a **collection of random variables**, any finite number of which have a **joint Gaussian distribution**.

## In analog system
Mathematically, a Gaussian Process (GP) is denoted as:

$$
f(x) \sim \mathcal{GP}(m(x), k(x, x'))
$$
Where:
- $f(x)$: A function drawn from the Gaussian Process.
- $m(x) = E[f(x)]$: The **mean function**.
- $k(x, x') = E[(f(x) - m(x)) (f(x') - m(x'))]$: The **covariance function** (also called the **kernel**).

## In discrete system
For a finite set of input points $X=[x_{1},...,x_{n}]$, the outputs $f=[f(x_{1}),...,f(x_{n})]^{⊤}$ follow a multivariate Gaussian:
$$
f \sim \mathcal{N}(0, K)
$$
Where $K \in \mathbb{R}^{n \times n}$ is the **covariance matrix** with entries $K_{ij} = k(x_{i}, x_{j})$.

## Key Concepts

- A GP defines a **distribution over functions**.
- For any finite set of inputs, the corresponding outputs follow a **multivariate normal distribution**.
- The **kernel function** $k(x, x')$ determines the smoothness and general behavior of the functions.

# UTM coordinate system

The **UTM (Universal Transverse Mercator)** coordinate system is a global map projection system that allows you to specify precise locations on Earth in a Cartesian (x, y) coordinate format. It is widely used in GPS, GIS, and navigation systems.
## 🔹 Key Concepts

- **Projection Type**: UTM uses a **Transverse Mercator projection**, which projects the Earth onto a cylinder wrapped around a meridian, rather than the equator.
    
- **Zoning**: The Earth is divided into **60 longitudinal zones**, each **6 degrees wide**, numbered from **1 to 60** starting at the 180°W meridian.
    
- **Hemisphere Separation**:
    
    - Northern Hemisphere: Uses a **false northing** of 0 meters at the equator.
        
    - Southern Hemisphere: Uses a **false northing** of 10,000,000 meters to avoid negative coordinates.
        
- **Easting and Northing**:
    
    - **Easting**: Distance from the central meridian of the zone (500,000 m is the central meridian).
        
    - **Northing**: Distance from the equator (in meters).
```yaml
Zone 33T, Easting: 500000, Northing: 4649776
```
This means:

- Zone **33**, in the **T** latitude band (optional but often used)
    
- 500 km east of the central meridian of Zone 33
    
- ~4.65 million meters north of the equator