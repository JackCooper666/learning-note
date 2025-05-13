
## Problem: Subscribing twice on the same topic

python

复制编辑

`self.subscriber = rospy.Subscriber('/imu/data', Imu, self.filter_imu, queue_size=100)`

Earlier you also subscribed:

python

复制编辑

`self.subscriber = rospy.Subscriber('/imu/data/bias', Imu, self.calculate_mean_bias)`

### This overwrites the first `self.subscriber`!

Only the **second subscriber will remain active**, because `self.subscriber =` reassigns the same variable.

---

### Solution 2: Use two separate variables:

python

复制编辑

`self.sub_bias = rospy.Subscriber('/imu/data/bias', Imu, self.calculate_mean_bias) self.sub_imu = rospy.Subscriber('/imu/data', Imu, self.filter_imu, queue_size=100)`

This ensures **both subscriptions stay alive**.

-----------------------------------------------------------------------------------------------

## Problem: Why Do We Need to Normalize Quaternions?

A **quaternion** represents a rotation in 3D space, and it must always satisfy:

### Unit Norm Condition:

复制编辑

`x² + y² + z² + w² = 1`

This means it must lie on the **unit 4D hypersphere** — otherwise it’s not a valid rotation.

Therefore, when process the imu bias data  the orientation bias should be normalized

## Solution: python version
q_bias = np.array([
    self.mean_orientation_x_bias,
    self.mean_orientation_y_bias,
    self.mean_orientation_z_bias,
    self.mean_orientation_w_bias
])

q_bias /= np.linalg.norm(q_bias)

------------------------------------------------------------------------








