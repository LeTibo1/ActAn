import numpy as np
from scipy import stats

def run_calculation(data):
    EPSILON = 6220 * 10**(-6)
    VOL_CUVETTE = 1.2

    x = np.array(list(data.keys()))
    y = np.array(list(data.values()))

    res = stats.linregress(x,y)
    v = res.slope / EPSILON * VOL_CUVETTE

    return v
