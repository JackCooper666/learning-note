SAM-RL 先通过真实 RGB-D 图像不断修正一个可微的虚拟物理世界，然后在这个虚拟世界里学习机器人应该怎么操作，同时利用 Q function 和可微渲染自动寻找更好的摄像头观察位置；最后再用 residual policy 修正 simulation 与 real world 之间剩余的误差。
```
══════════════════════════════════════
       REAL WORLD
══════════════════════════════════════

Camera takes RGB-D image
        │
        ▼
      I_real

        │
        │ Real2Sim
        ▼

══════════════════════════════════════
       VIRTUAL WORLD
══════════════════════════════════════

Simulation
        │
        ├── Render I_sim
        │
        ▼
 Compare I_sim vs I_real
        │
        ▼
      LOSS
        │
        ▼
Differentiable Rendering /
Differentiable Physics
        │
        ▼
Update:
 position
 shape
 color
 mass
 inertia
 etc.

══════════════════════════════════════
          Learn@Sim
══════════════════════════════════════

Differentiable Physics
        │
        ▼
Expert Trajectories
        │
      ┌─┴────────────┐
      ▼              ▼
   Actor            Q Network
      │              │
 Image→Action     Image+Action→Q
                     │
                     ▼
             optimize camera pose

══════════════════════════════════════
          Sim2Real
══════════════════════════════════════

Simulation Action
       │
       ▼
     a_sim
       +
Residual Policy
       │
       ▼
    δa_real
       │
       ▼
a_real = a_sim + δa_real
       │
       ▼
REAL ROBOT EXECUTES
```


# Real2Sim

# Learn@Sim

# Sim2 Real