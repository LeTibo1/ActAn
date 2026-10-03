from pathlib import Path
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

    # save plot in plots
    file_path = Path(file)
    path_to_plots = file_path.parent / "plots"

    filename = file_path.stem
    path_to_plots.mkdir(parents=True, exist_ok=True)

    plt.title(filename, fontsize=20)
    plt.savefig(path_to_plots / f"{filename}.png")

    return res.slope

def run_plot_generation(file, data, data_area, EPSILON, VOL_CUVETTE, IS_DOSAGE):
    slope = generate_plot(file, data, data_area)
    slope = round(slope, 4)

    if IS_DOSAGE == 0:
        v = round(np.abs(slope / EPSILON * VOL_CUVETTE), 4)
    elif IS_DOSAGE == 1:
        v = round(np.abs(slope / EPSILON), 4)

    return v, slope
