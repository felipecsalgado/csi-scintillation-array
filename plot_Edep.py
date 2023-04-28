## Python 3 script for plotting the scoring mesh
# The plot is an integrated value over the scoring mesh assuming the detector
# to be imaged from the side.
#
# Created by: Felipe Salgado (FSU Jena, Helmholtz Institute Jena)

# Instructions:
# Insert the number of bins in the scoring mesh that were defined in the macro file: nx, ny and nz.
# Insert the number half length and half-width of the scoring mesh that were defined in the macro file:
# 							halfLength, and halfWidth
#
# Insert the number of primary particles of the simulation: Nparticles

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import scipy.constants as const
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter, AutoMinorLocator)
from matplotlib.colors import LogNorm
from scipy import interpolate
from tqdm import tqdm

SMALL_SIZE = 18
MEDIUM_SIZE = 20
BIGGER_SIZE = 24

plt.rc('font', size=SMALL_SIZE)          # controls default text sizes
plt.rc('axes', titlesize=SMALL_SIZE)     # fontsize of the axes title
plt.rc('axes', labelsize=MEDIUM_SIZE)    # fontsize of the x and y labels
plt.rc('xtick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
plt.rc('ytick', labelsize=SMALL_SIZE)    # fontsize of the tick labels
plt.rc('legend', fontsize=16)    # legend fontsize
plt.rc('figure', titlesize=BIGGER_SIZE)  # fontsize of the figure title
ml = MultipleLocator(2)

## Input parameters
# Modify accordily to your simulation
nx = 300
ny = 300
nz = 10

halfLength = 20.0 
halfWidth = 20
Nparticles = 5000


## Read txt file using numpy
import pandas as pd
data = pd.read_csv("eDep.txt", skiprows=3, usecols=(0, 1, 2, 3), delimiter=',', header=None)
data2 = data.to_numpy()
new_data = data2.reshape(nx, ny, nz, 4)


## Side View projection
projection2D = np.zeros((nx, ny))
#
for ix in tqdm(range(0, nx)):
    for iy in range(0, ny):
        for iz in range(0, nz):
            projection2D[ix, iy] = projection2D[ix, iy] + new_data[ix, iy, iz, 3]*1e3


# Scaling the energy deposited by the number of particles
projection2D = projection2D / Nparticles

offset = halfLength
x = np.linspace(-halfLength, halfLength, nx) + offset
y = np.linspace(-halfWidth, halfWidth, ny)
XX, YY = np.meshgrid(x, y)

## Plot the energy deposited
fig, axes1 = plt.subplots(1, 1, figsize=(10, 4))
axes = iter(np.ravel(axes1))
#
ax = next(axes)
#im = plt.imshow(projection2D, norm=LogNorm(1, 1e5))
im = ax.pcolormesh(XX, YY, projection2D.T, cmap=cm.jet, norm=LogNorm(0.01, 1e7), rasterized=True)
ax.set_xlabel("z-position (cm)")
ax.set_ylabel("x-position (cm)")
#ax.set_title(r"Photon Effective Dose for 2.5 GeV electron beam (top view)")
#ax.set_ylim(ax.get_ylim()[::-1])
cbar = plt.colorbar(im, pad=0.01)
#
cbar.ax.get_yaxis().labelpad = 1
cbar.ax.set_ylabel('Average energy\ndeposited (keV)')
#
ax.xaxis.set_major_locator(MultipleLocator(5))
ax.xaxis.set_major_formatter(FormatStrFormatter('%d'))
ax.xaxis.set_minor_locator(MultipleLocator(1))

ax.yaxis.set_major_locator(MultipleLocator(5))
ax.yaxis.set_major_formatter(FormatStrFormatter('%d'))
ax.yaxis.set_minor_locator(MultipleLocator(1))


ax.set_xlim(-1, 2 + 2*offset)
ax.set_ylim(-3, 3)
ax.grid(visible=True, which='both', axis='both', c='gray', alpha=0.2)
#
fig.tight_layout()
plt.savefig('Edep.png', dpi=500, transparent=False, format='png', facecolor='white')




######## sum over axis
integrated_sum = np.sum(projection2D.T, axis=0)
fig, axes1 = plt.subplots(1, 1, figsize=(10, 4))
axes = iter(np.ravel(axes1))
#
ax = next(axes)
im = ax.plot(np.linspace(0, 2*halfLength, nx), integrated_sum, '-xr')
#im = plt.imshow(projection2D, norm=LogNorm(1, 1e5))
ax.xaxis.set_major_locator(MultipleLocator(2))
ax.xaxis.set_major_formatter(FormatStrFormatter('%d'))
ax.xaxis.set_minor_locator(MultipleLocator(0.5))

ax.yaxis.set_major_locator(MultipleLocator(1e3))
ax.yaxis.set_major_formatter(FormatStrFormatter('%d'))
ax.yaxis.set_minor_locator(MultipleLocator(250))


ax.set_xlim(-1, 2 + 2*offset)
ax.set_xlabel("CsI crystal position")
ax.set_ylabel("Energy Deposited (keV)")
ax.grid(visible=True, which='both', axis='both', c='gray', alpha=0.2)
#ax.set_ylim(-3, 3)
#
fig.tight_layout()
plt.savefig('Integrated_sum.png', dpi=500, transparent=False, format='png', facecolor='white')


#
fig.tight_layout()
plt.savefig('DosePhotons_side.png', dpi=500)
