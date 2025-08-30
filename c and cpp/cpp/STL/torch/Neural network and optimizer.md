```cpp
// 1) 定义模型
struct MLPImpl : torch::nn::Module {
  torch::nn::Linear l1{nullptr}, l2{nullptr};
  MLPImpl(int in, int hidden, int out) {
    l1 = register_module("l1", torch::nn::Linear(in, hidden));
    l2 = register_module("l2", torch::nn::Linear(hidden, out));
  }
  torch::Tensor forward(torch::Tensor x) {
    x = torch::relu(l1->forward(x));
    return l2->forward(x);
  }
};
TORCH_MODULE(MLP); // 生成别名 MLP = std::shared_ptr<MLPImpl>

MLP model(/*in=*/32, /*hidden=*/64, /*out=*/10);
model->to(device);
model->train();    // 或 model->eval();

// 2) 损失与优化器
auto criterion = torch::nn::CrossEntropyLoss();
torch::optim::Adam optim(model->parameters(), torch::optim::AdamOptions(1e-3));

// 3) 训练步
auto xb = torch::randn({64, 32}, f32);
auto yb = torch::randint(/*low=*/0, /*high=*/10, {64}, torch::kLong).to(device);

optim.zero_grad();
auto logits = model->forward(xb);
auto loss = criterion(logits, yb);
loss.backward();
optim.step();

```