import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os

output_dir = "Pairing_plots/Analytical/"

# Constants
mH = 125

# Sampling ranges
mX_vals = np.linspace(300, 2000, 200)
mY_vals = np.linspace(60, 1800, 100)

# Create meshgrid
mX, mY = np.meshgrid(mX_vals, mY_vals)

# Apply kinematic condition: mX > mY + mH
kinematic_mask = mX > (mY + mH)

# Compute f
#f = mY / mX
#f = np.where(kinematic_mask, mY / mX, np.nan)
f = mY / mX

# Compute g, avoid invalid sqrt
sqrt_arg = (mX**2 - (mY - mH)**2) * (mX**2 - (mY + mH)**2)
sqrt_arg = np.where(sqrt_arg < 0, np.nan, sqrt_arg)
g = np.where(kinematic_mask & (sqrt_arg >= 0), np.sqrt(sqrt_arg) / (2 * mX * np.minimum(mY, mH)), np.nan)

# Flatten arrays for scatter plot
f_flat = f.flatten()
g_flat = g.flatten()

# Remove NaNs
mask = ~np.isnan(g_flat)
f_flat = f_flat[mask]
g_flat = g_flat[mask]

# Plot
plt.figure(figsize=(8,6))
plt.scatter(f_flat, g_flat, s=1, alpha=0.6)
plt.xlabel('mY / mX')
plt.ylabel('kinematic fraction')
plt.title('Scatter plot: kinematic fraction vs mY/mX')
plt.grid(True)
plt.savefig(os.path.join(output_dir, f"Mass_fraction.png"))
plt.close()

# 3D plot
# Mask invalid g values
g_masked = np.ma.masked_invalid(g)

# Heatmap using axes
fig, ax = plt.subplots(figsize=(10,6))
pcm = ax.pcolormesh(mX, f, g_masked, shading='auto', cmap='viridis',vmin=0, vmax=5)
fig.colorbar(pcm, ax=ax, label='kinematic fraction')
ax.set_xlabel('mX')
ax.set_ylabel('mY / mX')
ax.set_ylim(0, 1)
ax.set_title('Heatmap: mX vs mY/mX vs kinematic fraction')
plt.savefig(os.path.join(output_dir, "Mass_fraction-heatmap.png"))
plt.close()
