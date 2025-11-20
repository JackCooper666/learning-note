# linear fitting
## Least square fit
```cpp
#include<Eigen/Eigen>
Eigen::Vector2d leastsquareFit(const vector<Eigen::Vector2d>& points)
{
	int n = points.size();
	Eigen::MatrixXd A(n,2);
	Eigen::VectorXd B(n);
	
	for(int i = 0; i < n; i++){
		A(i,0) = points[i](0);
		A(i,1) = 1;
		B(i) = points[i](1);
	}
	Eigen::Vector2d x = A.colPivHouseHolderQr().solve(B);
	return x;
}
```

```cpp
std::vector<double> LineFit(const std::vector<double>& x, const std::vector<double>& y){

}
```



## RANSAC
