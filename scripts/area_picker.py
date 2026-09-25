def search_algo(t, data):
    i = None
    return i

def run_area_pick(dts, data):
    # temporary manual setting of parameters
    TFRAME_PRE = 60 #s
    TFRAME_RUN = 60 #s
    AREA_NO = 3 #1,2,3

    no_scans = int(TFRAME_RUN / dts)

    # start of area is at about
    t = (AREA_NO - 1) * TFRAME_PRE / dts

    i = search_algo(t, data)
    i = 240
    if not i:
        raise Exception("Failed to find the starting point of the time frame")
    j = i + no_scans

    data_area = {}
    keys = list(data.keys())
    for k in keys[i:j+1]:
        data_area[k] = data[k]

    return data_area
