import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

def generate_plot(file, data, data_area):
    fsize = 14

    x = np.array(list(data.keys()))
    y = np.array(list(data.values()))

    x_area = np.array(list(data_area.keys()))
    y_area = np.array(list(data_area.values()))

    res = stats.linregress(x_area,y_area)
    slope = round(res.slope, 4)
    intercept = round(res.intercept, 4)
    equation = f"y = {slope}x + {intercept}"

    # generate plot
    fig, ax = plt.subplots(figsize=(10,7))
    ax.plot(x,y, label='Measured data')
    ax.plot(x_area,y_area, label='Data used for lin. regression')
    ax.set_xlabel(r'Time t[min]', fontsize=fsize)
    ax.set_ylabel(r'Absorption', fontsize=fsize)
    plt.xticks(fontsize=fsize)
    plt.yticks(fontsize=fsize)
    plt.grid(color='gray',alpha=0.3,zorder=0)
    plt.legend(loc='best', fontsize=fsize)
    plt.text(
        0.7*x[-1], 0,
        equation,
        fontsize=fsize,
    )
    file = file[:-4]
    plt.savefig(f"plots/{file}.png")

    return res.slope

def run_plot_generation(file, data, data_area):
    EPSILON = 6220 * 10**(-6)
    VOL_CUVETTE = 1.2

    slope = generate_plot(file, data, data_area)
    v = round(np.abs(slope / EPSILON * VOL_CUVETTE), 4)

    return v
