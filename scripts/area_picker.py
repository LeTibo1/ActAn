import numpy as np
from scipy import stats

def search_algo(data, area_no):
    start = None
    thresh = 0.05
    counter = 1
    i = 0
    is_reset = False
    found = False

    x = np.array(list(data.keys()))
    y = np.array(list(data.values()))

    for j in range(2, len(x)):
        if j - i < 2:
            continue

        # checks if j+1 is still following the linear trend
        if not is_reset:
            ### might want to change to polynomial regression
            res = stats.linregress(x[i:j], y[i:j])
            dif = np.abs(y[j+1] - (res.intercept + res.slope * x[j+1]))
            if dif > thresh:
                is_reset = True
                continue

        # if not, then find the next large increase in abs
        elif not found:
            dif = y[j+1] - y[j]
            if dif > thresh:
                found = True

        # find the highest point which will be the new starting point
        else:
            dif = y[j+1] - y[j]
            if dif < 0.001:
                is_reset = False
                found = False
                counter += 1
                i = j

                if counter == area_no:
                    start = j
                    break

    print("start found at:", start)
    return start

def run_area_pick(dts, data):
    # temporary manual setting of parameters
    TFRAME_PRE = 60 #s
    TFRAME_RUN = 60 #s
    AREA_NO = 3 #1,2,3

    no_scans = int(TFRAME_RUN / dts)

    i = search_algo(data, AREA_NO)
    if not i:
        raise Exception("Failed to find the starting point of the time frame")
    j = i + no_scans

    data_area = {}
    keys = list(data.keys())
    for k in keys[i:j+1]:
        data_area[k] = data[k]

    return data_area
