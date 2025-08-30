```cpp
auto m1 = torch::randn({3, 4}, f32);
auto m2 = torch::randn({4, 5}, f32);
auto mm = m1.matmul(m2);          // 2D 矩阵乘 = mm({3,5})

// 批量矩阵乘（bmm）：输入 3D [B, M, K] x [B, K, N] -> [B, M, N]
auto A = torch::randn({8, 3, 4}, f32);
auto B = torch::randn({8, 4, 5}, f32);
auto C = torch::bmm(A, B);

// 连接/堆叠/拆分
auto cat0 = torch::cat({m1, m1}, /*dim=*/0);   // 拼接
auto stk0 = torch::stack({m1, m1}, /*dim=*/0); // 叠成新维
auto parts = m1.chunk(/*chunks=*/2, /*dim=*/1);// 等分
auto sps   = m1.split(/*split_size=*/2, /*dim=*/1);

// 广播与重复
auto e = m1.unsqueeze(0).expand({10, 3, 4});   // 共享内存的广播
auto rep = m1.repeat({2, 1});                  // 真实复制

// 索引收集/散射
auto idx = torch::tensor({0,2}, torch::kLong).to(device);
auto g = torch::gather(m1, /*dim=*/1, idx.unsqueeze(0).expand({3,2}));

```