import numpy as np
import matplotlib.pyplot as plt
import os

output_dir = "Pairing_plots/Analytical/"

# Constants
mh = 125.0   # GeV (SM Higgs mass)
DeltaR0 = 0.8
frac = 0.3
#frac = 1-frac

# Factor for target fraction f
factor = 1.0 / np.sqrt(frac**2)

# Define scan ranges
mX_vals = np.linspace(100, 2000, 1000)
mY_vals = np.linspace(60, 1800, 400)
MX, MY = np.meshgrid(mX_vals, mY_vals)

# Function for p* in X rest frame
lam = (MX**2 - (MY + mh)**2) * (MX**2 - (MY - mh)**2)
lam = np.where(lam > 0, lam, 0)   # remove unphysical negative values
pstar_vals = np.sqrt(lam) / (2 * MX)

# Transverse momentum threshold for resolved topology
pT_thr = (2.0 / DeltaR0) * np.minimum(MY, mh)
pT_req = pT_thr * factor

# Condition for resolved fraction >= f
resolved_region = (pstar_vals <= pT_req)

# Impose kinematic constraint: mX > mY + mh
kinematic_mask = MX > (MY + mh)
resolved_region_masked = resolved_region & kinematic_mask

# Plot
plt.figure(figsize=(7,6))
plt.contourf(MX, MY, resolved_region_masked, 
             levels=[-0.5,0.5,1.5], colors=["white","green"], alpha=0.6)

# Add the line mX = mY + mh
plt.plot(mX_vals, mX_vals - mh, "r--", label=r"$m_X = m_Y + m_h$")

plt.xlabel(r"$m_X$ [GeV]")
plt.ylabel(r"$m_Y$ [GeV]")
plt.title(r"Region with $f \geq {frac}$ (resolved topology), $m_X>m_Y+m_h$")
plt.xlim(100,2000)
plt.ylim(60,1800)
plt.legend()
plt.colorbar(label="Resolved region (1=yes, 0=no)", ticks=[0,1])
plt.savefig(os.path.join(output_dir, f"Analytic_fraction_{frac}.png"))
#plt.savefig(os.path.join(output_dir, f"Analytic_fraction.png"))
plt.close()


