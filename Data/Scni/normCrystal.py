import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 🔹 Load Data
file_path = "cs137.org"
data = np.loadtxt(file_path)  # Assuming two-column format: (Bin, Counts)

bins = data[:, 0]  # Bin numbers (Energy bins)
counts = data[:, 1]  # Observed counts

# 🔹 Normalize Histogram by Integral
bin_width = np.diff(bins).mean()  # Estimate uniform bin width
norm_counts = counts / (np.sum(counts) * bin_width)  # Normalize by total integral

# 🔹 Crystal Ball Function
def crystal_ball(x, A, mu, sigma, alpha, n, bkg, slope):
    """
    A: Amplitude
    mu: Mean (Peak position)
    sigma: Standard deviation (Gaussian width)
    alpha: Tail transition
    n: Tail exponent
    bkg: Constant background
    slope: Linear background slope
    """
    t = (x - mu) / sigma
    abs_alpha = np.abs(alpha)

    # Gaussian core
    gaussian = np.exp(-0.5 * t**2)

    # Power-law tail (for x < mu - alpha*sigma)
    A_tail = (n / abs_alpha) ** n * np.exp(-0.5 * alpha**2)
    B_tail = n / abs_alpha - abs_alpha
    power_law = A_tail / (B_tail - t) ** n

    # Apply conditions
    cb_shape = np.where(t > -alpha, gaussian, power_law)

    return A * cb_shape + bkg + slope * x

# 🔹 Initial Parameter Estimates
init_params = [1.0, 631, 40, 1.5, 2.5, 0.001, -0.0005]  # Adjust A for normalized data

# 🔹 Fit the Normalized Histogram
popt, pcov = curve_fit(crystal_ball, bins, norm_counts, p0=init_params)

# 🔹 Generate Smooth Curve for Plot
x_fit = np.linspace(min(bins), max(bins), 1000)
y_fit = crystal_ball(x_fit, *popt) * np.sum(counts) * bin_width  # Scale back

# 🔹 Plot the Results
plt.figure(figsize=(8,6))
plt.scatter(bins, counts, color="black", label="Data", s=10)
plt.plot(x_fit, y_fit, color="red", label="Crystal Ball Fit", linewidth=2)
plt.xlabel("Energy (keV)")
plt.ylabel("Counts")
plt.legend()
plt.title("Cs-137 Spectrum Fit with Normalized Crystal Ball Function")
plt.grid()
plt.show()

# 🔹 Print Fitted Parameters
param_names = ["A", "mu", "sigma", "alpha", "n", "bkg", "slope"]
for name, value in zip(param_names, popt):
    print(f"{name}: {value:.5f}")

