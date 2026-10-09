import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

np.random.seed(42)

N = 6000  # 恒星数量

# ---------- 生成星系结构 ----------
# 半径分布：中心密、外围疏
r = np.random.power(2.2, N) * 10  # 0~10

# 两条对数旋臂 + 散布的盘面恒星
n_arms = 2
arm_id = np.random.randint(0, n_arms, N)
theta_disk = np.random.uniform(0, 2 * np.pi, N)

# 旋臂：对数螺旋 r = a * e^(b*theta)，加一点抖动
theta_arm = arm_id * (2 * np.pi / n_arms) + np.log(r + 0.3) * 2.2
theta_arm += np.random.normal(0, 0.15, N)  # 旋臂厚度抖动

is_arm = np.random.rand(N) < 0.65  # 65% 恒星在旋臂上
theta = np.where(is_arm, theta_arm, theta_disk)

# ---------- 旋转曲线（模拟暗物质的平缓曲线）----------
# v(r) = vmax * r / sqrt(r^2 + rc^2)：中心近似刚体转动，外围趋于匀速
rc = 1.5
vmax = 1.0
v = vmax * r / np.sqrt(r**2 + rc**2)
omega = v / (r + 0.05)  # 角速度，中心快外围慢

# ---------- 颜色与大小：中心偏黄（年老恒星），外围偏蓝（年轻恒星）----------
cmap = plt.cm.plasma
colors = cmap(1 - r / 11)
sizes = np.random.uniform(0.5, 3.5, N) * (1.5 - r / 20)

# 中心核球：额外一堆密集的黄色恒星
bulge_n = 1500
bulge_r = np.random.power(3, bulge_n) * 1.5
bulge_theta = np.random.uniform(0, 2 * np.pi, bulge_n)
bulge_v = vmax * bulge_r / np.sqrt(bulge_r**2 + rc**2)
bulge_omega = bulge_v / (bulge_r + 0.05)

fig, ax = plt.subplots(figsize=(8, 8), facecolor="black")
ax.set_facecolor("black")
ax.set_xlim(-12, 12)
ax.set_ylim(-12, 12)
ax.set_xticks([])
ax.set_yticks([])
ax.set_aspect("equal")

disk_sc = ax.scatter(r * np.cos(theta), r * np.sin(theta),
                     s=sizes, c=colors, cmap=cmap, edgecolors="none", alpha=0.8)
bulge_sc = ax.scatter(bulge_r * np.cos(bulge_theta), bulge_r * np.sin(bulge_theta),
                      s=np.random.uniform(0.5, 2, bulge_n),
                      c="#ffd9a0", edgecolors="none", alpha=0.9)

def update(frame):
    t = frame * 0.05
    # 每颗恒星按自己的角速度转
    disk_sc.set_offsets(np.c_[r * np.cos(theta + omega * t),
                              r * np.sin(theta + omega * t)])
    bulge_sc.set_offsets(np.c_[bulge_r * np.cos(bulge_theta + bulge_omega * t),
                               bulge_r * np.sin(bulge_theta + bulge_omega * t)])
    return disk_sc, bulge_sc

ani = FuncAnimation(fig, update, frames=600, interval=20, blit=True)
plt.title("Rotating Galaxy", color="white", fontsize=14)
plt.tight_layout()
plt.show()

# 想保存成 mp4 的话取消下面注释（需要 ffmpeg）：
# ani.save("galaxy.mp4", writer="ffmpeg", fps=30, dpi=150)
