# device setup and tensor initialization
```cpp
#include <torch/torch.h>     // 训练/张量 API
#include <torch/script.h>    // JIT/部署（如需）

// 设备与类型
torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);
auto f32 = torch::TensorOptions().dtype(torch::kFloat32).device(device);

// 创建张量
auto a = torch::zeros({3, 4}, f32);
auto b = torch::ones({3, 4}, f32);
auto r = torch::rand({2, 3}, f32);
auto n = torch::randn({2, 3}, f32);

// 基本属性
std::cout << a.sizes() << " | requires_grad=" << a.requires_grad() << "\n";

// 迁移/转换
a = a.to(torch::kCPU);                 // 改设备
a = a.to(torch::kFloat64);             // 改 dtype
float s = a[0][0].item<float>();       // 取标量（注意：会同步、慢，别在循环里频繁用）

```

# shape and index
```cpp
using namespace torch::indexing;

auto x = torch::randn({2, 3, 4}, f32);

// 形状变换
auto y1 = x.view({2, 12});             // 仅改视图（需连续内存）
auto y2 = x.reshape({2, 12});          // 可不连续，必要时返回拷贝
auto y3 = x.permute({0, 2, 1});        // 维度换位（返回非连续张量）
auto y4 = x.transpose(1, 2);           // 交换两个维度
auto y5 = x.contiguous();              // 转为连续内存
auto y6 = x.unsqueeze(1);              // 在 dim=1 插入维度：{2,1,3,4}
auto y7 = y6.squeeze();                // 去掉长度为1的维度

// 索引/切片（.index）
auto x01 = x.index({0, Slice(), 1});           // 等价于 x[0, :, 1]
auto xsub = x.index({Slice(0,2), Slice(1,3), Slice(None)}); // 范围切片
auto mask = x > 0;
auto xm = x.index({mask});                      // 布尔掩码

```