def read_file(file):
    raw = []
    with open(file, "r", encoding='latin-1') as f:
        for line in f:
            raw.append(line)

    return raw

def extract(raw):
    dts = None
    data = {}

    for line in raw:
        l = line.strip()
        if l.startswith("Ave Time (sec)"):
            dts = float(l.split()[-1])

        if l and l[0].isdigit():
            xy = l.split(",")
            x = float(xy[0])
            y = float(xy[1])
            data[x] = y

    return dts, data

def run_extraction(file):
    raw = read_file(file)

    if raw:
        dts, data = extract(raw)

    if dts and data:
        return dts, data

if __name__ == "__main__":
    file = "oxydase3.csv"
    run_extraction(file)
