**loosely coupled** and **tightly coupled** describe **at what level different sensors are fused**.

The simplest distinction is:
1. Loosely coupled: fuse sensor outputs, or Loosely coupled: sensor estimates are processed separately, and their cross-correlations may be ignored​​
2. Tightly coupled: fuse sensor measurements/residuals directly or Tightly coupled: measurements are estimated jointly, so correlations are preserved/handled consistently​


### Loosely coupled LIO

LiDAR first runs its own localization algorithm, for example ICP:

LiDAR scan→ICP→TLiDAR​

where
$$
T_{LiDAR}​=(R_{LiDAR}​,p_{LiDAR}​)
$$
is already a complete LiDAR pose estimate.

Meanwhile, IMU performs prediction:
$$
IMU→x_{k^{-}}​.
$$
Then EKF fuses these two higher-level estimates: IMU predicted pose+LiDAR ICP pose→EKF​

So LiDAR has already done most of its estimation before the fusion stage.

This is why it is called **loosely coupled**.

You can picture it as:
```
LiDAR
  ↓
 ICP
  ↓
LiDAR pose ─────┐
                │
                ▼
              EKF
                ▲
                │
IMU → prediction┘
```

The EKF only sees the final LiDAR pose.

It does **not** see the original LiDAR point constraints.

### Tightly coupled LIO

In tightly coupled LIO, LiDAR does not first produce an independent pose observation.

Instead, LiDAR measurements directly enter the same estimator.

For example:

LiDAR point→point-to-plane residual

such as
$$
r_{i}​=n_{i}^{T}​(Rp_{i}​+p−q_{i}​).
$$
The IMU gives the prediction:
$$
x_{k^{−}}​,P_{k^{−}}​.
$$
Then the estimator directly combines

IMU prior+LiDAR geometric residuals​

to estimate the state.

The architecture becomes
```
	             IMU
                  ↓
            state prediction
                  ↓
               x⁻, P⁻
                  ↓
LiDAR points → residuals r_i
                  ↓
	            EKF
                  ↓
            corrected state
```
So the same estimator sees the low-level sensor information.

That is why it is called **tightly coupled**.